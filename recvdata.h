#ifndef RECVDATA_H
#define RECVDATA_H

#include <QObject>

class RecvData : public QObject
{
    Q_OBJECT
public:
    explicit RecvData(QObject *parent = nullptr);
    void getData(std::string IP_SERVER,std::string filename);

signals:

public slots:
};

#endif // RECVDATA_H
