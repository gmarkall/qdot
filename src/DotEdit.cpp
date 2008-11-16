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
#include <QAbstractItemView>
#include <QScrollBar>
#include <QStringList>
#include <QListIterator>

#include "DotHighlight.h"

DotEdit::DotEdit(QWidget *parent):QTextEdit(parent){
    this->filename=QString("");
    this->saved=false;
    this->elements=new QList<DotElement>();
    new DotHighlight(this);
    setTabStopWidth(8);
    //autocompletition
    this->completer=NULL;
    refreshCompleter();
}

void DotEdit::refreshCompleter(){
    if (this->completer!=NULL){
        disconnect (completer,SIGNAL(activated(const QString&)),this,SLOT(insertCompletion(const QString&)));
    }
    QStringList wordList;
    wordList<<"digraph"<<"graph"<<"node";
    //aggiungo alla wordlist gli elementi
    QListIterator<DotElement> it(*this->elements);
    while (it.hasNext()){
        DotElement elem=it.next();
        wordList<<elem.getName();
    }

    this->completer=new QCompleter(wordList,this);
    completer->setWidget(this);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    completer->setCaseSensitivity(Qt::CaseSensitive);
    connect (completer,SIGNAL(activated(const QString&)),this,SLOT(insertCompletion(const QString&)));
}

void DotEdit::insertCompletion(const QString &text){
    QTextCursor cur= textCursor();
    int dimextra=text.length()- this->completer->completionPrefix().length();
    /*cur.movePosition(QTextCursor::Left);
    cur.movePosition(QTextCursor::EndOfWord);*/
    cur.insertText(text.right(dimextra));
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
    refreshCompleter();
}

QString DotEdit::textUnderCursor(){
    QTextCursor cur=textCursor();
    cur.select(QTextCursor::WordUnderCursor);
    QString selText=cur.selectedText();
    if (selText.left(1)=="\"")
    {
        selText=selText.right(selText.length()-1);
    }
    if (selText.right(1)=="\"")
    {
        selText=selText.left(selText.length()-1);
    }
    return selText;
}

void DotEdit::keyPressEvent(QKeyEvent *e){
    //AUTO COMPLETAMENTO
    if (this->completer && this->completer->popup()->isVisible()){
        switch (e->key()) {
        case Qt::Key_Enter:
        case Qt::Key_Return:
        case Qt::Key_Escape:
        case Qt::Key_Tab:
        case Qt::Key_Backtab:
            e->ignore();
            return; // let the completer do default behavior
        default:
            break;
        }
    }
    bool isShortcut = ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_Space); // CTRL+SPACE
    if (!this->completer|| !isShortcut){
        //INDENTAZIONE
        int ntab=0;
        if (e->key()==Qt::Key_Return){
            QTextBlock prev=textCursor().block();
            QRegExp tabExp("^\\t*");
            prev.text().indexOf(tabExp);
            ntab=tabExp.matchedLength();
        }
        QTextEdit::keyPressEvent(e);
        for (int i=0;i<ntab;i++){
            this->insertPlainText("\t");
        }
    }
    //AutoCompletamento
    const bool ctrlOrShift = e->modifiers() & (Qt::ControlModifier | Qt::ShiftModifier);
    if (!completer || (ctrlOrShift && e->text().isEmpty()))
        return;

    static QString eow("~!@#$%^&*()_+{}|:\"<>?,./;'[]\\-="); // end of word
    bool hasModifier = (e->modifiers() != Qt::NoModifier) && !ctrlOrShift;
    QString completionPrefix = textUnderCursor();

    if (!isShortcut && (hasModifier || e->text().isEmpty()|| completionPrefix.length() < 3
                        || eow.contains(e->text().right(1)))) {
        completer->popup()->hide();
        return;
    }

    if (completionPrefix != completer->completionPrefix()) {
        completer->setCompletionPrefix(completionPrefix);
        completer->popup()->setCurrentIndex(completer->completionModel()->index(0, 0));
    }
    QRect cr = cursorRect();
    cr.setWidth(completer->popup()->sizeHintForColumn(0)
                + completer->popup()->verticalScrollBar()->sizeHint().width());
    completer->complete(cr); // popup it up!

}

void DotEdit::newLine(){
    QTextCursor cur=textCursor();
    cur.movePosition(QTextCursor::EndOfLine);
    setTextCursor(cur);
    keyPressEvent(new QKeyEvent(QEvent::KeyPress,Qt::Key_Return,Qt::NoModifier));
}
