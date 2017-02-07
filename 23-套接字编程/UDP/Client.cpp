#include <iostream>
#include <WinSock2.h>
#pragma comment (lib, "ws2_32.lib")
using namespace std;

/*
	UDP客户端架构步骤
	1． //初始化套接字环境WSAStartup		
	2． //初始化地址和端口
	3． //创建UDP套接字socket		 
	4． //用sendto发送数据
	5． //用recvfrom接收数据
*/

int main() {
	cout << "请发送Client信息: " << endl;

	//	1.初始化套接字环境WSAStartup		
	WSADATA wsdata;
	int ret = WSAStartup(MAKEWORD(2,2), &wsdata);
	if (ret != 0) {
		cout << "初始化失败" << endl;
		return -1;
	}

	//2.初始化地址和端口
	SOCKET MyClient= socket(AF_INET,SOCK_DGRAM, 0);
	if (ret == INVALID_SOCKET) {
		cout << "创建套接字失败" << endl;
		return -1;
	}

	//3.绑定SOCKADDR并创建UDP套接字socket
	SOCKADDR_IN ServerAddr, ClientAddr;
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
	ServerAddr.sin_port=htons(1234);

	while (true) {
		char sendbuff[256];
		gets(sendbuff);
		 //4.用sendto发送数据	return 0;
		sendto(MyClient, sendbuff, 255, 0,(sockaddr*)&ServerAddr, sizeof(ServerAddr));

		//5.用recvfrom接收数据
		char buff[256];
		int len = sizeof(ServerAddr);
		recvfrom(MyClient, buff, 255, 0, (sockaddr*)&ServerAddr, &len);
		if (ret == SOCKET_ERROR) {
			cout << "接受数据失败" << endl;
			closesocket(MyClient);
			WSACleanup();
			return -1;
		}
		UINT uip=ServerAddr.sin_addr.S_un.S_addr;
		printf("收到信息：%s\t来自于:d.%d.%d,%d \n",buff,LOBYTE(uip),HIBYTE(uip),LOBYTE(HIWORD(uip)),HIBYTE(HIWORD(uip)));
	}
	return 0;
}