cmake_minimum_required(VERSION 2.8)
include(../CompileScripts/CMakeLists.txt)

if(INCLUDE_DIR_ONLY)
	includeDirAll(../libGamesServer/)
	include(../libGamesEngines/CMakeLists.txt)
elseif(COMPILE_GAME_SERVER)
	message(编译服务端游戏库${GAME_NAME})
	project(${GAME_NAME}Server)
	#包含目录
	includeDirAll(../libGamesServer/)
	set(INCLUDE_DIR_ONLY ON)
	include(../lib${GAME_NAME}/CMakeLists.txt)#寻找对应游戏的工程目录
	#库输出
	add_library(${PROJECT_NAME} SHARED ${SRC_LIST})
	target_link_libraries(${PROJECT_NAME} GamesServer ${GAME_NAME} GamesEngines ${LIBS_LIST})
elseif(COMPILE_GAME_EXE)
	message(编译执行程序)
	project(GamesExe)
	#包含依赖库的目录
	set(INCLUDE_DIR_ONLY ON)
	include(../libGamesServer/CMakeLists.txt)
	#设置共用库,给不同平台的可执行文件用
	set(LIBS_LIST ${GAME_NAME}Server GamesServer ${GAME_NAME} GamesEngines ${LIBS_LIST})#把编译好的引擎添加到库中
	#以下为各种可执行文件的编译过程,根据情况选择编译自己需要的可执行文件即可
	add_executable(GameServer ./executable/GamesServer.cpp)
	target_link_libraries(GameServer ${LIBS_LIST})
else()
	message(编译服务端库)
	project(GamesServer)
	#添加所有paths下的源码和头文件
	srcIncludeAll()
	#包含依赖库的目录
	set(INCLUDE_DIR_ONLY ON)
	include(../libGamesEngines/CMakeLists.txt)
	#库输出
	add_library(${PROJECT_NAME} SHARED ${SRC_LIST})
	target_link_libraries(${PROJECT_NAME} ${LIBS_LIST} GamesEngines)
endif()