#include"Player.h"
#include"Directory.h"
#include<string.h>

Player::Player(){
	whenTransceiverReceived=whenReceived;
}
Player::~Player(){}

//判断所有字符是否字母
bool isAlpha(const string &str){
	int len=str.size();
	for(int i=0;i<len;++i){
		if(!isalpha(str[i]))return false;
	}return true;
}
//客户端库,用于比对更新
static void addSOfileInfo(SocketDataBlock &sdb,const string &platformName,const string &name){
	char filename[256],fullname[256];
	sprintf(filename,"lib%s.so",name.data());
	sprintf(fullname,"so/%s/%s",platformName.data(),filename);
	//获取文件状态
	struct stat status;
	if(::stat(fullname,&status)==0){
		sdb.add(filename).add(status.st_mtime);
	}
}

void Player::whenReceived(Transceiver *transceiver){dynamic_cast<Player*>(transceiver)->whenReceived();}
void Player::whenReceived(){
	//收到了完整指令
	uint16 u16;
	string command;
	readBuffer.rwSize=writeBuffer.rwSize=0;
	readBuffer.read(u16).read(command);
#define CASE(name) if(command==#name){resp##name(readBuffer);}else
	CASE(UpdateSOfiles)
	CASE(UpgradeSOfiles)
#undef CASE
	{printf("未处理的命令%s\n",command.data());}
}

void Player::respUpdateSOfiles(SocketDataBlock &reqData){
	//读取内容
	string gameName,platform;
	reqData.read(gameName).read(platform);//游戏名
	//参数检查
	bool legal=isAlpha(gameName) && isAlpha(platform);
	if(legal){//生成最新的库文件信息
		writeBuffer.add("OK");
		//字符串拼接(直接用string会崩溃!)
		char gameNameClient[256];
		sprintf(gameNameClient,"%sClient",gameName.data());
		//添加更新文件
		addSOfileInfo(writeBuffer,platform,"lua");
		addSOfileInfo(writeBuffer,platform,"GamesEngines");
		addSOfileInfo(writeBuffer,platform,gameName);
		addSOfileInfo(writeBuffer,platform,"GamesClient");
		addSOfileInfo(writeBuffer,platform,gameNameClient);
	}else{//游戏名或平台名不合法
		writeBuffer.add("ERR").add("Illegal game name or platform");
	}
	//开始回发数据
	sendData();
}
void Player::respUpgradeSOfiles(SocketDataBlock &data){
	string filename;
	data.read(filename);
	printf("客户端要更新文件%s\n",filename.data());
}