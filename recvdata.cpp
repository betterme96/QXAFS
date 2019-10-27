#include "recvdata.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstdio>
#include <QString>
#include <time.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <qdebug.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#define SIZE 200
#define PORT 8000

RecvData::RecvData(QObject *parent) : QObject(parent)
{

}


void RecvData::getData(std::string IP_SERVER,std::string filename)
{
    int socket_fd;
    socket_fd = socket(AF_INET,SOCK_STREAM,0);

    if (socket_fd < 0)
    {
        qDebug()<<"creat socket failed!";
        exit(1);
    }
    qDebug()<<"creat socket successed!";

    struct sockaddr_in server_addr;
    memset(&server_addr,0,sizeof (server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(IP_SERVER.c_str());
    server_addr.sin_port = htons(PORT);
    memset(&(server_addr.sin_zero),0,8);

    int res;
    res = ::connect(socket_fd,(struct sockaddr*)&server_addr, sizeof (server_addr));

    if(res < 0)
    {
        qDebug()<<"can not connect to server";
        //exit(-1);
    }
    qDebug()<< QString::fromStdString(IP_SERVER) <<"tcp socket connect successed!";

    //set start
    unsigned char start[2];
    start[0] = 0x00;
    start[1] = 0x01;

    if(send(socket_fd,start,2,0) != 2)
    {
        qDebug()<<"send start error";
        //exit(1);
    }
    qDebug()<<"send start";

    sleep(1);

    char fn[] = {0};
    strcpy(fn,filename.c_str());
    FILE *out = fopen(fn,"w");

    while (1) {
        unsigned char buf[SIZE];
        unsigned int curRecv = 0;
        unsigned int recvNo = 0;
        while(recvNo < SIZE)
        {
            curRecv = 0;
            curRecv = recv(socket_fd, buf+recvNo, SIZE-recvNo, 0);
            if(curRecv > 0)
                recvNo += curRecv;
            else if (curRecv < 0) {
                qDebug()<<"cannot recv any byte!";
                //exit(-1);
            }
        }
        fwrite(buf,recvNo,1,out);
        fflush(out);
    }

    fclose(out);
    std::cout<< "finish!"<<endl;
    close(socket_fd);
}
