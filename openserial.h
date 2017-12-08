#ifndef OPENSERIAL_H_
#define OPENSERIAL_H_

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

class oPenSerial : public QObject
{

Q_OBJECT

private:
	QString portName;


public:
	int signal;
	QByteArray inputSerial;
	QString strErr;

	int SetPort(QString dev);
    int OpenDev();
    int CloseDev();
    int SendSignal();

private:
	QSerialPort serial;

private slots:


};


#endif /*OPENSERIAL_H_*/
