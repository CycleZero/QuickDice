#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <WS2tcpip.h>
#include <iostream>
using  namespace std;

#define PORT 9999
int  main() 
{
	//???winsock2.DLL
	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD(2, 2);
	if (WSAStartup(wVersionRequested, &wsaData) != 0)
	{
		cout << "winsock.dllʧ��!" << endl;
		system("pause");
		return 0;
	}
	//?????
	SOCKET  sock_client; 
	sock_client = socket(AF_INET, SOCK_STREAM, 0);
	//?????
	sockaddr_in   addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.S_un.S_addr=inet_addr("121.199.32.99");
//	inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);//?????????
	int len = sizeof(addr);
	if (connect(sock_client, (struct  sockaddr*)&addr, len) == SOCKET_ERROR) {
		cout << "����ʧ��:" << WSAGetLastError() << endl;
		system("pause");
		return 0;
	}
	char buf1[1024];
	recv(sock_client, buf1, sizeof(buf1), 0);
	cout<<buf1<<endl;
	//??????,???????????
	while (1)
	{
		//????????
		char msgbuffer[1000] = { 0 };
		
		cout << "���͸�������:" << endl;
				cin.getline(msgbuffer, sizeof(msgbuffer));
				if (strcmp(msgbuffer, "end\0") == 0)
				{
					cout << "�ر�����!" << endl;
					break;
				}
				int ret = send(sock_client, msgbuffer, sizeof(msgbuffer), 0);
				if (ret == SOCKET_ERROR || ret == 0)
				{
					cout << "����ʧ��:" << WSAGetLastError() << endl;
					break;
				}
				else cout << "���ͳɹ�!" << endl;
		
		
		msgbuffer[999] =  0 ;
		
		int size = recv(sock_client, msgbuffer, sizeof(msgbuffer), 0);
		if (strcmp(msgbuffer, "end\0") == 0)
		{
			cout << "������Ѿ��ر�����!" << endl;
			break;
		}
		if (size < 0)
		{
			cout << "������Ϣʧ��:" << WSAGetLastError() << endl;
			break;
		}
		else if (size == 0)
		{
			cout << "�Է��Ѿ��ر�����" << endl;
			break;
		}
		else cout << "The message from Server:" << msgbuffer << endl;

		//???????????????
		
		
		
		
	}
	closesocket(sock_client);
	WSACleanup();
	return 0;
}
