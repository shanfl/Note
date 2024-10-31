#### gitlab



#### 1. ssh登陆原docker

`docker ps`

| containerid  | image                   | command           | created | status | ports                                                            | names  |
| ------------ | ----------------------- | ----------------- | ------- | ------ | ---------------------------------------------------------------- | ------ |
| 3f0eeb6d86f5 | gitlab/gitlab-ce:latest | "/assets/wrapper" | ...     | ...    | 0.0.0.0:443->443/tcp, 0.0.0.0:9022->22/tcp, 0.0.0.0:8099->80/tcp | gitlab |



`docker inspect 3f0eeb6d86f5`

        "HostConfig": {
            "Binds": [
                "/srv/gitlab/config:/etc/gitlab",
                "/srv/gitlab/logs:/var/log/gitlab",
                "/srv/gitlab/data:/var/opt/gitlab"
            ],
            "ContainerIDFile": "",
            "LogConfig": {
                "Type": "json-file",
                "Config": {}
            },
            "NetworkMode": "default",
            "PortBindings": {
                "22/tcp": [
                    {
                        "HostIp": "",
                        "HostPort": "9022"
                    }
                ],
                "443/tcp": [
                    {
                        "HostIp": "",
                        "HostPort": "443"
                    }
                ],
                "80/tcp": [
                    {
                        "HostIp": "",
                        "HostPort": "8099"
                    }
                ]
            },

   ``

```
docker save gitlab/gitlab-ce > gitlab.tar
scp -r gitlab.tar`  dest-ssh:~
scp -r gitlab-src     dest-ssh:/srv/
```

#### 2. 登陆到目的gitlab地址

0. 安装docer engine

因为我们scp拷贝gitalb的物理目录到了 /srv
`tree /srv -L 2`

```
/srv
└── gitlab
    ├── config
    ├── data
    └── logs
```

1. 编写docker 启动脚本  start_gitlab_docker.sh

```bash
#!/bin/bash

GITLAB_HOME='/srv/gitlab'

docker run --detach \
  --hostname gitlab \
  --name gitlab \
  --publish 443:443 --publish 8099:80 --publish 9022:22 \
  --restart always \
  --volume $GITLAB_HOME/config:/etc/gitlab \
  --volume $GITLAB_HOME/logs:/var/log/gitlab \
  --volume $GITLAB_HOME/data:/var/opt/gitlab \
  gitlab/gitlab-ce:latest
```

2. docker load gitlab.tar

3. docker images
   
   ```
   REPOSITORY         TAG       IMAGE ID       CREATED       SIZE
   gitlab/gitlab-ce   latest    7d67652b36a7   4 years ago   1.92GB
   ```

4. `./start_gitlab_docker.sh`

5. 多次执行根据情况
   
   ```
   docker exec -it gitlab update-permissions
   docker restart gitlab
   docker exec gitlab gitlab-ctl reconfigure
   docker restart gitlab
   ```
   
   

6. `docker exec gitlab gitlab-ctl status`  查看还有哪些没有启动

```
run: alertmanager: (pid 347) 2226s; run: log: (pid 328) 2226s
down: gitaly: 1s, normally up, want up; run: log: (pid 330) 2226s
run: gitlab-exporter: (pid 335) 2226s; run: log: (pid 324) 2226s
run: gitlab-workhorse: (pid 349) 2226s; run: log: (pid 334) 2226s
down: grafana: 1s, normally up, want up; run: log: (pid 325) 2226s
run: logrotate: (pid 346) 2226s; run: log: (pid 329) 2226s
run: nginx: (pid 341) 2226s; run: log: (pid 323) 2226s
run: postgres-exporter: (pid 345) 2226s; run: log: (pid 333) 2226s
run: postgresql: (pid 344) 2226s; run: log: (pid 332) 2226s
run: prometheus: (pid 338) 2226s; run: log: (pid 327) 2226s
run: puma: (pid 339) 2226s; run: log: (pid 321) 2226s
run: redis: (pid 336) 2226s; run: log: (pid 326) 2226s
run: redis-exporter: (pid 343) 2226s; run: log: (pid 331) 2226s
run: sidekiq: (pid 337) 2226s; run: log: (pid 322) 2226s
run: sshd: (pid 32) 2232s; run: log: (pid 31) 2232s
```

看到 down的 就要根据具体问题来解决



问题 如  gitaly

```
cd /var/opt/gitlab/gitaly/
chmod 777 gitaly.pid 
gitlab-ctl restart
```



#### todo: iptables 重定向ip到目的ip



#### 5. docker 命令免sudo

```bash
     sudo groupadd docker
     sudo gpasswd -a ${USER} docker
     sudo chmod a+rw /var/run/docker.sock
     sudo systemctl restart docker 

```


