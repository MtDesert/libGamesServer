#include"Player.h"
#include"Protocol.h"

Player::Player():Player(nullptr){}
Player::Player(Socket *skt):socket(skt){
	if(skt){
		skt->userData=this;
	}
}

void Player::whenSocketSent(Socket *skt){}
void Player::whenSocketReceived(Socket *skt){
	auto block=skt->recvData;
	uint cmd=block.dataPointer[0];
	switch(cmd){
		case enumSelectGame:break;
		case enumRegister:break;
		case enumLogin:break;
		case enumLogout:break;
		default:printf("未知请求%d\n",cmd);
	}
}