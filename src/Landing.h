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

#ifndef LANDING_H
#define LANDING_H

#include "Common.h"
#include "Generator.h"

class LandingButtons : public Widget
{
    Q_OBJECT
    
public:
    explicit LandingButtons(QWidget *parent = 0);    
    
private:
    Button* renderButton(const QString &text);
    Button *buttonCreate, *buttonJoin, *buttonAbout, *buttonQuit;
    
    friend class Landing;
};

class Landing : public QDialog
{
    Q_OBJECT
    
public:
    explicit Landing(QWidget *parent = 0);
    
private slots:
    void clicked(const QString &text);

signals:
    void createGame(QString nickname, QString ip, int port, QString stateMe, QString stateOpponent);
    void joinGame(QString nickname, QString ip, int port);
    
private:
    QLabel* renderTitle();    
    
    LandingButtons *buttons;
    Generator *generator;
};

class PendingMsg : public QDialog
{
    Q_OBJECT

public:
    explicit PendingMsg(QWidget *parent = 0);    
    void setIp(QString ip);
    void setPort(int port);
    
private slots:
    void clicked();

signals:
    void canceled();    
    
private:
    void renderInfo();
    
    QLabel *info;
    QString ip;
    int port;    
};

#endif // LANDING_H
