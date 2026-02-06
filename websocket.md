## websocket
#### Frame  
```
 0                   1                   2                   3
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-------+-+-------------+-------------------------------+
|F|R|R|R| opcode|M| Payload len |    Extended payload length    |
|I|S|S|S|  (4)  |A|     (7)     |             (16/64)           |
|N|V|V|V|       |S|             |   (if payload len==126/127)   |
| |1|2|3|       |K|             |                               |
+-+-+-+-+-------+-+-------------+ - - - - - - - - - - - - - - - +
|     Extended payload length continued, if payload len == 127  |
+ - - - - - - - - - - - - - - - +-------------------------------+
|                               |Masking-key, if MASK set to 1  |
+-------------------------------+-------------------------------+
| Masking-key (continued)       |          Payload Data         |
+-------------------------------- - - - - - - - - - - - - - - - +
:                     Payload Data continued ...                :
+ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - +
|                     Payload Data continued ...                |
+---------------------------------------------------------------+
```
#### 时序
```
客户端                            服务器端
  |                                  |
  |------- HTTP GET Upgrade --------->|
  |                                  |
  |<---- 101 Switching Protocols ----|
  |                                  |
  |        WebSocket连接建立         |
  |                                  |
  |------ Text Frame "Hello" -------->|
  |                                  |
  |<---- Text Frame "Response" ------|
  |                                  |
  |------ Binary Frame (data) ------->|
  |                                  |
  |<------- Ping Frame --------------|
  |                                  |
  |------ Pong Frame ---------------->|
  |                                  |
  |------ Close Frame --------------->|
  |                                  |
  |<------ Close Frame --------------|
  |                                  |
  |        TCP连接关闭              |
```

#### opcode


|值 |	含义	| 描述 |
0x0	| 延续帧	| 分片消息的延续
0x1	|文本帧 	| UTF-8文本数据
0x2	|二进制帧 |	 二进制数据
0x8	| 连接关闭 |	关闭连接
0x9	| Ping	| 心跳检测
0xA	| Pong	| 心跳响应

