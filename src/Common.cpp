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

#include "Common.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
}

// to enable stylesheet for the widget
void Widget::paintEvent(QPaintEvent *)
{
    QStyleOption* option = new QStyleOption;
    option->init(this);
    style()->drawPrimitive(QStyle::PE_Widget, option, new QPainter(this), this);
}    

Button::Button(QWidget *parent) :
    QLabel(parent)
{
    setStyleSheet("border-radius: 8px;"
                  "background: " + Config::Colors::PRIMARY + ";"
                  "color: white;");
    setAlignment(Qt::AlignCenter);
    setCursor(Qt::PointingHandCursor);
}

Button::Button(const QString &text, QWidget *parent) :
    Button(parent)
{
    setText(text);
}

void Button::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        emit clicked(text());
}

void MsgHandler::handler(QtMsgType type, const QMessageLogContext&, const QString &msg)
{
    if (type >= Config::MSG_LEVEL)
    {
        const QString types[] = {"Debug", "Warning", "Critical", "Fatal", "Info"};
        fprintf(stderr, "%s: %s\n", types[type].toStdString().c_str(), msg.toStdString().c_str());
    }
}    
