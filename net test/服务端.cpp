#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<winsock2.h>
#include<iostream>

using namespace std;
int main()
{
	
	WSADATA data;
	int ret=WSAStartup(MAKEWORD(2,2),&data);
	if(ret)
	{
		cout<<"error"<<endl;
		WSACleanup();
		return -1;
	}
	SOCKET sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock==-1)
	{
		cout<<"�����׽���ʧ��"<<endl;
		WSACleanup();
		return -1; 
	}
	sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(9999);
	addr.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
	ret=bind(sock,(sockaddr*)&addr,sizeof(addr));
	if(ret==-1)
	{
		cout<<"�󶨶˿�ʧ��"<<endl;
		WSACleanup();
		return -1;
	}
	ret=listen(sock,5);
	if(ret==-1)
	{
		cout<<"�����׽���ʧ��"<<endl;
		WSACleanup();
		return -1;
	}
	sockaddr addrCli;
	int len=sizeof(addrCli);
	SOCKET sockCli=accept(sock,&addrCli,&len);
	if(sockCli==-1)
	{
		cout<<"���տͻ�������ʧ��"<<endl;
		WSACleanup();
		return -1;
	}
	char message[0xFF]="���Ƿ�����";
	ret=send(sockCli,message,strlen(message),0);
	if(ret==-1)
	{
		cout<<"������Ϣʧ��"<<endl;
		WSACleanup();
		return -1;
	}
	ret=recv(sockCli,message,0xFF,0);
	if(ret<=0)
	{
		cout<<"���տͻ�������ʧ��"<<endl;
		WSACleanup();
		return -1;
	}
	WSACleanup();
	
		
	
	
	
	
	
	return 0;
	
	
}
