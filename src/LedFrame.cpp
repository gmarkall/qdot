#include "LedFrame.h"
#include <QImage>

LedFrame::LedFrame(QWidget *parent,Qt::WindowFlags f):QFrame(parent,f){
    this->state=-1;
}

void LedFrame::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QImage img;
    switch (this->state){
    case -1:{
            img=QImage(":/images/ledblue.png");
        }break;
    case 0:{
            img=QImage(":/images/ledgreen.png");
        }break;
    case 1:{
            img=QImage(":/images/ledorange.png");
        }break;
    case 2:{
            img=QImage(":/images/ledred.png");
        }break;
    }
    painter.drawImage(QPoint(0,0),img);
}

void LedFrame::setState(int state){
    if (state>-2 && state < 3){
        this->state=state;
    }
}
