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

#ifndef JOINGAMEDIALOG_H
#define JOINGAMEDIALOG_H

#include <QDialog>

namespace Ui {
class JoinGameDialog;
}

class JoinGameDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit JoinGameDialog(QWidget *parent = 0);
    ~JoinGameDialog();
    QString ip();
    QString nickname();
    int port();    
    
private slots:
    void on_buttonCreate_clicked();
    
    void on_buttonCancel_clicked();
    
private:
    Ui::JoinGameDialog *ui;
};

#endif // JOINGAMEDIALOG_H
