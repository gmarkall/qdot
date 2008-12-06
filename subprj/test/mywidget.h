#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QAccessibleWidget>

class mywidget : public QAccessibleWidget
{
public:
    mywidget(QWidget *parent, Role role=QAccessible::Client, const QString &name=QString());
};

#endif // MYWIDGET_H
