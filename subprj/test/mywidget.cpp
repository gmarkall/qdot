#include "mywidget.h"
#include <QAccessible>
mywidget::mywidget(QWidget *parent, Role role, const QString &name):QAccessibleWidget(parent,role,name)
{
    addControllingSignal("textChanged(const QString &)");
}

QString mywidget::text(Text t,int child ){
    return "ciaociao";
}


