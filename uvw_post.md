```
// post_to_main_thread.hpp
#pragma once
#include <uvw.hpp>
#include <functional>
#include <queue>
#include <mutex>
#include <memory>

class post_to_main_thread {
public:
    static post_to_main_thread& instance() {
        static post_to_main_thread poster;
        return poster;
    }

    // 必须在主线程调用一次！
    void init(std::shared_ptr<uvw::loop> loop) {
        std::call_once(flag_, [this, loop]() {
            async_ = loop->resource<uvw::async_handle>();
            async_->on<uvw::async_event>([this](const auto&, auto&) {
                flush();
            });
        });
    }

    // 任意线程调用！
    template<typename F>
    void post(F&& task) {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            tasks_.push(std::function<void()>(std::forward<F>(task)));
        }
        async_->send();  // 唤醒主线程
    }

private:
    void flush() {
        std::queue<std::function<void()>> local;
        {
            std::lock_guard<std::mutex> lock(mutex_);
            local.swap(tasks_);
        }
        while (!local.empty()) {
            local.front()();
            local.pop();
        }
    }

    std::shared_ptr<uvw::async_handle> async_;
    std::queue<std::function<void()>> tasks_;
    std::mutex mutex_;
    std::once_flag flag_;
};

// 全局便捷函数
template<typename F>
void post_to_main_thread(F&& task) {
    post_to_main_thread::instance().post(std::forward<F>(task));
}
```

#### 完整 TCP 示例（正确版）
```
// tcp_client.cpp
#include <uvw.hpp>
#include <iostream>
#include <memory>
#include "post_to_main_thread.hpp"

class tcp_client : public std::enable_shared_from_this<tcp_client> {
public:
    static std::shared_ptr<tcp_client> create(std::shared_ptr<uvw::loop> loop) {
        auto client = std::shared_ptr<tcp_client>(new tcp_client(loop));
        
        // ✅ 必须在主线程创建 handle
        loop->run([client](uvw::loop&) {
            client->tcp_ = client->loop_->resource<uvw::tcp_handle>();
            client->setup_callbacks();
        });
        
        return client;
    }
    
    // ✅ 线程安全 connect
    void connect(std::string host, int port) {
        post_to_main_thread([this, host = std::move(host), port]() {
            if (!tcp_) return;
            sockaddr_in dest;
            uv_ip4_addr(host.c_str(), port, &dest);
            tcp_->connect(dest);
        });
    }
    
    // ✅ 线程安全 send
    void send(std::string data) {
        post_to_main_thread([this, data = std::move(data)]() {
            if (tcp_ && tcp_->active()) {
                tcp_->write(data.data(), data.size());
            }
        });
    }
    
    // ✅ 线程安全 close
    void close() {
        post_to_main_thread([self = shared_from_this()]() {
            if (self->tcp_) {
                self->tcp_->once<uvw::close_event>([self](const auto&, auto&) {
                    self->tcp_.reset();
                });
                self->tcp_->close();
            }
        });
    }
    
private:
    explicit tcp_client(std::shared_ptr<uvw::loop> loop) : loop_(loop) {}
    
    void setup_callbacks() {
        if (!tcp_) return;
        
        tcp_->on<uvw::connect_event>([](const auto&, auto&) {
            std::cout << "Connected!" << std::endl;
        });
        
        tcp_->on<uvw::data_event>([](const auto& evt, auto&) {
            std::cout << "Received: " << std::string(evt.data.get(), evt.length) << std::endl;
        });
        
        tcp_->on<uvw::end_event>([this](const auto&, auto&) {
            std::cout << "Connection closed" << std::endl;
            close();
        });
        
        tcp_->on<uvw::error_event>([](const auto& evt, auto&) {
            std::cerr << "Error: " << evt.what() << std::endl;
        });
    }
    
    std::shared_ptr<uvw::loop> loop_;
    std::shared_ptr<uvw::tcp_handle> tcp_;
};

int main() {
    auto loop = uvw::loop::create();
    
    // ✅ 1. 初始化 post_to_main_thread（必须在主线程）
    post_to_main_thread::instance().init(loop);
    
    // ✅ 2. 在主线程创建 client
    std::shared_ptr<tcp_client> client;
    loop->run([&client, loop](uvw::loop&) {
        client = tcp_client::create(loop);
    });
    
    // ✅ 3. 工作线程 - 所有调用都线程安全
    std::thread worker([client]() {
        client->connect("127.0.0.1", 8888);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        client->send("Hello from thread!");
        std::this_thread::sleep_for(std::chrono::seconds(1));
        client->close();
    });
    
    loop->run();
    worker.join();
    
    return 0;
}
```

#### 🎯 最终简洁版 - 直接使用 async_handle
```
// 最简单的跨线程投递实现
#include <uvw.hpp>
#include <functional>
#include <queue>
#include <mutex>

class main_thread {
public:
    main_thread(std::shared_ptr<uvw::loop> loop) {
        async_ = loop->resource<uvw::async_handle>();
        async_->on<uvw::async_event>([this](auto&, auto&) {
            std::queue<std::function<void()>> local;
            {
                std::lock_guard<std::mutex> lock(mutex_);
                local.swap(tasks_);
            }
            while (!local.empty()) {
                local.front()();
                local.pop();
            }
        });
    }
    
    template<typename F>
    void post(F&& task) {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            tasks_.push(std::function<void()>(std::forward<F>(task)));
        }
        async_->send();
    }
    
private:
    std::shared_ptr<uvw::async_handle> async_;
    std::queue<std::function<void()>> tasks_;
    std::mutex mutex_;
};

// 使用：
auto loop = uvw::loop::create();
main_thread mt(loop);  // 在主线程创建

// 任意线程调用
mt.post([]() {
    std::cout << "在主线程执行" << std::endl;
});
```
