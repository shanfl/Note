#!/bin/bash
#将http://172.19.80.170/ (gitlab) 转到 192.168.8.2 

sudo iptables -t nat -A OUTPUT -d 172.19.80.170 -j DNAT --to-destination 192.168.8.2

:<<'COMMENT'
-t      表名 FILTER NAT ,默认filter
-A      新增规则,规则在chain列表下
-D      删除
-R      替换
-P      默认动作
-nL     查看当前运行的防火墙规则列表
--line-numbers

-i|o   网卡名称 i是指定数据包从哪块网卡进入,o是指定数据包从哪块网卡输出
-p      协议类型 可以指定规则应用的协议,包含tcp、udp和icmp等
-s      源IP地址 源主机的IP地址或子网地址
-sport  源端口号 数据包的IP的源端口号
-d      目标IP地址:目标主机的IP地址或子网地址
-dport  目标端口号:数据包的IP的目标端口号
-j 
    ACCEPT:允许数据包通过。

    DROP:丢弃数据包,不给任何回应。

    REJECT:拒绝数据包通过,并给发送者一个错误响应。

    LOG:记录数据包的信息到系统日志。

    DNAT:进行目标地址转换。

    SNAT:进行源地址转换。

    MASQUERADE:用于动态的网络地址转换,如在家庭网络中共享单个公网 IP。
COMMENT