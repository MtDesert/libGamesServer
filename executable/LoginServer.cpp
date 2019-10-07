#include"Player.h"
#include"ErrorNumber.h"
#include"List.h"
#include"Player.h"

#include<unistd.h>
#include<string.h>

List<Player> playersList;//玩家列表

void whenSocketError(Socket *socket){
	printf("error: %d %s\n",socket->errorNumber,ErrorNumber::getErrorString(socket->errorNumber));
}
void whenSocketAccepted(Socket *socket){
	playersList.push_back(Player(socket));
}

int main(int argc,char* argv[]){
	Socket socket;
	//设置回调函数
	socket.whenSocketAccepted=whenSocketAccepted;
	socket.whenSocketSent=Player::whenSocketSent;
	socket.whenSocketReceived=Player::whenSocketReceived;
	socket.whenSocketError=whenSocketError;
	//监听
	socket.listenPort(2048);
	socket.waitListenFinish();
	return 0;
}