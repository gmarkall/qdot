#include "DotEdit.h"
#include <QRegExp>
#include <QDebug>

DotEdit::DotEdit(QWidget *parent):QTextEdit	(parent){
    this->filename=QString("");
    this->saved=false;
    this->elements=new QList<DotElement>();
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
