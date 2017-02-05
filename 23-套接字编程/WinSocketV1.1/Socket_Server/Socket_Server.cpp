// WinSocket.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <WinSock2.h>		//应包含头文件WinSock2.h和库文件ws2_32.lib

/*
		服务器 端代码构建流程： 
		1、加载套接字库 （WSAStartup）
		2、创建套接字 （socket）
		3、将套接字绑定到一个本地地址和端口上（bind）
		4、将套接字设为监听模式，准备接收客户请求（listen）
		5、等待客户请求到来；当请求到来后，接受连接请求，返回一个新的对应于此次连接的套接字（accept）
		6、用返回的套接字和客户端进行通信（send/recv）
		7、返回，等待另一客户请求 回到第5步
		8、关闭套接字。 closesocket
		9、退出时用 WSACleanup卸载套接库
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

	//3、将套接字绑定到一个本地地址和端口上（bind）
	SOCKADDR_IN sockin;
	sockin.sin_family = AF_INET;
	sockin.sin_port=htons(1234);		//指定端口
	sockin.sin_addr.S_un.S_addr = htonl(INADDR_ANY);		//设置绑定地址INADDR_ANY
	
	//4、将套接字设为监听模1234接收客户请求（listen）
	bind(mysocket, (sockaddr*)&sockin, sizeof(sockin));
	printf("服务端已启动\n");

	//5、等待客户请求到来；当请求到来后，接受连接请求，返回一个新的对应于此次连接的套接字（accept）
	listen(mysocket, 4);
	SOCKADDR_IN clientsin;
	int len = sizeof(SOCKADDR_IN);
	while (true) {	//循环接受套接字
		SOCKET clientsocket = accept(mysocket, (SOCKADDR*)&clientsin, &len);		//保存客户端的套接字句柄clientsocket

		//6、用返回的套接字和客户端进行通信（send/recv）
		char buff[256] = {0};
		recv(clientsocket, buff, sizeof(buff), 0);
		printf("服务端收到信息:%s\n", buff);
		char buffret[] = "服务端已经收到信息啦\n";
		send(clientsocket, buffret, sizeof(buffret), 0);
		//7、返回，或等待另一客户请求 回到第5步
		//8、关闭套接字。 closesocket
		closesocket(clientsocket);
	}

	//9、退出时用 WSACleanup卸载套接库
	WSACleanup();

	return 0;
}

