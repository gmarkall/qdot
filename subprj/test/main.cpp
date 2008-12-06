#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QAccessible>
#include "mywidget.h"

 QAccessibleInterface *sliderFactory(const QString &classname, QObject *object)
 {
     QAccessibleInterface *interface = 0;

     if (classname == "QLineEdit" && object && object->isWidgetType())
         interface = new mywidget(static_cast<QWidget *>(object));

     return interface;
 }

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QAccessible::installFactory(sliderFactory);
    MainWindow *w=new MainWindow();
    w->show();
    return a.exec();
}
