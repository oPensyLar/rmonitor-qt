#ifndef OPENMONITORRIG_H
#define OPENMONITORRIG_H

#include <QObject>
#include <QProcess>
#include <QTcpSocket>
#include <QAbstractSocket>


class oPenMonitorHost : public QObject
{
    Q_OBJECT

public:


    QString host;
    int port;
    int signal;
    int reboots;
    bool up;

    QString errString;

    explicit oPenMonitorHost(QObject *parent = nullptr);
    int CheckStatus();

signals:

public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
    int error(QAbstractSocket::SocketError);

private:
    QTcpSocket *socket;
};

#endif // OPENMONITORRIG_H
