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

#include "Game.h"

Cell::Cell(QColor background, int x, int y, QWidget *parent) :
    QLabel(parent)
{
    this->background = background;
    this->x = x;
    this->y = y;
    this->occupier = -1;
    this->king = false;
    this->focused = false;
    this->highlighted = false;
    this->died = false;
}

void Cell::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(highlighted ? Config::Colors::CELL_NEXT : background));
    painter.drawRect(0, 0, width(), height());
    if (occupier != -1) // draw piece
    {
        const int margin = 7;
        const int stroke = 5;
        if (focused)
            painter.setPen(QPen(Config::Colors::PIECE_FOCUSED, stroke));
        if (occupier) 
            painter.setBrush(QBrush(Config::Colors::PIECE_LIGHT));
        else
            painter.setBrush(QBrush(Config::Colors::PIECE_DARK));
        painter.drawEllipse(margin, margin, width() - margin * 2, height() - margin * 2);
        if (king)
        {
            const int margin = 14;
            painter.drawPixmap(margin, margin, width() - margin * 2, height() - margin * 2,
                               occupier ? QPixmap(":/icons/king-light.png") : QPixmap(":/icons/king-dark.png"));
        }
    }
}

void Cell::setOccupier(int occupier, bool king)
{
    this->occupier = occupier;
    this->king = king;
    this->focused = this->highlighted = false;
    update();
}

void Cell::setFocused(bool focused)
{
    this->focused = focused;
    update();
}

void Cell::setHighlighted(bool highlighted)
{
    this->highlighted = highlighted;
    update();
}

void Cell::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        emit clicked(x, y);
}

Board::Board(QString state, QWidget *parent) : 
    Widget(parent)
{
    QTextStream in(&state);
    int current;
    
    if (state != "")
        in >> (this->role) >> current;
    
    QGridLayout *layout = new QGridLayout;    
    
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
        {
            cell[i][j] = new Cell(((i + j) % 2) ? Config::Colors::CELL_DARK : Config::Colors::CELL_LIGHT, i, j);
            layout->addWidget(cell[i][j], i, j);
        }
    
    if (state != "")
    {
        for (int i = 0; i < 10; ++i)
            for (int j = 0; j < 10; ++j)
            {
                int occupier, king;
                in >> occupier >> king;
                cell[i][j]->setOccupier(occupier, king);
            }
    }
                
    layout->setSpacing(0);
    layout->setMargin(4);
    setLayout(layout);
    
    setStyleSheet("border: 4px solid " + Config::Colors::BORDER + ";");
    
    setFixedWidth(600);
    setFixedHeight(600);
}

GameSidebarPlayerStatus::GameSidebarPlayerStatus(int role, QWidget *parent) :
    QLabel(parent)
{
    pen = Qt::NoPen;
    if (role == 0)
        brush = QBrush(Config::Colors::PIECE_DARK);
    else
        brush = QBrush(Config::Colors::PIECE_LIGHT);
    setFixedHeight(100);  
}

void GameSidebarPlayerStatus::setActive(bool active)
{
    if (!active)
        pen = Qt::NoPen;
    else
        pen = QPen(Config::Colors::PIECE_FOCUSED, 5);
    update();
}

void GameSidebarPlayerStatus::setWinner()
{        
    if (brush == QBrush(Config::Colors::PIECE_DARK))
        winner = QPixmap(":/icons/king-dark.png");
    else
        winner = QPixmap(":/icons/king-light.png");
    update();
}

void GameSidebarPlayerStatus::paintEvent(QPaintEvent *)
{
    const int r = 30;
    const int rWinner = 20;  
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);    
    painter.setBrush(brush);
    painter.setPen(pen);
    painter.drawEllipse(QPoint(width() / 2, height() / 2), r, r);
    painter.drawPixmap(width() / 2 - rWinner, height() / 2 - rWinner, 2 * rWinner, 2 * rWinner, winner);
}

