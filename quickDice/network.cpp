#include "network.h"

network::network()
{

}

newserverb::newserverb()
{
    connect(&server,SIGNAL(newConnection()),this,SLOT(onNewconnection()));
    connect(&timer,SIGNAL(timeout()),this,SLOT(onTimeout()));
}

void newserverb::onNewconnection()
{
    QTcpSocket* client =  server.nextPendingConnection();
        //将和客户端通信的套接字保存到容器中
    tcpClientList.append(client);
        //当客户端给服务器发送消息时,client发送信号readyReaad,连接到接收聊天消息的槽函数
    connect(client,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
}
void newserverb::onReadyRead()
{
    for(int i=0;i<tcpClientList.size();i++)
    {
        if(tcpClientList.at(i)->bytesAvailable())
        {

        }
    }
}
