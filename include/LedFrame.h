#ifndef LEDFRAME_H
#define LEDFRAME_H
#include <QPainter>
#include <QFrame>
#include <QPaintEvent>

class LedFrame : public QFrame{
    Q_OBJECT
private:
    int state;
public:
    LedFrame(QWidget *parent,Qt::WindowFlags  f = 0);
    void paintEvent(QPaintEvent*);
    void setState(int state);
};

#endif // LEDFRAME_H
