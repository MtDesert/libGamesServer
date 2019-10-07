cmake_minimum_required(VERSION 2.8)
include(../CompileScripts/CMakeLists.txt)

if(GAME_NAME)
	include(../lib${GAME_NAME}/CMakeLists.txt)#读取游戏的CMakeLists.txt
	#编译执行程序或库
	if(COMPILE_GAME_EXE)
		message(编译执行程序)
		project(GamesExe)
		#设置共用库,给不同平台的可执行文件用
		#以下为各种可执行文件的编译过程,根据情况选择编译自己需要的可执行文件即可
		add_executable(GamesGLUT ./executable/LoginServer.cpp)
		target_link_libraries(GamesGLUT ${LIBS_LIST})
	else()
		message(编译客户端游戏库${GAME_NAME})
		project(${GAME_NAME}Client)
		srcIncludeAll(../lib${GAME_NAME}/Client/ ${CLIENT_DIR})
		#库输出
		add_library(${PROJECT_NAME} SHARED ${SRC_LIST})
		target_link_libraries(${PROJECT_NAME} GamesClient ${GAME_NAME} GamesEngines ${LIBS_LIST})
	endif()
else()
	message(编译服务端库)
	project(GameServer)
	#添加所有paths下的源码和头文件
	srcIncludeAll(./ .)
	#包含依赖库的目录
	set(INCLUDE_DIR_ONLY ON)
	include(../libGamesEngines/CMakeLists.txt)
	#库输出
	add_library(${PROJECT_NAME} SHARED ${SRC_LIST})
	target_link_libraries(${PROJECT_NAME} GamesEngines ${LIBS_LIST})
	#程序输出
	add_executable(LoginServer ./executable/LoginServer.cpp)
	target_link_libraries(LoginServer GameServer GamesEngines)
endif()