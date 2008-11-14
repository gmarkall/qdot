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
#include "DotEdit.h"
#include <QRegExp>
#include <QDebug>
#include <QTextBlock>
#include "DotHighlight.h"

DotEdit::DotEdit(QWidget *parent):QTextEdit(parent){
    this->filename=QString("");
    this->saved=false;
    this->elements=new QList<DotElement>();
    DotHighlight *highlight= new DotHighlight(this);
    setTabStopWidth(8);
}

void DotEdit::setFileName(QString filename){
    this->filename=filename;
}

QString DotEdit::getFileName(){
    return this->filename;
}

bool DotEdit::isSaved(){
    this->saved=!this->document()->isModified();
    return this->saved;
}

void DotEdit::setSaved(bool saved){
    this->saved=saved;
    this->document()->setModified(false);
}

QList<DotElement>* DotEdit::getElements(){
    return this->elements;
}

void DotEdit::importElements(){
    QRegExp elementsExp("\"[a-z0-9A-Z]*\"");
    QString allText=this->toPlainText();
    int pos=0;
    while ((pos=elementsExp.indexIn(allText,pos))!=-1){
        DotElement el;
        QString name=elementsExp.cap(0);
        el.setName(name.mid(1,name.length()-2));
        if (!elements->contains(el)){
            elements->insert(0,el);
        }
        pos+=elementsExp.matchedLength();
    }
}

void DotEdit::keyPressEvent(QKeyEvent *e){
    int ntab=0;
    if (e->key()==Qt::Key_Return){
        QTextBlock prev=textCursor().block();
        QRegExp tabExp("^\\t*");
        prev.text().indexOf(tabExp);
        ntab=tabExp.matchedLength();
        qDebug()<< ntab;
    }
    QTextEdit::keyPressEvent(e);
    for (int i=0;i<ntab;i++){
        this->insertPlainText("\t");
    }
}
