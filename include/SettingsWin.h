#ifndef SETTINGSWIN_H
#define SETTINGSWIN_H
#include <QDialog>
#include "ui_SettingsWin.h"
using namespace Ui;

class SettingsWin: public QDialog{
    Q_OBJECT
private:
    SettingsWin_ui ui;
    void connectSignals();
    void readSettings();
public:
    SettingsWin(QWidget *);
public slots:
    void apply();
    void ok();
    void cancel();
    void openGraphvizBrowse();

};

#endif // SETTINGSWIN_H
