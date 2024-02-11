#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <WS2tcpip.h>
#include <iostream>
using namespace std;
#define PORT 9999

DWORD WINAPI ThreadFun(LPVOID lpThreadParameter);
volatile int newyear=0;
int main() 
{
	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD(2, 2);
	if (WSAStartup(wVersionRequested, &wsaData) != 0)
	{
		cout << "����winsock.dllʧ��!" << endl;
		return 0;
	}

	SOCKET  sock_server;
	sock_server = socket(AF_INET, SOCK_STREAM, 0);

	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.S_un.S_addr=inet_addr("172.18.55.237");
	if (SOCKET_ERROR == bind(sock_server, (SOCKADDR*)&addr, sizeof(sockaddr_in)))
	{
		cout << "��ַ��ʧ��:" << WSAGetLastError() << endl;
		closesocket(sock_server);
		WSACleanup();
		return 0;
	}

	listen(sock_server, 0);

	while (1) 
	{
		sockaddr_in addrClient;
		int len = sizeof(sockaddr_in);

		SOCKET con = accept(sock_server, (SOCKADDR*)&addrClient, &len);
		if (con != INVALID_SOCKET) 
		{

			HANDLE hThread = CreateThread(NULL, 0, ThreadFun, (LPVOID)con, 0, NULL);
			CloseHandle(hThread);
		}
	}
	closesocket(sock_server);
	WSACleanup();
	return 0;
}

DWORD WINAPI ThreadFun(LPVOID lpThreadParameter) 
{

	SOCKET sock = (SOCKET)lpThreadParameter;
	cout << "�ɹ���" << sock << "��������!" << endl;
	char buf1[]="�ɹ����������������";
	send(sock, buf1, sizeof(buf1), 0);
	char msgbuffer1[]="�������";
	while (1)
	{
		char msgbuffer[1000];
		
		int ret = recv(sock, msgbuffer, sizeof(msgbuffer), 0);
				if(ret == SOCKET_ERROR || ret == 0)
				{
					cout << sock << "�Ͽ�������!" << endl;
					break;
				}
				else cout << sock << "  ˵: " << msgbuffer << endl;
		if (strcmp(msgbuffer, "newyear\0") == 0)
				{
					newyear=1;
				}
				else
				{
					if (strcmp(msgbuffer, "newyearoff\0") == 0)
					{
						newyear=0;
					}
				}
				
				
		int size;
		
		if(newyear==1)
		{
			 size = send(sock, msgbuffer1, sizeof(msgbuffer1), 0);
		}
		else
		{
			 size = send(sock, msgbuffer, sizeof(msgbuffer), 0);
		}
//		msgbuffer[999] = { 0 };
		printf("��������%d��������:", sock);
		cout<<msgbuffer<<endl;
//		cin.getline(msgbuffer, sizeof(msgbuffer));
		
		
		if (size == SOCKET_ERROR || size == 0)
		{
			cout << "������Ϣʧ��:" << WSAGetLastError() << endl;
			return 0;
		}
		else cout << "��Ϣ���ͳɹ�!" << endl;
		

		
		
	}
	return 0;
}
