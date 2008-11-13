#include <QApplication>
#include "MainWin.h"
#include <iostream>
using namespace std;

int main(int argc, char** argv){
    QApplication a(argc,argv);
    if (QApplication::arguments().indexOf(QRegExp("[-]{1,2}help"))>0){
        cout << "Usage: QDot [OPTIONS]"<< endl;
        cout << "[OPTIONS]"<<endl;
        cout << "-zoom [value] : Value of text editor zoom"<< endl;
    }
    else{
        MainWin *win=new MainWin();
        win->showMaximized();
        return a.exec();
    }
}
