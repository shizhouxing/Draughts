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

#ifndef GAME_H
#define GAME_H

#include "Common.h"

class Cell : public QLabel
{
    Q_OBJECT

public:
    explicit Cell(QColor background, int x, int y, QWidget *parent = 0);
    void setOccupier(int occupier, bool king = false);
    void setFocused(bool focused);
    void setHighlighted(bool highlighted);
    
signals:
    void clicked(int x, int y);    
    
private:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    QColor background;
    int x, y;
    int occupier;
    bool died;
    bool king;
    bool focused, highlighted, focusable;
    
    friend class Game;
    friend class Generator;
};

class Board : public Widget
{
    Q_OBJECT

public:
    explicit Board(QString state = "", QWidget *parent = 0);
    
private:
    int role;
    Cell *cell[10][10];
    
    friend class Game;
    friend class Generator;
};

class GameSidebarPlayerStatus : public QLabel
{
    Q_OBJECT

public:
    explicit GameSidebarPlayerStatus(int role, QWidget *parent = 0);    
    void setActive(bool active);    
    void setWinner();
    
private:
    void paintEvent(QPaintEvent *);    
    
    QPen pen;
    QBrush brush;
    QPixmap winner;
    
    friend class Game;
};

class GameSidebarPlayer : public Widget
{
    Q_OBJECT

public:
    explicit GameSidebarPlayer(QString name, QString ip, int role, QWidget *parent = 0);   
    
private:
    QLabel* renderText(QString text);
    
    GameSidebarPlayerStatus *status;    
    QLabel *name, *ip;
    
    friend class Game;
};

class GameSidebarButtons : public Widget
{
    Q_OBJECT

public:
    explicit GameSidebarButtons(QWidget *parent = 0);    
    
private:
    Button* renderButton(QString text);
    
    Button *buttonRequestDraw, *buttonResign, *buttonSound;    
    
    friend class Game;
};

class GameSidebar : public Widget
{
    Q_OBJECT
    
public:    
    explicit GameSidebar(QString name0, QString ip0, int role0, QString name1, QString ip1, int role1, QWidget *parent = 0);
    
private:
    GameSidebarPlayer *player[2];  
    GameSidebarButtons *buttons;
    
    friend class Game;
};

class Game : public QDialog
{
    Q_OBJECT
    
public:
    explicit Game(QString state, QString name0, QString ip0, QString name1, QString ip1, QWidget *parent = 0);
    void start();
    void lose(QString message = "");
    void win(QString message = "Congratulations!");  
    void draw();
    void move(bool informOpponent = true);  
    void move(QPoint S, QPoint E, bool informOpponent = false);    
    
private slots:
    void clickCell(int x, int y); 
    void requestDraw();
    bool resign();
    void switchSound(QString text);
    
signals:
    void sendMessage(QString message); 
    void checkMessages();
    
private:
    void closeEvent(QCloseEvent *event);
    void setFocus(int x, int y, bool mustJump = false);
    bool isEmpty(int x, int y);
    bool isOpponent(int x, int y);
    bool noObstruct(int x1, int y1, int x2, int y2);
    bool clearCorpses();
    void switchCurrent();
    void updateFocusable();
    bool promote(QPoint p);
    void playSound(QSoundEffect *sound);
    QSoundEffect* renderSound(QString url);
    int lengthEating(int x, int y);
    void dfs(int x, int y, int len, int maxStep);
    QList<QPoint> nextCells(int x, int y, bool mustJump = false);
    
    Board *board;
    GameSidebar *gameSidebar;
    int role, current;
    QPoint focus, lastMove;
    bool focusLocked;
    QList<QPoint> pathBuffer;
    
    QSoundEffect *soundMove, *soundEat, *soundWin, *soundLose;
    bool sound;
    
    int longestEating;
    bool nextTemp[10][10], vis[10][10];
    QList<QPoint> path;
    
    const int dx[4] = {-1, -1, 1, 1};
    const int dy[4] = {1, -1, 1, -1};    
};

#endif
