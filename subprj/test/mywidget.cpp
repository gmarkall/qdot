#include "mywidget.h"
mywidget::mywidget(QWidget *parent, Role role, const QString &name):QAccessibleWidget(parent,role,name)
{
    setValue("ciao");

}
