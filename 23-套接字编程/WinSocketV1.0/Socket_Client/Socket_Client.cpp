// WinSocket.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <WinSock2.h>		//应包含头文件WinSock2.h和库文件ws2_32.lib

/*
		客户端 程序：
		1、加载套接字库  WSAStartup
		2、创建套接字（socket）
		3、向服务器发出连接请求（connect）
		4、和服务器端进行通信（send/recv）
		5、关闭套接字。closesocket
		6、卸载套接字库 WSACleanup
*/


int _tmain(int argc, _TCHAR* argv[])
{
	WORD wVersionRequested;	//版本号
	WSADATA wsaData;	//数据
	wVersionRequested = MAKEWORD( 2, 2 );

	//1、加载套接字库（WSAStartup）
	int err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) {
		printf("初始化失败\n");
		getchar();
		return 0;
	}

	//2、创建套接字（socket）
	SOCKET mysocket=socket(AF_INET, SOCK_STREAM, 0);

	//3、向服务器发出连接请求（connect）
	SOCKADDR_IN sockin;
	sockin.sin_family = AF_INET;
	sockin.sin_port=htons(1234);		//指定端口
	sockin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");	//绑定本机服务器地址127.0.0.1

	int ret = connect(mysocket, (SOCKADDR*)&sockin, sizeof(sockin));
	if (ret == SOCKET_ERROR) {
			printf("链接服务器失败\n");
			getchar();
			return 0;
	}
	printf("链接服务器成功\n");

	//4、和服务器端进行通信（send/recv）
	char mess[256];
	printf("请给服务端发送信息:");
	gets(mess);
	send(mysocket, mess, strlen(mess), 0);
	getchar();

	//5、关闭套接字。closesocket
	closesocket(mysocket);

	//6、卸载套接字库 WSACleanup
	WSACleanup();

	return 0;
}

