#include"Player.h"
#include"Directory.h"
#include<string.h>

Player::Player(){
	whenTransceiverReceived=whenReceived;
}
Player::~Player(){}

void Player::soFilename(char *buffer,const char *name){sprintf(buffer,"lib%s.so",name);}
void Player::soFullFilename(char *buffer,const char *filename)const{sprintf(buffer,"so/%s/%s",platformName.data(),filename);}

#define SO_FILENAME_FULLNAME(name) \
char filename[256],fullname[256];\
soFilename(filename,name);\
soFullFilename(fullname,filename);

void Player::writeSOfileInfo(const char *name){
	SO_FILENAME_FULLNAME(name)
	//获取文件状态
	struct stat status;
	if(::stat(fullname,&status)==0){
		writeBuffer.write(filename).write(status.st_mtime);
	}
}

//判断所有字符是否字母
bool isAlpha(const string &str){
	int len=str.size();
	for(int i=0;i<len;++i){
		if(!isalpha(str[i]))return false;
	}return true;
}

void Player::whenReceived(Transceiver *transceiver){dynamic_cast<Player*>(transceiver)->whenReceived();}
void Player::whenReceived(){
	printf("Player:客户端请求\n");
	//收到了完整指令
	string command;
	readBuffer.rwSize=writeBuffer.rwSize=0;
	readBuffer.read(packetLength).read(command);
#define CASE(name) if(command==#name){resp##name(readBuffer);}else
	CASE(UpdateSOfiles)
	CASE(UpgradeSOfiles)
#undef CASE
	{printf("未处理的命令%s\n",command.data());}
}

void Player::respUpdateSOfiles(SocketDataBlock &reqData){
	//读取内容
	reqData.read(gameName).read(platformName);//游戏名
	//参数检查
	bool legal=isAlpha(gameName) && isAlpha(platformName);
	if(legal){//生成最新的库文件信息
		readySend("OK");
		//字符串拼接(直接用string会崩溃!)
		char gameNameClient[256];
		sprintf(gameNameClient,"%sClient",gameName.data());
		//添加更新文件
		writeSOfileInfo("lua");
		writeSOfileInfo("GamesEngines");
		writeSOfileInfo(gameName.data());
		writeSOfileInfo("GamesClient");
		writeSOfileInfo(gameNameClient);
	}else{//游戏名或平台名不合法
		readySend("ERR").write("Illegal game name or platform");
	}
	sendData();
}
void Player::respUpgradeSOfiles(SocketDataBlock &data){
	//读取文件名
	string name;
	data.read(name);
	printf("客户端要升级文件%s\n",name.data());
	//获取全路径
	char fullname[256];
	soFullFilename(fullname,name.data());
	if(sendFile(fullname)){//打开并获取了文件大小
		readySend("OK").write(sendFileSize);
	}else{//无法升级
		readySend("ERR").write("Send file failed");
	}
	sendData();
}