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

#ifndef COMMON_H
#define COMMON_H

#include "Config.h"

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);
    
protected:
    void paintEvent(QPaintEvent*);    
};

// button
class Button : public QLabel 
{
    Q_OBJECT
    
public:
    explicit Button(QWidget *parent = 0);
    explicit Button(const QString &text, QWidget *parent = 0);
    
signals:
    void clicked(const QString &text); 
    
protected:
    void mousePressEvent(QMouseEvent *event);    
};

// message handler
class MsgHandler 
{
public:    
    static void handler(QtMsgType type, const QMessageLogContext&, const QString &msg);
};

#endif // COMMON_H
