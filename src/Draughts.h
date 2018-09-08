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

#ifndef DRAUGHTS_H
#define DRAUGHTS_H

#include "Common.h"
#include "Landing.h"
#include "Server.h"
#include "Client.h"
#include "Connection.h"
#include "Game.h"
#include "Generator.h"

class Draughts : public QDialog
{
    Q_OBJECT
    
public:
    explicit Draughts(QWidget *parent = 0);
    
private slots:
    void createGame(QString nickname, QString ip, int port, QString stateMe, QString stateOpponent);     
    void joinGame(QString nickname, QString ip, int port);
    void handleMessage(QString message);
    void clientJoined(QString ip);
    void initGame();
    void startGame(QString state);    
    void returnToHome();
    
private:      
    QStackedWidget *stackedWidget;
    Landing *landing;
    PendingMsg *pendingMsg;
    Server *server;
    Client *client;
    Connection *connection;
    Game *game;
    Generator *generator;
    
    QString nickname[2], ip[2], stateMe, stateOpponent;
    int side; // whether is server or client
};

#endif
