/*  Copyright (C) 2008 Igor Maculan <n3wtron AT gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/
#include "AddElementWin.h"
#include "DotElement.h"
#include <QDebug>

AddElementWin::AddElementWin(QWidget *parent,QList<DotElement> *list): QDialog(parent){
    ui.setupUi(this);
    this->elementList=list;
    connect (ui.btnAdd,SIGNAL(clicked()),this,SLOT(addElement()));
    connect (ui.btnCancel,SIGNAL(clicked()),this,SLOT(close()));
};

void AddElementWin::addElement(){
    DotElement* elem=new DotElement();
    elem->setName(ui.nameEdt->text());
    elem->setParameter(ui.parameterEdt->toPlainText());
    if (!this->elementList->contains(*elem)){
        this->elementList->insert (this->elementList->count(),*elem);
    }
    emit elementInserted();
    ui.nameEdt->setText("");
    ui.nameEdt->setFocus();
}
