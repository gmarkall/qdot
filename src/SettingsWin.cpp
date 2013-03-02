#include "SettingsWin.h"
#include <QFileDialog>
#include <QSettings>
#include <QFont>
#include <QDebug>
SettingsWin::SettingsWin(QWidget *parent):QDialog(parent){
    ui.setupUi(this);
    setModal(true);
    connectSignals();
    readSettings();
}


void SettingsWin::readSettings(){
    QSettings setting;
    //GRAPHVIZ
    ui.edtGraphvizPath->setText(setting.value("Application/graphvizBinaryDir").toString());
    //FONT
    QFont fnt;
    fnt.fromString(setting.value("Application/font","Luxi Sans,-1,12,5,50,0,0,0,0,0").toString());
    ui.cmbFontName->setCurrentFont(fnt);
    ui.spinFontSize->setValue(fnt.pixelSize());
    //FONT APPLICATION
    QFont appfnt;
    appfnt.fromString(setting.value("Application/applicationFont","Luxi Sans,-1,12,5,50,0,0,0,0,0").toString());
    ui.cmbApplicationFontName->setCurrentFont(appfnt);
    ui.spinApplicationFontSize->setValue(appfnt.pixelSize());
}

void SettingsWin::connectSignals(){
    connect (ui.btnApply,SIGNAL(clicked()),this,SLOT(apply()));
    connect (ui.btnOk,SIGNAL(clicked()),this,SLOT(ok()));
    connect (ui.btnCancel,SIGNAL(clicked()),this,SLOT(cancel()));
    connect (ui.btnGraphvizBrowse,SIGNAL(clicked()),this,SLOT(openGraphvizBrowse()));
}

void SettingsWin::openGraphvizBrowse(){
    QString graphvizPath=QFileDialog::getExistingDirectory(this,tr("Graphviz bin directory"),"");
    if (!graphvizPath.isEmpty()){
        ui.edtGraphvizPath->setText(graphvizPath);
    }
}

/*
  * Apply ALL (ALL PAGES) changes into QDot Settings
*/
void SettingsWin::apply(){
    QSettings setting;
    //APPLICATION
    setting.beginGroup("Application");
    //GRAPHVIZ PATH
    setting.setValue("graphvizBinaryDir",ui.edtGraphvizPath->text());
    //FONT
    QFont selFont=ui.cmbFontName->currentFont();
    selFont.setPixelSize(ui.spinFontSize->value());
    setting.setValue("font",selFont.toString());

    //FONT APPLICATION
    QFont appfnt=ui.cmbApplicationFontName->currentFont();
    appfnt.setPixelSize(ui.spinApplicationFontSize->value());
    setting.setValue("applicationFont",appfnt.toString());

    //Salvataggio
    setting.endGroup();

    emit settingsApplied();
}

void SettingsWin::cancel(){
    close();
}

void SettingsWin::ok()
{
    apply();
    cancel();
}
