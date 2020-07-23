#include"Player.h"
#include"ErrorNumber.h"
#include"List.h"
#include"Player.h"

#include<unistd.h>
#include<string.h>

List<Player*> playersList;//玩家列表

void whenSocketError(Socket *socket){
	printf("server error: %d %s\n",socket->errorNumber,ErrorNumber::getErrorString(socket->errorNumber));
}
void whenSocketAccepted(Socket *socket){
	printf("server收到连接\n");
	//添加玩家
	playersList.push_back(new Player());
	auto pPlayer=*(playersList.data(playersList.size()-1));
	//关联socket
	auto skt=socket->newAcceptSocket;
	skt->userData=pPlayer;
	pPlayer->setSocket(*skt);
}
void whenSocketDisconnected(Socket *socket){
	printf("socket断开连接\n");
}

int main(int argc,char* argv[]){
	ErrorNumber::init();
	Socket socket;//这个socket是用来监听玩家的连接的
	int listenPort=666;//默认端口
	auto file=fopen("server.cfg","rb");
	if(file){
		fseek(file,0,SEEK_SET);
		printf("fscanf %d\n",fscanf(file,"%d",&listenPort));
		fclose(file);
	}else{
		printf("配置文件server.cfg: %s\n",ErrorNumber::getErrorString(errno));
	}
	//设置回调函数
	socket.whenSocketError=whenSocketError;
	socket.whenSocketAccepted=whenSocketAccepted;
	socket.whenSocketDisconnected=whenSocketDisconnected;
	//监听
	socket.listenPort(listenPort);
	socket.acceptLoop();
	return 0;
}