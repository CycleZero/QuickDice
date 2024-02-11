#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include<string>
#include <cstring>
#include<iostream>
#include <WS2tcpip.h>
#define PORT 65432
using namespace std;


int main()
{
    WSADATA wsaData;
    int port = 5099;

    char buf[] = "Server: hello, I am a server.....";
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        printf("Failed to load Winsock");
        return -1;
    }
    

    //创建用于监听的套接字
    SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);

    SOCKADDR_IN addrSrv;
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(port); //1024以上的端口号
    addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

    int retVal = bind(sockSrv, (LPSOCKADDR)&addrSrv, sizeof(SOCKADDR_IN));
    if (retVal == SOCKET_ERROR){
        printf("Failed bind:%d\n", WSAGetLastError());
        return -1;
    }

    if (listen(sockSrv, 10) == SOCKET_ERROR){
        printf("Listen failed:%d", WSAGetLastError());
        return -1;
    }

    SOCKADDR_IN addrClient;
    int len = sizeof(SOCKADDR);

//等待客户请求到来    
    SOCKET sockConn = accept(sockSrv, (SOCKADDR *)&addrClient, &len);
    if (sockConn == SOCKET_ERROR){
        printf("Accept failed:%d", WSAGetLastError());
        //break;
    }

    printf("Accept client IP:[%s]\n", inet_ntoa(addrClient.sin_addr));

	
	
    char recvBuf[1024];
    do{
    //接收数据
    memset(recvBuf, 0, sizeof(recvBuf));
    recv(sockConn, recvBuf, sizeof(recvBuf), 0);
    printf("%s\n", recvBuf);
	
	
	//发送数据
	int iSend = send(sockConn, recvBuf, sizeof(recvBuf), 0);
	if (iSend == SOCKET_ERROR){
	    printf("send failed");
		// break;
	}
    }while(strlen(recvBuf)!=1||recvBuf[0]!='0');
	
	
	cout<<"程序退出"<<endl;
    closesocket(sockConn);
    closesocket(sockSrv);
    WSACleanup();
    system("pause");
}
