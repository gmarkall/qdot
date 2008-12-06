#include "mainwindow.h"

#include <QLineEdit>
#include <QGridLayout>
#include <QAccessible>
#include <QMessageBox>

MainWindow::MainWindow(){
    resize(800,600);
    this->setWindowTitle("Accessibility test");
    edt=new QLineEdit(this);
    connect (edt,SIGNAL(textChanged(const QString &)),this,SLOT(refresh(const QString &)));
    QAccessible::queryAccessibleInterface(edt);
    this->setCentralWidget(edt);
    if (QAccessible::isActive()){
        QMessageBox::information(this,tr("OK"),tr("OK"));
    }
    else{
        QMessageBox::information(this,tr("KO"),tr("KO"));
    }
}


void MainWindow::refresh(const QString &tt){
    QAccessible::updateAccessibility(edt, 0, QAccessible::ValueChanged);
}
