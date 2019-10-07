#ifndef PLAYER_H
#define PLAYER_H

#include"Socket.h"
//玩家,当服务端有新的连接进来时,就会创建一个本类对象
class Player{
public:
	//网络部分
	Socket *socket;//与玩家进行通讯用的socket
	uint8 sendBuffer[1024];//发送缓冲
public:
	Player();
	Player(Socket *skt);
	//数据部分
	string gameName;//游戏名,用来指明用户要玩的游戏
	string username;//用户名,这是用来调用玩家数据的凭据

	static void whenSocketSent(Socket *skt);
	static void whenSocketReceived(Socket *skt);
};
#endif