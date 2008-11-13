#ifndef MAINWIN_H_
#define MAINWIN_H_

#include <QMainWindow>
#include <QSet>
#include <QProcess>
#include "ui_MainWin.h"
#include "ui_About.h"
#include "DotEdit.h"
using namespace Ui;

class MainWin : public QMainWindow {
    Q_OBJECT
private:
    QString destType;
    MainWin_ui ui;
    About_ui uiAbout;
    QList<DotEdit*> dotEdits;
    DotEdit *actualEditor;
    void connectSignals();
    QString basicDirPath;
    void refreshBasicDirPath(QString);
    int zoom;
public:
    MainWin();
public slots:
    void newFile();
    void save();
    void saveAs();
    void open();
    bool closeFile();
    void compile();
    void view();
    void zoomIn();
    void zoomOut();
    void changeEditor(int);
    void refreshElements();
    void nextTab();
    void prevTab();
private slots:
    void fileChange();
    void about();
    void changeDestType(int);
    void drawLine();
    void preamble();
    void openAddElementWindow();
    void openAssociateElementWindow();
    void addElementFromList(QListWidgetItem*);
protected:
    void closeEvent(QCloseEvent *event);
};

#endif /*MAINWIN_H_*/
