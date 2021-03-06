/*  Copyright (C) 2008 Igor Maculan <n3wtron AT gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/
#include "MainWin.h"
#include "ui_About.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QDir>
#include <QCloseEvent>
#include <QStringList>
#include <QDesktopServices>
#include <QUrl>
#include <QTextCursor>
#include "AddElementWin.h"
#include "AssociateElementWin.h"
#include <QListIterator>
#include <QDebug>
#include <QSettings>
#include <QCoreApplication>
#include <QWindowsVistaStyle>
#include <QPlastiqueStyle>
#include <QIcon>
#include <QPainter>
#include "SettingsWin.h"

MainWin::MainWin() : QMainWindow() {
    //Settaggi di sistema
    QCoreApplication::setOrganizationName("MZTech");
    QCoreApplication::setApplicationName("QDot");
    QCoreApplication::setOrganizationDomain("mztech.info");
    this->setting=new QSettings();
    setting->beginGroup("Application");
    if(!setting->contains("graphvizBinaryDir")){
        openSettingsWindow();
    }
    setting->endGroup();

    dotEdits.clear(); //Svuoto la lista degli editor aperti
    actualEditor=NULL;
    basicDirPath=QDir::homePath();
    ui.setupUi(this);
    connectSignals(); //Connetto i segnali
    destType="png";
    changeDestType(0);
    QStringList arguments=QApplication::arguments();
    /*Controllo del parametro -zoom [num]*/
    int loc=arguments.indexOf(QRegExp("-zoom"));
    if (loc>0){
        //this->actualEditor->zoomIn(arguments.at(loc+1));
        bool convOK;
        int zoom=arguments.at(loc+1).toInt(&convOK,10);
        if (convOK){
            this->zoom=zoom;
        }
        else{
            this->zoom=0;
        }
    }else
        this->zoom=0;
#ifdef Q_WS_WIN
    QApplication::setStyle(new QWindowsVistaStyle);
#else
    QApplication::setStyle(new QPlastiqueStyle);
#endif
    setCompilationState(-1);
    readSettings();

}

void MainWin::readSettings(){
    QFont fnt, appfnt;
    fnt.fromString(setting->value("Application/font","Luxi Sans,-1,12,5,50,0,0,0,0,0").toString());
    appfnt.fromString(setting->value("Application/applicationFont","Luxi Sans,-1,12,5,50,0,0,0,0,0").toString());
    QApplication::setFont(appfnt);

    for (int i=0; i<dotEdits.size(); i++) {
        dotEdits[i]->setFont(fnt);
    }
}

void MainWin::connectSignals() {
    connect(ui.actionNew, SIGNAL(triggered()), this, SLOT(newFile()));
    connect(ui.actionSave, SIGNAL(triggered()), this, SLOT(save()));
    connect(ui.actionSaveAs, SIGNAL(triggered()), this, SLOT(saveAs()));
    connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(open()));
    connect(ui.actionClose, SIGNAL(triggered()), this, SLOT(closeFile()));
    connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui.actionExec, SIGNAL(triggered()), this, SLOT(compile()));
    connect(ui.actionView, SIGNAL(triggered()), this, SLOT(view()));
    connect(ui.actionZoomIn, SIGNAL(triggered()), this, SLOT(zoomIn()));
    connect(ui.actionZoomOut, SIGNAL(triggered()), this, SLOT(zoomOut()));
    connect(ui.actionAbout, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui.actNextTab,SIGNAL(triggered()),this,SLOT(nextTab()));
    connect(ui.actPrevTab,SIGNAL(triggered()),this,SLOT(prevTab()));
    connect(ui.mainTab,SIGNAL(currentChanged(int)),this,SLOT(changeEditor(int)));
    connect(ui.cmbDestType,SIGNAL(currentIndexChanged(int)),this,SLOT(changeDestType(int)));
    connect(ui.actionDrawLine,SIGNAL(triggered()),this,SLOT(drawLine()));
    connect(ui.btnCompile,SIGNAL(clicked()),this,SLOT(compile()));
    connect(ui.btnView,SIGNAL(clicked()),this,SLOT(view()));
    connect(ui.actionPreamble,SIGNAL(triggered()),this,SLOT(preamble()));
    connect(ui.actAddElement,SIGNAL(triggered()),this,SLOT(openAddElementWindow()));
    connect(ui.actionSettings,SIGNAL(triggered()),this,SLOT(openSettingsWindow()));
    connect(ui.actAssociateElement,SIGNAL(triggered()),this,SLOT(openAssociateElementWindow()));
    connect(ui.elementsList,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(addElementFromList(QListWidgetItem*)));
    //aggiungo il segnale di delete alla lista degli elementi
    QAction *modElement=new QAction(QIcon(":/images/edit.png"),tr("Modify"),ui.elementsList);
    QAction *delElement=new QAction(QIcon(":/images/del.png"),tr("Delete"),ui.elementsList);
    ui.elementsList->addAction(modElement);
    ui.elementsList->addAction(delElement);
    connect (delElement,SIGNAL(triggered()),this,SLOT(deleteSelectedElement()));
    connect (modElement,SIGNAL(triggered()),this,SLOT(editActualElement()));
    connect (ui.elementsList,SIGNAL(itemChanged(QListWidgetItem*)),this,SLOT(endEditActualElement(QListWidgetItem *)));
}

