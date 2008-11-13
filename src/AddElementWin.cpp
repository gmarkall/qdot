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
