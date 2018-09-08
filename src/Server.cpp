/***********************************************************************
    Draughts

    Copyright (c) 2017 Zhouxing Shi <zhouxingshichn@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

**********************************************************************/ 

#include "Server.h"

Server::Server(QString ip, int port)
{
    listenSocket = new QTcpServer;
    listenSocket->listen(QHostAddress(ip), port);
    qInfo("Server is listening at %s:%d...", ip.toStdString().c_str(), port);
    connect(listenSocket, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
}

void Server::acceptConnection()
{
    readWriteSocket = listenSocket->nextPendingConnection();
    emit connected(readWriteSocket->peerAddress().toString());
}

void Server::close()
{
    listenSocket->close();   
}

QTcpSocket* Server::socket()
{
    return readWriteSocket;
}