void MainWin::newFile() {
    actualEditor=new DotEdit(this);
    dotEdits << actualEditor;
    ui.mainTab->addTab(actualEditor, tr("Untitled"));
    ui.mainTab->setCurrentWidget(actualEditor);
    if (this->zoom > 0 )
        actualEditor->zoomIn(this->zoom);
    QFont fnt;
    fnt.fromString(setting->value("Application/font").toString());
    actualEditor->setFont(fnt);
}

bool MainWin::closeFile() {
    bool okChiudi=true;
    if (actualEditor !=NULL) {
        if (!actualEditor->isSaved()) {
            QMessageBox::StandardButton
                    res =QMessageBox::question(
                            this,
                            tr("File not saved"),
                            tr("Do you want to save the file %1 ?").arg(actualEditor->getFileName()),
                            QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
            if (res==QMessageBox::Yes) {
                save();
                if (!actualEditor->isSaved())
                    okChiudi=false;
            }
            if (res==QMessageBox::Cancel) {
                okChiudi=false;
            }
        }
        if (okChiudi) {
            DotEdit *tmp=actualEditor;
            ui.mainTab->removeTab(ui.mainTab->currentIndex());
            dotEdits.removeAll(tmp);
        }
    }
    return okChiudi;
}

void MainWin::save() {
    if (actualEditor!=NULL && !actualEditor->getFileName().isEmpty()) {
        //e' gia' stato salvato una volta
        QFile f(actualEditor->getFileName());
        f.open(QIODevice::WriteOnly);
        if (f.write(actualEditor->toPlainText().toAscii())>-1) {
            actualEditor->setSaved(true);
        } else
            QMessageBox::critical(this, tr("Saving File"),
                                  tr("Error saving file"));
        f.close();
        fileChange();
    } else {
        //Non ha ancora un nome
        saveAs();
    }
}

void MainWin::saveAs() {
    if (actualEditor!=NULL) {
        QString tmpFilename= QFileDialog::getSaveFileName(this,
                                                          tr("Save as"), basicDirPath, tr("Dot Files(*.dot)"));
        refreshBasicDirPath(tmpFilename);
        if (!tmpFilename.isEmpty()) {
            QFile f(tmpFilename);
            f.open(QIODevice::WriteOnly);
            if (f.write(actualEditor->toPlainText().toAscii())>-1) {
                actualEditor->setSaved(true);
                actualEditor->setFileName(tmpFilename);
                QFileInfo finfo(f);
                ui.mainTab->setTabText(ui.mainTab->currentIndex(),
                                       finfo.fileName());
            } else
                QMessageBox::critical(this, tr("Save file"),
                                      tr("Error saving file"));
            f.close();
        }
    }
}

void MainWin::open() {
    QString tmpFilename= QFileDialog::getOpenFileName(this, tr("Open"),
                                                      basicDirPath, tr("Dot Files(*.dot)"));
    if (!tmpFilename.isEmpty()) {
        // The user has chosen the name and not pressed cancel
        refreshBasicDirPath(tmpFilename);
        // If the file is already open, go to the tab it's in
        for (int i=0; i<dotEdits.size(); i++) {
            if (dotEdits.at(i)->getFileName()==tmpFilename) {
                ui.mainTab->setCurrentIndex(i+1); // First tab is "Welcome"
                return;
            }
        }
        newFile(); //creo la nuova scheda
        QFile f(tmpFilename);
        f.open(QIODevice::ReadOnly); //apro il file
        actualEditor->setPlainText(f.readAll()); //riempio la scheda con il contenuto del file
        f.close(); //chiusura file
        actualEditor->setFileName(tmpFilename); //cambio il nome del file nell'editor
        actualEditor->setSaved(true);
        QFileInfo finfo(f);
        ui.mainTab->setTabText(ui.mainTab->currentIndex(), finfo.fileName()); //cambio il nome del path nella tab
        //carico gli elementi già presenti
        actualEditor->importElements();
        refreshElements();
    }
}

void MainWin::changeEditor(int index) {
    if (index>0) {
        if (actualEditor!=NULL) {
            disconnect(actualEditor, SIGNAL(textChanged()), this,
                       SLOT(fileChange()));
        }
        actualEditor=(DotEdit*)ui.mainTab->currentWidget();
        //Reset the font
        QFont fnt;
        fnt.fromString(setting->value("Application/font").toString());
        actualEditor->setFont(fnt);

        actualEditor->setFocus();
        connect(actualEditor, SIGNAL(textChanged()), this,
                SLOT(fileChange()));
    } else {
        actualEditor=NULL;
    }
    refreshElements();
}

void MainWin::fileChange() {
    if (actualEditor!=NULL) {
        int index=ui.mainTab->currentIndex();
        if (!actualEditor->isSaved()) {
            if (!ui.mainTab->tabText(index).contains("*"))
                ui.mainTab->setTabText(index, QString("%1 [*]").arg(ui.mainTab->tabText(index))); //cambio il nome del path nella tab
        } else {
            ui.mainTab->setTabText(index, QString("%1").arg(ui.mainTab->tabText(index).remove(" [*]"))); //cambio il nome del path nella tab
        }
    }
}

void MainWin::refreshBasicDirPath(QString fname) {
    QDir tm(fname);
    basicDirPath=tm.filePath(fname);
}

/*
  Cambia il colore del led sulla sinistra in base allo stato
  -1->led blue
  0 ->led verde
  1 ->led arancione
  2 ->led rosso
*/
void MainWin::setCompilationState(int state){
    ui.ledFrame->setState(state);
    ui.ledFrame->repaint();
}

void MainWin::compile() {
    if (actualEditor!=NULL && !actualEditor->getFileName().isEmpty()) {
        QProcess *dot=new QProcess(this);
        QString dest=actualEditor->getFileName().left(actualEditor->getFileName().lastIndexOf("."));

#ifdef Q_WS_WIN
        QString basicCmd=QString("\"%1\\%2.exe\"")
                         .arg(QDir::toNativeSeparators(setting->value("Application/graphvizBinaryDir").toString()))
                         .arg(ui.cmbEngine->currentText());
        QStringList env = QProcess::systemEnvironment();
        dot->setEnvironment(env);
        QString cmd=QString("%1 -T%2 \"%3\" -o \"%4.%5\" -Gsize=\"%6,%7\"")
                    .arg(basicCmd)
                    .arg(destType)
                    .arg(QDir::toNativeSeparators(actualEditor->getFileName()))
                    .arg(QDir::toNativeSeparators(dest)).arg(destType)
                    .arg(ui.edtWidth->value()).arg(ui.edtHeight->value());
#else
        QString basicCmd=QString("%1/%2")
                         .arg(setting->value("Application/graphvizBinaryDir").toString())
                         .arg(ui.cmbEngine->currentText());
        QString cmd=QString("%1 -T%2  %3 -o %4.%5 -Gsize=\"%6,%7\" ")
                    .arg(basicCmd)
                    .arg(destType)
                    .arg(QDir::toNativeSeparators(actualEditor->getFileName()))
                    .arg(QDir::toNativeSeparators(dest)).arg(destType).arg(ui.edtWidth->value())
                    .arg(ui.edtHeight->value());
#endif
        dot->start(cmd);
        dot->waitForStarted();
        dot->waitForFinished();
        QByteArray result=dot->readAllStandardError();
        if (result.isEmpty() && dot->error()==QProcess::UnknownError ){
            setCompilationState(0);
            QMessageBox::information(this, tr("Compilation"), tr("Compilation successful"));
        }
        else{
            //errore di compilazione
            if (!result.isEmpty()){
                setCompilationState(1);
                QMessageBox::warning(this, tr("Compilation"), QString(result));
            }
            //errore dell'eseguibile
            if (dot->error()!=QProcess::UnknownError){
                setCompilationState(2);
                QMessageBox::critical(this, tr("Compilation"), tr("ERROR: %1 not found").arg(basicCmd));
            }
        }
    } else{
        setCompilationState(1);
        QMessageBox::warning(
                this,
                tr("Compilation"),
                tr("Can't compile an unsaved file."));
    }
}

void MainWin::view() {
    if (actualEditor!=NULL) {
        QString dest=actualEditor->getFileName().left(actualEditor->getFileName().lastIndexOf("."));
#ifdef Q_WS_WIN
        QString viewCmd=QString("file:///%1.%2").arg(dest).arg(destType);
        viewCmd.replace(' ',"%20");
        QDesktopServices::openUrl(viewCmd);
#else
        QDesktopServices::openUrl(QString("%1.%2").arg(dest).arg(destType));
#endif
    }
}

void MainWin::closeEvent(QCloseEvent *event) {
    //controllo che i file siano salvati
    bool okChiudi=true;
    while (!dotEdits.isEmpty()){
        actualEditor=dotEdits.at(dotEdits.size()-1);
        ui.mainTab->setCurrentWidget(actualEditor);
        okChiudi=okChiudi && closeFile();
        if (!okChiudi)
            break;
    }
    if (okChiudi)
        event->accept();
    else
        event->ignore();
}

void MainWin::zoomIn() {
    if (actualEditor!=NULL)
        actualEditor->zoomIn();
}

void MainWin::zoomOut() {
    if (actualEditor!=NULL)
        actualEditor->zoomOut();
}

void MainWin::about() {
    QDialog *about=new QDialog(this,Qt::Dialog);
    uiAbout.setupUi(about);
    about->show();
}

void MainWin::changeDestType(int) {
    destType=ui.cmbDestType->currentText();
}

void MainWin::drawLine(){
    if (actualEditor!=NULL){
        QTextCursor txtCur=actualEditor->textCursor();
        txtCur.insertText("\"--\" \";");
        txtCur.movePosition(QTextCursor::Left);
        txtCur.movePosition(QTextCursor::Left);
        txtCur.movePosition(QTextCursor::Left,QTextCursor::KeepAnchor);
        actualEditor->setTextCursor(txtCur);
    }
}

void MainWin::preamble(){
    if (actualEditor!=NULL){
        QTextCursor txtCur=actualEditor->textCursor();
        txtCur.insertText("digraph unix {\n\tnode[color=lightblue2,style=filled];\n\t\n}");
        txtCur.movePosition(QTextCursor::PreviousBlock);
        txtCur.movePosition(QTextCursor::EndOfBlock);
        actualEditor->setTextCursor(txtCur);
    }
}

void MainWin::openAddElementWindow(){
    if (actualEditor!=NULL){
        AddElementWin *elWin=new AddElementWin(this,actualEditor->getElements());
        connect(elWin, SIGNAL(elementInserted()), this, SLOT(refreshElements()));
        elWin->setModal(true);
        elWin->show();
    }
}

void MainWin::refreshElements()
{
    ui.elementsList->clear();
    if(actualEditor!=NULL)
    {
        QListIterator<DotElement> it(*actualEditor->getElements());
        while(it.hasNext())
        {
            DotElement elem = it.next();
            ui.elementsList->addItem(elem.getName());
        }
        actualEditor->refreshCompleter();
    }

}

void MainWin::openAssociateElementWindow(){
    if (actualEditor!=NULL){
        AssociateElementWin *win=new AssociateElementWin(this,actualEditor);
        connect(win, SIGNAL(elementInserted()), this, SLOT(refreshElements()));
        win->show();
    }
}

void MainWin::addElementFromList(QListWidgetItem* item){
    if (this->actualEditor!=NULL && item!=NULL){
        this->actualEditor->insertPlainText(QString("\"%1\"").arg(item->text()));
    }
}

void MainWin::nextTab(){
    ui.mainTab->setCurrentIndex(ui.mainTab->currentIndex()+1);
}

void MainWin::prevTab(){
    ui.mainTab->setCurrentIndex(ui.mainTab->currentIndex()-1);
}

void MainWin::openSettingsWindow(){
    SettingsWin *win = new SettingsWin(this);
    connect(win,SIGNAL(settingsApplied()),this,SLOT(readSettings()));
    win->show();
}

void MainWin::deleteSelectedElement(){
    if (actualEditor!=NULL){
        QListWidgetItem *it = ui.elementsList->currentItem();
        if (it!=NULL){
            actualEditor->getElements()->removeAll(DotElement(it->text()));
            refreshElements();
        }
    }
}

/**
*  RINOMINA
*/
void MainWin::editActualElement(){

    ui.elementsList->openPersistentEditor(ui.elementsList->currentItem());
    editItemString=ui.elementsList->currentItem()->text();
}

void MainWin::endEditActualElement(QListWidgetItem *it){
    ui.elementsList->closePersistentEditor(it);
    if (actualEditor!=NULL && !editItemString.isEmpty()){
        QList<DotElement>* lst=actualEditor->getElements();
        //recupero la posizione dell'elemento nella lista
        int i=lst->indexOf(DotElement(editItemString));
        //copio l'elemento per non perdere i dati
        DotElement el=lst->at(i);
        //rimozione elemento dalla lista
        lst->removeAt(i);
        el.setName(it->text());
        //reinserimento in posizione
        lst->insert(i,el);
        QString actualText=actualEditor->toPlainText();
        actualText.replace(QRegExp(QString("\"%1\"").arg(editItemString),Qt::CaseInsensitive),QString("\"%1\"").arg(it->text()));
        actualEditor->setPlainText(actualText);
        editItemString="";
        refreshElements();
    }
}

