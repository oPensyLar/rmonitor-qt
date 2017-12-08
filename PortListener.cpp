#include "PortListener.h"
#include <QtDebug>



PortListener::PortListener()
{

    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();


    foreach (QextPortInfo info, ports) 
    {
        qDebug() << "port name:"       << info.portName;
        qDebug() << "friendly name:"   << info.friendName;
        qDebug() << "physical name:"   << info.physName;
        qDebug() << "enumerator name:" << info.enumName;
        qDebug() << "vendor ID:"       << info.vendorID;
        qDebug() << "product ID:"      << info.productID;
    }


    exit(0);

    

    this->port = new QextSerialPort(portName, QextSerialPort::EventDriven);
    port->setBaudRate(BAUD9600);
    port->setFlowControl(FLOW_OFF);
    port->setParity(PAR_NONE);
    port->setDataBits(DATA_8);
    port->setStopBits(STOP_2);

    if (port->open(QIODevice::ReadWrite) == true) 
    {
        connect(port, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
        connect(port, SIGNAL(dsrChanged(bool)), this, SLOT(onDsrChanged(bool)));


        if (!(port->lineStatus() & LS_DSR))
        {
            qDebug() << "warning: device is not turned on";
        }

        


        qDebug() << "listening for data on" << port->portName();
    }

        else
        {

            qDebug() << "device failed to open:" << port->errorString();
        }
}



void PortListener::onReadyRead()
{
    QByteArray bytes;
    int a = port->bytesAvailable();
    bytes.resize(a);
    port->read(bytes.data(), bytes.size());


    qDebug() << "bytes read:" << bytes.size();    
    qDebug() << "bytes:" << bytes;

}



void PortListener::onDsrChanged(bool status)
{
    if (status)
        qDebug() << "device was turned on";
    else
        qDebug() << "device was turned off";
}
