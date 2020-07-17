#ifndef PLAYER_H
#define PLAYER_H

#include"Transceiver.h"
//玩家,当服务端有新的连接进来时,就会创建一个本类对象
class Player:public Transceiver{
public:
	Player();
	~Player();
	//数据部分
	string gameName;//游戏名,用来指明用户要玩的游戏
	string platformName;//平台名,确定游戏的运行环境
	string username;//用户名,这是用来调用玩家数据的凭据

	//收到请求后处理请求
	static void whenReceived(Transceiver *transceiver);
	void whenReceived();
	//响应客户端请求的函数
#define RESP(name) void resp##name(SocketDataBlock &data);
	RESP(UpdateSOfiles)
	RESP(UpgradeSOfiles)
#undef RESP
};
#endif