QLabel* GameSidebarPlayer::renderText(QString text)
{
    QLabel *widget = new QLabel(text);
    widget->setAlignment(Qt::AlignCenter);
    widget->setStyleSheet("color: white;");
    return widget;
}

GameSidebarPlayer::GameSidebarPlayer(QString name, QString ip, int role, QWidget *parent) :
    Widget(parent)
{
    status = new GameSidebarPlayerStatus(role);
    this->name = renderText(name);
    this->ip = renderText(QString("IP: %1").arg(ip));
    
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(status);
    layout->addWidget(this->name);
    layout->addWidget(this->ip);
    
    layout->setSpacing(0);
    layout->setMargin(4);
    
    setLayout(layout);
    
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setObjectName("GameSidebarPlayer");
    setStyleSheet("background: " + Config::Colors::PRIMARY + ";");
}

Button* GameSidebarButtons::renderButton(QString text)
{
    Button *button = new Button(text);
    button->setStyleSheet(button->styleSheet() + 
                          "font-size: 18px;"
                          "padding: 10px 0;");
    return button;
}

GameSidebarButtons::GameSidebarButtons(QWidget *parent) : 
    Widget(parent)
{
    buttonRequestDraw = renderButton("Request Draw");
    buttonResign = renderButton("Resign");
    buttonSound = renderButton("Sound: On");
    
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addStretch();
    layout->addWidget(buttonRequestDraw);
    layout->addWidget(buttonResign);
    layout->addWidget(buttonSound);
    layout->addStretch();
    layout->setContentsMargins(20, 4, 20, 4);
    layout->setSpacing(10);
    setLayout(layout);
    
    setObjectName("GameSidebarButtons");
    setStyleSheet("#GameSidebarButtons{"
                  "border-top: 4px solid " + Config::Colors::BORDER + ";" +
                  "border-bottom: 4px solid " + Config::Colors::BORDER + ";"
                  "}");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

GameSidebar::GameSidebar(QString name0, QString ip0, int role0, QString name1, QString ip1, int role1, QWidget *parent) :
    Widget(parent)
{
    player[0] = new GameSidebarPlayer(name0, ip0, role0);
    player[1] = new GameSidebarPlayer(name1, ip1, role1);
    buttons = new GameSidebarButtons();
    
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(player[0]);
    layout->addWidget(buttons);
    layout->addWidget(player[1]);
    
    layout->setSpacing(0);
    layout->setMargin(4);
    
    setLayout(layout);
    
    setObjectName("GameSidebar");
    setStyleSheet("#GameSidebar{"
                  "border: 4px solid " + Config::Colors::BORDER + ";"
                  "}");    
    setFixedWidth(200);  
}

Game::Game(QString state, QString name0, QString ip0, QString name1, QString ip1, QWidget *parent) : 
    QDialog(parent)
{
    QTextStream in(&state);
    in >> (this->role) >> current;
    
    board = new Board(state);
    gameSidebar = new GameSidebar(name0, ip0, 1 - role, name1, ip1, role);
    
    sound = true;
    soundMove = renderSound(":/sounds/move.wav");
    soundEat = renderSound(":/sounds/eat.wav");
    soundWin = renderSound(":/sounds/win.wav");
    soundLose = renderSound(":/sounds/lose.wav");
    
    connect(gameSidebar->buttons->buttonRequestDraw, SIGNAL(clicked(QString)), this, SLOT(requestDraw()));
    connect(gameSidebar->buttons->buttonResign, SIGNAL(clicked(QString)), this, SLOT(resign()));
    connect(gameSidebar->buttons->buttonSound, SIGNAL(clicked(QString)), this, SLOT(switchSound(QString)));
    
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            connect(board->cell[i][j], SIGNAL(clicked(int,int)), this, SLOT(clickCell(int, int)));
    
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(board);
    layout->addWidget(gameSidebar);
    
    layout->setMargin(10);
    layout->setSpacing(10);
     
    setLayout(layout);
    
    setWindowFlags(Qt::Window 
                     | Qt::WindowSystemMenuHint
                     | Qt::WindowMinimizeButtonHint
                     | Qt::WindowCloseButtonHint); 
    setStyleSheet("QDialog { background: " + Config::Colors::BACKGROUND + "; }");   
    setFixedWidth(830);
}

void Game::start()
{
    qInfo("Game started: role = %d", role);
    
    current ^= 1;
    focus = QPoint(-1, -1);
    focusLocked = false;
    pathBuffer.clear();  
    switchCurrent();
    show();
}

bool Game::isEmpty(int x, int y)
{
    if (x < 0 || y < 0 || x >= 10 || y >= 10) return false;
    return board->cell[x][y]->occupier == -1;
}

bool Game::isOpponent(int x, int y)
{
    if (x < 0 || y < 0 || x >= 10 || y >= 10) return false;
    return board->cell[x][y]->occupier == 1 - role;    
}

void Game::dfs(int x, int y, int len, int maxStep)
{
    if (len > longestEating)
    {
        longestEating = len;
        memset(nextTemp, 0, sizeof(nextTemp));
        nextTemp[path[0].x()][path[0].y()] = true;
    }
    else if (len == longestEating && path.size())
        nextTemp[path[0].x()][path[0].y()] = true;
    
    for (int k = 0; k < 4; ++k)
        for (int step = 1; step <= maxStep; ++step)
        {
            int xx = x + dx[k] * step;
            int yy = y + dy[k] * step;
            
            if (xx < 0 || yy < 0 || xx >= 10 || yy >= 10) break;
            if (board->cell[xx][yy]->occupier != -1)
            {
                if (board->cell[xx][yy]->occupier == role) break;
                if (vis[xx][yy] || board->cell[xx][yy]->died) break;
                
                for (int nextStep = 1; nextStep <= maxStep; ++nextStep)
                {
                    int xxx = xx + dx[k] * nextStep;
                    int yyy = yy + dy[k] * nextStep;
                    if (xxx < 0 || yyy < 0 || xxx >= 10 || yyy >= 10) break;
                    if (board->cell[xxx][yyy]->occupier != -1) break;
                    if (vis[xxx][yyy]) break;
                    vis[xx][yy] = true;
                    path.push_back(QPoint(xxx, yyy));
                    dfs(xxx, yyy, len + 1, maxStep);
                    path.pop_back();
                    vis[xx][yy] = false;
                }
                break;
            }
    }
}

QList<QPoint> Game::nextCells(int x, int y, bool mustJump)
{
    QList<QPoint> res;
    res.clear();
    
    lengthEating(x, y);
    
    if (longestEating)
    {
        for (int i = 0; i < 10; ++i)
            for (int j = 0; j < 10; ++j)
                if (nextTemp[i][j])
                    res.push_back(QPoint(i, j));
    }
    
    if (!mustJump && !res.size())
    {
        int maxStep = board->cell[x][y]->king ? 9 : 1;
        for (int k = 0; k < ((board->cell[x][y]->king) ? 4 : 2); ++k)
            for (int step = 1; step <= maxStep; ++step)
            {
                int xx = x + dx[k] * step;
                int yy = y + dy[k] * step;
                if (xx < 0 || yy < 0 || xx >= 10 || yy >= 10) break;
                if (board->cell[xx][yy]->occupier != -1) break;
                res.push_back(QPoint(xx, yy));
            }
    }
    return res;
}

int Game::lengthEating(int x, int y)
{
    longestEating = 0;
    path.clear();
    memset(vis, 0, sizeof(vis));
    int maxStep = board->cell[x][y]->king ? 9 : 1;
    int occupier = board->cell[x][y]->occupier;
    board->cell[x][y]->occupier = -1;
    dfs(x, y, 0, maxStep);
    board->cell[x][y]->occupier = occupier;
    return longestEating;
}

void Game::updateFocusable()
{
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            board->cell[i][j]->focusable = false;
    int length[10][10], maxLength = 0;
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            if (board->cell[i][j]->occupier == role)
            {
                length[i][j] = lengthEating(i, j);
                maxLength = std::max(maxLength, length[i][j]);
            }
    bool hasNext = false;
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            if (board->cell[i][j]->occupier == role && length[i][j] == maxLength)
            {
                board->cell[i][j]->focusable = true;
                hasNext = true;
            }
    if (!hasNext)
        lose();
}

void Game::setFocus(int x, int y, bool mustJump)
{
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            board->cell[i][j]->setFocused(false);    
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            board->cell[i][j]->setHighlighted(false);
    if (x != -1)
    {
        QList<QPoint> next = nextCells(x, y, mustJump);
        for (int i = 0; i < next.size(); ++i)
            board->cell[next[i].x()][next[i].y()]->setHighlighted(true);
        if (mustJump && !next.size())
        {
            focus = QPoint(-1, -1);
            return;
        }
        else
            board->cell[x][y]->setFocused(true);
                
    }
    focus = QPoint(x, y);
}

bool Game::noObstruct(int x1, int y1, int x2, int y2)
{
    int dx = (x1 < x2) ? 1 : -1;
    int dy = (y1 < y2) ? 1 : -1;
    for (int x = x1 + dx; x != x2; x += dx)
        for (int y = y1 + dy; y != y2; y += dy)
            if (board->cell[x][y]->occupier != -1)
                return false;
    return true;
}

void Game::clickCell(int x, int y)
{
    if (current != role) return;
    if (board->cell[x][y]->occupier != -1)
    {
        if (board->cell[x][y]->occupier != role) return;
        if (!focusLocked)
        {
            if (board->cell[x][y]->focusable)
                setFocus(x, y);
            else
                setFocus(-1, -1);
        }
    }
    else
    {
        if (focus == QPoint(-1, -1)) return;
        if (!board->cell[x][y]->highlighted) 
        {
            if (!focusLocked)
                setFocus(-1, -1);
        }
        else
        {
            move(focus, QPoint(x, y), true);       
            if (noObstruct(focus.x(), focus.y(), x, y))
            {
                setFocus(-1, -1);
                move();             
            }
            else
            {
                setFocus(x, y, true);
                if (focus == QPoint(-1, -1))
                    move();
                else
                {
                    playSound(soundMove);
                    focusLocked = true;
                }
            }
        }
    }
}

bool Game::promote(QPoint p)
{
    if (board->cell[p.x()][p.y()]->king)
        return false;
    if (p.x() == (board->cell[p.x()][p.y()]->occupier != role) * 9)
    {
        board->cell[p.x()][p.y()]->setOccupier(board->cell[p.x()][p.y()]->occupier, true);
        return true;
    }
    else
        return false;
}

void Game::move(QPoint S, QPoint E, bool informOpponent)
{
    int dx = (S.x() < E.x()) ? 1 : -1;
    int dy = (S.y() < E.y()) ? 1 : -1;
    for (int x = S.x() + dx; x != E.x(); x += dx)
        for (int y = S.y() + dy; y != E.y(); y += dy)
            if (board->cell[x][y]->occupier != -1)
                board->cell[x][y]->died = true;
    
    board->cell[E.x()][E.y()]->setOccupier(board->cell[S.x()][S.y()]->occupier, board->cell[S.x()][S.y()]->king);
    board->cell[S.x()][S.y()]->setOccupier(-1, 0);
    
    lastMove = E;
    
    if (!informOpponent)
        playSound(soundMove);    
    else
    {
        QString message;
        QTextStream out(&message);
        out << "move " << S.x() << " " << S.y() << " " << E.x() << " " << E.y() << "\n";
        emit sendMessage(message);
    }
}

void Game::move(bool informOpponent)
{
    int t1 = promote(lastMove);
    int t2 = clearCorpses();
    if (t1 || t2)
    {
        if (informOpponent)
            playSound(soundEat);
    }
    else
    {
        if (informOpponent)
            playSound(soundMove);
    }
    switchCurrent();
    if (informOpponent)
        emit sendMessage("endMove");
}

void Game::switchCurrent()
{
    current ^= 1;
    focusLocked = false;
    for (int i = 0; i < 2; ++i)
        gameSidebar->player[i]->status->setActive(current ^ i ^ role);
    updateFocusable();
}

bool Game::clearCorpses()
{
    bool hasDied = false;
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            if (board->cell[i][j]->died)
            {
                board->cell[i][j]->setOccupier(-1);
                board->cell[i][j]->died = false;
                hasDied = true;
            }
    return hasDied;
}

void Game::lose(QString message)
{
    if (current == -1) return;
    current = -1;
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
        {
            board->cell[i][j]->setFocused(false);
            board->cell[i][j]->setHighlighted(false);
        }    
    emit sendMessage("finish");    
    for (int k = 0; k < 2; ++k)
        gameSidebar->player[k]->status->setActive(false);
    gameSidebar->player[0]->status->setWinner();    
    playSound(soundLose);
    QMessageBox::information(this, "You lose", QString("<h2>You lose.</h2><p>%1</p>").arg(message));
}

void Game::win(QString message)
{
    if (current == -1) return;
    current = -1;
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
        {
            board->cell[i][j]->setFocused(false);
            board->cell[i][j]->setHighlighted(false);
        }    
    for (int k = 0; k < 2; ++k)
        gameSidebar->player[k]->status->setActive(false);
    gameSidebar->player[1]->status->setWinner();
    playSound(soundWin);
    QMessageBox::information(this, "You win", QString("<h2>You win!</h2><p>%1</p>").arg(message));
}

void Game::draw()
{
    for (int i = 0; i < 2; ++i)
    {
        gameSidebar->player[i]->status->setActive(false);
        gameSidebar->player[i]->status->setWinner();
    }
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
        {
            board->cell[i][j]->setFocused(false);
            board->cell[i][j]->setHighlighted(false);
        }
    current = -1;
    QMessageBox::information(this, "Draw", "<h2>Draw.</h2>");    
}

void Game::requestDraw()
{
    if (current == -1) return;
    if (current == role) 
    {
        QMessageBox::information(this, "Can't Draw", "Please finish your operation first.");
        return;
    }
    int ret = QMessageBox::warning(this, "Request Draw", "Do you really want to request draw?", QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes)
    {
        QMessageBox::information(this, "Request Draw", "Draw request sent.");
        emit sendMessage("requestDraw");        
    }
    emit checkMessages();
}

bool Game::resign()
{
    if (current == -1) return true;
    int ret = QMessageBox::warning(this, "Resign", "Do you really want to resign?", QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes)
    {
        emit sendMessage("resign");        
        lose("You've resigned.");
        return true;
    }
    else return false;
}

void Game::switchSound(QString text)
{
    if (text == "Sound: On")
    {
        sound = false;
        gameSidebar->buttons->buttonSound->setText("Sound: Off");
    }
    else
    {
        sound = true;
        gameSidebar->buttons->buttonSound->setText("Sound: On");
    }
}

void Game::playSound(QSoundEffect *sound)
{
    if (this->sound)
        sound->play();
}

QSoundEffect* Game::renderSound(QString url)
{
    QSoundEffect* sound = new QSoundEffect;
    sound->setSource(QUrl::fromLocalFile(url));    
    return sound;
}

void Game::closeEvent(QCloseEvent *event)
{
    if (resign())
        event->accept();
    else
        event->ignore();
}
