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

#ifndef CREATEGAMEDIALOG_H
#define CREATEGAMEDIALOG_H

#include "Common.h"
#include <QDialog>

namespace Ui {
class CreateGameDialog;
}

class CreateGameDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit CreateGameDialog(QWidget *parent = 0);
    ~CreateGameDialog();
    QString ip();
    QString nickname();
    int port();
    QString mode();
    
private slots:
    void on_buttonCancel_clicked();
    
    void on_buttonCreate_clicked();
    
private:
    Ui::CreateGameDialog *ui;
};

#endif // CREATEGAMEDIALOG_H
