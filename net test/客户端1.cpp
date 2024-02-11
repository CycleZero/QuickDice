#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <stdio.h>
#include<iostream>

using namespace std;
int main()
{
    //初始化网络模块
    WSADATA wsaData;
    char buff[1024];
    memset(buff, 0, sizeof(buff));

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        printf("Failed to load Winsock");
        return -1;
    }

    SOCKADDR_IN addrSrv;
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(5099);
    addrSrv.sin_addr.S_un.S_addr = inet_addr("26.14.170.193");

    //创建套接字
    SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);
    if (SOCKET_ERROR == sockClient){
        printf("Socket() error:%d", WSAGetLastError());
        return -1;
    }

    //连接服务器
    if (connect(sockClient, (struct  sockaddr*)&addrSrv, sizeof(addrSrv)) == INVALID_SOCKET){
        printf("Connect failed:%d", WSAGetLastError());
        return-1;
    }
        
	do{
		 
    //发送数据
    char buffSend[1024];
    memset(buffSend,0,sizeof(buffSend));
    cin>>buffSend;
    send(sockClient, buffSend, strlen(buffSend) + 1, 0);
    printf("SendLength:%d\n", strlen(buffSend) + 1);
    
    //接收数据
	recv(sockClient, buff, sizeof(buff), 0);
	printf("Server:%s\n", buff);
	}while(buff[0]!='0'||strlen(buff)!=1);
	
	cout<<"程序退出"<<endl;

    //关闭
    closesocket(sockClient);
    WSACleanup();
    system("pause");
}
