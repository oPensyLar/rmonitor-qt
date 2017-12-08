#include "openserial.h"
#include <QtDebug>


int oPenSerial::SendSignal()
{
    if (serial.isOpen() && serial.isWritable())
    {

        qDebug() << "[+] Sending payload ... " << signal;

        QByteArray output = QByteArray::number(signal);        
        serial.write(output);
        serial.waitForBytesWritten(2000);
        serial.waitForReadyRead(8000);
        
        inputSerial = serial.readAll();

        if(inputSerial.length()>0)
        {
          return 0;
        }
          
    }

        else
        {
            strErr = "[!] IsNotOpen || isNotWritiable (false)";
            return -1;
        }


    return -2;

}


int oPenSerial::SetPort(QString dev)
{

    this->portName = dev;

    return 0;
}


int oPenSerial::CloseDev()
{

    serial.close();
    return 0;

}


int oPenSerial::OpenDev()
{


    serial.setPortName(portName);    
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::HardwareControl);

    if(serial.open(QIODevice::ReadWrite)==false)
    {
        strErr = "[!] ERROR opening device ";
        strErr.append(this->portName);
        return -1;
    }

    return 0;

}
