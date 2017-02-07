#include <iostream>
#include <WinSock2.h>
#include <stdio.h>
#pragma comment (lib, "ws2_32.lib")
using namespace std;

/*
	UDP套接字服务端架构步骤:
	1． //初始化套接字环境WSAStartup		
	2． //初始化地址和端口
	3． //绑定SOCKADDR并创建UDP套接字socket		 
	4． //用recvfrom接收数据
	5． //用sendto发送数据
	6． //退出或者返回第5步继续	

*/

int main() {
	cout << "Server端:" << endl;

	//	1.初始化套接字环境WSAStartup		
	WSADATA wsdata;
	int ret = WSAStartup(MAKEWORD(2,2), &wsdata);
	if (ret != 0) {
		cout << "初始化失败" << endl;
		return -1;
	}

	//2.初始化地址和端口
	SOCKET MyServer= socket(AF_INET,SOCK_DGRAM, 0);
	if (ret == INVALID_SOCKET) {
		cout << "创建套接字失败" << endl;
		return -1;
	}

	//3.绑定SOCKADDR并创建UDP套接字socket
	SOCKADDR_IN ServerAddr, ClientAddr;
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
	ServerAddr.sin_port=htons(1234);
	ret = bind(MyServer, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr));
	if (ret == SOCKET_ERROR) {
		cout << "绑定套接字失败" << endl;
		closesocket(MyServer);
		WSACleanup();
		return -1;
	}

	 //4.用recvfrom接收数据
	while (true) {
		char buff[256];
		int len = sizeof(ClientAddr);
		recvfrom(MyServer, buff, 255, 0, (sockaddr*)&ClientAddr, &len);
		if (ret == SOCKET_ERROR) {
			cout << "接受数据失败" << endl;
			closesocket(MyServer);
			return -1;
		}
		UINT uip=ClientAddr.sin_addr.S_un.S_addr;
		printf("收到信息：%s\t来自于:d.%d.%d,%d \n",buff,LOBYTE(uip),HIBYTE(uip),LOBYTE(HIWORD(uip)),HIBYTE(HIWORD(uip)));


		 //5.用sendto发送数据	return 0;
		char sendbuff[256] = "服务器已get到数据";
		sendto(MyServer, sendbuff, 255, 0,(sockaddr*)&ClientAddr, len);

		 //6.退出或者返回第5步继续	}
	}
	getchar();
	return 0;
}