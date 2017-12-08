#include "openmonitorrig.h"

oPenMonitorHost::oPenMonitorHost(QObject *parent) : QObject(parent)
{
    this->up = false;
}



void oPenMonitorHost::connected()
{
    
}



void oPenMonitorHost::disconnected()
{
    
}




void oPenMonitorHost::bytesWritten(qint64 bytes)
{
    
}



void oPenMonitorHost::readyRead()
{
    
}




int oPenMonitorHost::error(QAbstractSocket::SocketError)
{

    this->errString = socket->errorString();

    return 0;
}




int oPenMonitorHost::CheckStatus()
{

    this->socket = new QTcpSocket(this);

    connect(this->socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(this->socket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(error(QAbstractSocket::SocketError)));
    connect(this->socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(this->socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(this->socket, SIGNAL(readyRead()),this, SLOT(readyRead()));

     this->socket->connectToHost(this->host, this->port);



     if(!this->socket->waitForConnected(5000))
     {
         this->errString = socket->errorString();
         return 1;
     }



     this->socket->close();
     //delete(this->socket);
     return 0;
}
