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

#include "CreateGameDialog.h"
#include "ui_CreateGameDialog.h"

CreateGameDialog::CreateGameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateGameDialog)
{
    ui->setupUi(this);
    QList<QHostAddress> ipListAll = QNetworkInterface::allAddresses();
    ui->ipList->addItem(QHostAddress(QHostAddress::LocalHost).toString());    
    for (int i = 0; i < ipListAll.size(); ++i)
    {
        QHostAddress ip = ipListAll[i];
        if (ip != QHostAddress::LocalHost && ip.toIPv4Address())
            ui->ipList->addItem(ip.toString());
    }
}

CreateGameDialog::~CreateGameDialog()
{
    delete ui;
}

void CreateGameDialog::on_buttonCancel_clicked()
{
    reject();
}

void CreateGameDialog::on_buttonCreate_clicked()
{
    accept();
}

QString CreateGameDialog::nickname()
{
    return ui->nickname->text();
}

QString CreateGameDialog::ip()
{
    return ui->ipList->currentText();
}

int CreateGameDialog::port()
{
    return ui->port->text().toInt();
}

QString CreateGameDialog::mode()
{
    if (ui->modeCustom->isChecked())
        return "Custom";
    else 
        return "Standard";
}
