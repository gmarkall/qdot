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
        editor->insertPlainText(QString(" \"%1\" -> \"%2\";\n").arg(left->text()).arg(right->text()));
    }
}

void AssociateElementWin::lineConnect(){
    QListWidgetItem *left=ui.leftList->currentItem();
    QListWidgetItem *right=ui.rightList->currentItem();
    if (left!=NULL && right!=NULL){
        editor->insertPlainText(QString(" \"%1\" -- \"%2\";\n").arg(left->text()).arg(right->text()));
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
