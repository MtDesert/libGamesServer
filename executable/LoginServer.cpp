#include"Socket.h"
#include"ErrorNumber.h"
#include"List.h"

#include<unistd.h>
#include<string.h>

List<Socket*> socketsList;//套接字列表

//客户端回调
void whenClientSent(Socket *socket){}
void whenClientReceived(Socket *socket){}

//服务端回调
void whenSocketAccepted(Socket *socket){
	//得到
	auto skt=socket->acceptedSocket();
	printf("accept %s %d\n",skt->getIPaddress().toString(),skt->getPort());
	//保存到队列中
	socketsList.push_back(socket);
}

void whenSocketError(Socket *socket){
	printf("error: %d %s\n",socket->errorNumber,ErrorNumber::getErrorString(socket->errorNumber));
}

int main(int argc,char* argv[]){
	Socket socket;
	//设置回调函数
	socket.whenSocketAccepted=whenSocketAccepted;
	socket.whenSocketSent=whenClientSent;
	socket.whenSocketReceived=whenClientReceived;
	socket.whenSocketError=whenSocketError;
	//监听
	socket.listenPort(2048);
	socket.waitListenFinish();
	return 0;
}