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

#include "Connection.h"

Connection::Connection(QTcpSocket *socket)
{
    this->socket = socket;
    connect(socket, SIGNAL(readyRead()), this, SLOT(recvMessage()));    
}

void Connection::recvMessage()
{
    QString msg = socket->readAll();
    for (int i = 0; i < msg.size(); ++i)
        if (msg[i] == '\n') msg[i] = ' ';
    qInfo("READ %s", msg.toStdString().c_str());
    emit receivedMessage(msg);
}

void Connection::sendMessage(QString message)
{
    qInfo("WRITE %s", message.toStdString().c_str());
    socket->write((message + "\n").toStdString().c_str());
}

// in case of missed messages
void Connection::checkReadable()
{
    if (socket->canReadLine()) 
        recvMessage();
}
