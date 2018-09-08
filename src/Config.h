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

#ifndef CONFIG_H
#define CONFIG_H

#include <QApplication>
#include <QDialog>
#include <QLabel>
#include <QLayout>
#include <QTimer>
#include <QKeyEvent>
#include <QPushButton>
#include <QStyleOption>
#include <QPainter>
#include <QAction>
#include <QDebug>
#include <QMessageBox>
#include <QStackedWidget>
#include <QtNetwork>
#include <QSoundEffect>
#include <QFileDialog>

namespace Config
{
    const int MSG_LEVEL = 2;
    
    namespace Colors
    {
        const QColor CELL_LIGHT = QColor(206, 228, 242);
        const QColor CELL_DARK = QColor(68, 148, 170);
        const QColor CELL_NEXT = QColor(116, 255, 139);
        const QColor PIECE_LIGHT = QColor(245, 245, 245);
        const QColor PIECE_DARK = Qt::black;
        const QColor PIECE_FOCUSED = QColor(224, 102, 105);
        const QString PRIMARY = "#4494aa";    
        const QString DANGEROUS = "#e06669";        
        const QString BACKGROUND = "#fafcfc"; 
        const QString BORDER = "#09afdf";
    }
}

#endif
