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
#include "AssociateElementWin.h"
#include "AddElementWin.h"
#include <QListIterator>
#include <QListWidgetItem>

AssociateElementWin::AssociateElementWin(QWidget *parent,DotEdit *editor):QDialog(parent){
    ui.setupUi(this);
    this->editor = editor;
    this->refresh(true);
    this->refresh(false);
    connect (ui.btn_arrow,SIGNAL(clicked()),this,SLOT(arrowConnect()));
    connect (ui.btn_line,SIGNAL(clicked()),this,SLOT(lineConnect()));
    connect (ui.btn_add,SIGNAL(clicked()),this,SLOT(openAddElementWin()));
    connect (ui.leftEditor,SIGNAL(editingFinished()),this,SLOT(filterLeft()));
    connect (ui.rightEditor,SIGNAL(editingFinished()),this,SLOT(filterRight()));
}

void AssociateElementWin::refreshRight(){ refresh(false);}
void AssociateElementWin::refreshLeft(){ refresh(true);}

void AssociateElementWin::refresh(bool left){
    QListWidget *list;
    if (left){
        list=ui.leftList;
    }else
    {
        list=ui.rightList;
    }
    list->clear();
    QListIterator<DotElement> it(*(this->editor->getElements()));
    while (it.hasNext()){
        DotElement el=it.next();
        list->addItem(el.getName());
    }
}

void AssociateElementWin::arrowConnect(){
    QListWidgetItem *left=ui.leftList->currentItem();
    QListWidgetItem *right=ui.rightList->currentItem();
    if (left!=NULL && right!=NULL){
        editor->newLine();
        editor->insertPlainText(QString(" \"%1\" -> \"%2\";").arg(left->text()).arg(right->text()));
    }
}

void AssociateElementWin::lineConnect(){
    QListWidgetItem *left=ui.leftList->currentItem();
    QListWidgetItem *right=ui.rightList->currentItem();
    if (left!=NULL && right!=NULL){
        editor->newLine();
        editor->insertPlainText(QString(" \"%1\" -- \"%2\";").arg(left->text()).arg(right->text()));
    }
}

void AssociateElementWin::openAddElementWin(){
    AddElementWin *win=new AddElementWin(this,this->editor->getElements());
    connect(win, SIGNAL(elementInserted()), this, SLOT(refreshRight()));
    connect(win, SIGNAL(elementInserted()), this, SLOT(refreshLeft()));
    connect(win, SIGNAL(elementInserted()), this, SIGNAL(elementInserted()));
    win->setModal(true);
    win->show();
}

void AssociateElementWin::filterLeft(){ filter(true);}
void AssociateElementWin::filterRight(){ filter(false);}
void AssociateElementWin::filter(bool isLeft){
    QListWidget *list;
    QLineEdit *editor;
    if (isLeft){
        editor=ui.leftEditor;
        list=ui.leftList;
    }else
    {
        editor=ui.rightEditor;
        list=ui.rightList;
    }
    refresh(isLeft);
    QList<QListWidgetItem*>filterList=list->findItems(editor->text(),Qt::MatchContains);
    QStringList filterItems;
    for (int i=0;i<filterList.count();i++){
        filterItems.append(filterList.at(i)->text());
    }
    list->clear();
    for (int i=0;i<filterItems.count();i++){
        list->addItem(filterItems.at(i));
    }
}
