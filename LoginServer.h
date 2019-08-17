#ifndef LOGINSERVER_H
#define LOGINSERVER_H

#include"Socket.h"

//服务端
class LoginServer{
protected:
	Socket socket;//监听连接用的Socket
public:
	int main(int argc,char* argv[]);//服务端主函数
};

#endif