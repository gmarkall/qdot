#include "mainwindow.h"
#include "mywidget.h"
#include <QLineEdit>
#include <QGridLayout>
#include <QAccessible>
#include <QMessageBox>
MainWindow::MainWindow(){
        resize(800,600);
        this->setWindowTitle("Accessibility test");
        QLineEdit *edt=new QLineEdit(this);
        this->setCentralWidget(edt);
        mywidget *wid=new mywidget(edt);
        QAccessible::queryAccessibleInterface(edt);
        if (QAccessible::isActive()){
                QMessageBox::information(this,tr("OK"),tr("OK"));
        }
        else{
            QMessageBox::information(this,tr("KO"),tr("KO"));
        }
}
