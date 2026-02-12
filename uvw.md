```
#include <uvw.hpp>
#include <string>

// 自定义事件
struct SendDataEvent : uvw::Event<SendDataEvent> {
    std::string data;
    explicit SendDataEvent(std::string d) : data(std::move(d)) {}
};

class UdpSender : public std::enable_shared_from_this<UdpSender> {
public:
    UdpSender(std::shared_ptr<uvw::Loop> loop) : loop_(loop) {
        udp_ = loop_->resource<uvw::UDPHandle>();
        udp_->bind("0.0.0.0", 0);
        
        // 监听自定义事件
        loop_->resource<uvw::AsyncHandle>()->on<SendDataEvent>(
            [this](const SendDataEvent& event, uvw::AsyncHandle&) {
                // 在主线程执行
                udp_->send(udp_->sock(), 
                          event.data.c_str(), 
                          event.data.size());
            });
    }
    
    // 线程安全：任意线程调用
    void raw_send(std::string data) {
        loop_->resource<uvw::AsyncHandle>()->send(
            SendDataEvent(std::move(data))
        );
    }
    
private:
    std::shared_ptr<uvw::Loop> loop_;
    std::shared_ptr<uvw::UDPHandle> udp_;
};
```


###### lambda + vector 版本
```
#include <uvw.hpp>
#include <vector>
#include <functional>

class MainThreadPoster {
public:
    MainThreadPoster(std::shared_ptr<uvw::Loop> loop) : loop_(loop) {
        async_ = loop_->resource<uvw::AsyncHandle>();
        
        async_->on<uvw::AsyncEvent>([this](const uvw::AsyncEvent&, uvw::AsyncHandle&) {
            std::vector<std::function<void()>> local_tasks;
            {
                std::lock_guard<std::mutex> lock(mutex_);
                local_tasks.swap(tasks_);  // 无锁交换
            }
            
            for (auto& task : local_tasks) {
                task();  // 在主线程执行
            }
        });
    }
    
    template<typename F>
    void post(F&& task) {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            tasks_.push_back(std::forward<F>(task));
        }
        async_->send();  // 唤醒主线程
    }
    
private:
    std::shared_ptr<uvw::Loop> loop_;
    std::shared_ptr<uvw::AsyncHandle> async_;
    std::vector<std::function<void()>> tasks_;
    std::mutex mutex_;
};

// 使用示例
auto loop = uvw::Loop::getDefault();
auto poster = std::make_shared<MainThreadPoster>(loop);

// 任意线程调用
poster->post([]() {
    std::cout << "在主线程执行" << std::endl;
});

// raw_send 封装
void raw_send(std::shared_ptr<uvw::UDPHandle> udp, std::string data) {
    poster->post([udp, data = std::move(data)]() {
        udp->send(udp->sock(), 
                 reinterpret_cast<const char*>(data.data()), 
                 data.size());
    });
}
```


#### 使用 uvw::Loop::walk + uv_async
```
#include <uvw.hpp>
#include <functional>
#include <queue>
#include <mutex>

class UvwThreadSafeSender {
public:
    UvwThreadSafeSender(std::shared_ptr<uvw::Loop> loop, 
                        std::shared_ptr<uvw::UDPHandle> udp) 
        : loop_(loop), udp_(udp) {
        
        // 创建 AsyncHandle 用于线程间通信
        async_ = loop_->resource<uvw::AsyncHandle>();
        
        // 设置回调 - 在主线程执行
        async_->on<uvw::AsyncEvent>([this](const uvw::AsyncEvent&, uvw::AsyncHandle&) {
            flush_tasks();
        });
    }
    
    // 任意线程调用：post 任务到主线程
    void post_to_main_thread(std::function<void()> task) {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            tasks_.push(std::move(task));
        }
        async_->send();  // 唤醒主线程
    }
    
    // 线程安全的 raw_send
    void raw_send(std::string data) {
        post_to_main_thread([this, data = std::move(data)]() {
            // 在主线程中执行发送
            udp_->send(udp_->sock(), 
                      reinterpret_cast<const char*>(data.data()), 
                      data.size());
        });
    }
    
private:
    void flush_tasks() {
        std::queue<std::function<void()>> local_queue;
        {
            std::lock_guard<std::mutex> lock(mutex_);
            local_queue.swap(tasks_);
        }
        
        while (!local_queue.empty()) {
            local_queue.front()();
            local_queue.pop();
        }
    }
    
    std::shared_ptr<uvw::Loop> loop_;
    std::shared_ptr<uvw::UDPHandle> udp_;
    std::shared_ptr<uvw::AsyncHandle> async_;
    
    std::queue<std::function<void()>> tasks_;
    std::mutex mutex_;
};
```