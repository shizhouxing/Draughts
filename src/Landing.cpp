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

#include "Landing.h"
#include "CreateGameDialog.h"
#include "JoinGameDialog.h"

Landing::Landing(QWidget *parent) :
    QDialog(parent)
{
    buttons = new LandingButtons;
    generator = new Generator(this);
    
    connect(buttons->buttonCreate, SIGNAL(clicked(QString)), this, SLOT(clicked(QString)));
    connect(buttons->buttonJoin, SIGNAL(clicked(QString)), this, SLOT(clicked(QString)));
    connect(buttons->buttonAbout, SIGNAL(clicked(QString)), this, SLOT(clicked(QString)));
    connect(buttons->buttonQuit, SIGNAL(clicked(QString)), this, SLOT(clicked(QString)));
    
    QVBoxLayout *mainLayout = new QVBoxLayout;
    
    mainLayout->addStretch();
    mainLayout->addWidget(renderTitle());
    mainLayout->addWidget(buttons);
    mainLayout->addStretch();
    
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(70);
    setLayout(mainLayout);    
}

void Landing::clicked(const QString &text)
{
    if (text == "Create Game")
    {
        CreateGameDialog *dialog = new CreateGameDialog(this);
        if (dialog->exec() == QDialog::Rejected) return;
        else
        {
            QString stateMe, stateOpponent;
            if (dialog->mode() == "Standard")
            {
                srand(unsigned(time(0)));
                int role = rand() % 2;
                generator->reset(role);
                stateMe = generator->state();
                stateOpponent = generator->state(true);
            }
            else
            {
                generator->reset();
                if (generator->exec() == QDialog::Accepted)
                {
                    stateMe = generator->state();
                    stateOpponent = generator->state(true);
                }
                else return;
            }
            emit createGame(dialog->nickname(), dialog->ip(), dialog->port(), stateMe, stateOpponent);
        }
    }
    else if (text == "Join Game")
    {
        JoinGameDialog *dialog = new JoinGameDialog(this);
        if (dialog->exec() == QDialog::Rejected) return;
        else
            emit joinGame(dialog->nickname(), dialog->ip(), dialog->port());
    }
    else if (text == "About")
        QMessageBox::about(this, "About", "<h2>Draughts</h2>"
                                          "<p>Copyright &copy; 2017 <a href=\"mailto:zhouxingshichn@gmail.com\">Zhouxing Shi</a>. All rights reserved.</p>");
    else if (text == "Quit")
        qApp->quit();
}

QLabel* Landing::renderTitle()
{
    QLabel *title = new QLabel();
    QPixmap *pixmap = new QPixmap(":/icons/title.png");
    title->setPixmap(*pixmap);
    title->setFixedHeight(pixmap->height());
    title->setAlignment(Qt::AlignCenter);
    return title;
}

LandingButtons::LandingButtons(QWidget *parent) :
    Widget(parent)
{
    buttonCreate = renderButton("Create Game");
    buttonJoin = renderButton("Join Game");
    buttonAbout = renderButton("About");
    buttonQuit = renderButton("Quit");
        
    QVBoxLayout *mainLayout = new QVBoxLayout;
    
    mainLayout->addWidget(buttonCreate);
    mainLayout->addWidget(buttonJoin);
    mainLayout->addWidget(buttonAbout);
    mainLayout->addWidget(buttonQuit);
    
    mainLayout->setMargin(0);
    mainLayout->setSpacing(32);
    mainLayout->setAlignment(Qt::AlignHCenter);
    
    setLayout(mainLayout);
}

Button* LandingButtons::renderButton(const QString &text)
{
    Button* button = new Button(text);
    button->setStyleSheet(button->styleSheet() + 
                          "font-size: 24px;");
    button->setFixedHeight(65);
    button->setFixedWidth(195);
    return button;
}

PendingMsg::PendingMsg(QWidget *parent) :
    QDialog(parent)
{
    QLabel *text = new QLabel("Waiting for opponent...");
    text->setAlignment(Qt::AlignCenter);
    text->setStyleSheet("color: " + Config::Colors::PRIMARY + ";"
                        "font-size: 36px;");
    
    info = new QLabel();
    info->setAlignment(Qt::AlignCenter);
    info->setStyleSheet("color: " + Config::Colors::PRIMARY + ";"
                        "font-size: 24px;");    
    
    Button *button = new Button("Back");
    button->setStyleSheet(button->styleSheet() + 
                          "font-size: 20px;");
    button->setFixedHeight(40);
    button->setFixedWidth(115);
    connect(button, SIGNAL(clicked(QString)), this, SLOT(clicked()));
    
    QWidget *buttonBox = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(button);
    layout->setAlignment(Qt::AlignCenter);
    buttonBox->setLayout(layout);
    
    layout = new QVBoxLayout;
    layout->addStretch();
    layout->addWidget(text);
    layout->addWidget(info);
    layout->addWidget(buttonBox);
    layout->addStretch();
    layout->setSpacing(10);
    layout->setContentsMargins(0, 0, 0, 20);
    
    setLayout(layout);
}

void PendingMsg::clicked()
{
    emit canceled();
}

void PendingMsg::setIp(QString ip)
{
    this->ip = ip;
    renderInfo();
}

void PendingMsg::setPort(int port)
{
    this->port = port;
    renderInfo();
}

void PendingMsg::renderInfo()
{
    info->setText("IP: " + ip + " Port: " + QString::number(port));
}
