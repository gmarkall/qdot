#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QLineEdit>
#include "mywidget.h"
class MainWindow:public QMainWindow{
    Q_OBJECT
    private:
    QLineEdit *edt;
    mywidget *wid;
    public:
    MainWindow();
    public slots:
    void refresh(const QString &);
};


#endif // MAINWINDOW_H
