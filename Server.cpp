#include"Server.h"
#include"ErrorNumber.h"

//server
void whenSocketAccepted(Socket *socket){
	printf("accept!\n");
}
void whenSocketError(Socket *socket){
	printf("%d %s\n",socket->errorNumber,ErrorNumber::getErrorString(socket->errorNumber));
}

int Server::main(int argc,char* argv[]){
	//开始监听设置
	socket.whenSocketAccepted=whenSocketAccepted;
	socket.whenSocketError=whenSocketError;
	socket.listenPort(2048);
	socket.waitListenFinish();
    return 0;
}