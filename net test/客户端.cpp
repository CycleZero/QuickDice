#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<winsock2.h>
#include<iostream>

using namespace std;
int main() {
	WSADATA data;
	/*
	int ret = WSAStartup(MAKEWORD(2, 2), &data);
	if (ret) {
		cout << "��ʼ���������" << endl;
		WSACleanup();
		return -1;
	}
	*/
	int ret;
	
	
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9999);
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	ret = connect(sock, (sockaddr*)&addr, sizeof(addr));
	if (ret == -1) {
		WSACleanup();
		cout << "���ӷ�����ʧ��" << endl;
		return -1;
	}
	char buf[0xFF]{};
	ret=recv(sock,buf,sizeof(buf),0);
	if (ret <= 0) {
		WSACleanup();
		cout << "���ܷ���������ʧ��" << endl;
		return -1;
	}
	cout << "������:" << buf << endl;

	ret=send(sock,buf,ret,0); 
	if (ret <= 0) {
		WSACleanup();
		cout << "���ͷ���������ʧ��" << endl;
		return -1;
	}
	WSACleanup();
}
