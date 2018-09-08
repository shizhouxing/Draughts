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

#include "JoinGameDialog.h"
#include "ui_JoinGameDialog.h"

JoinGameDialog::JoinGameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JoinGameDialog)
{
    ui->setupUi(this);
}

JoinGameDialog::~JoinGameDialog()
{
    delete ui;
}

QString JoinGameDialog::ip()
{
    return ui->ip->text();
}

QString JoinGameDialog::nickname()
{
    return ui->nickname->text();
}

int JoinGameDialog::port()
{
    return ui->port->text().toInt();
}

void JoinGameDialog::on_buttonCreate_clicked()
{
    accept();
}

void JoinGameDialog::on_buttonCancel_clicked()
{
    reject();
}
