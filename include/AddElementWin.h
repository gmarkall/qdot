#ifndef ADDELEMENTWIN_H
#define ADDELEMENTWIN_H

#include <QDialog>
#include <QList>
#include "ui_AddElementWin.h"
#include "DotElement.h"

using namespace Ui;
class AddElementWin : public QDialog{
    Q_OBJECT
        private:
    AddElementWin_ui ui;
    QList<DotElement> *elementList;
        public:
    AddElementWin(QWidget *parent,QList<DotElement> *list);
        private slots:
    void addElement();
        signals:
    void elementInserted();
};

#endif
