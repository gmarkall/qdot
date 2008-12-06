#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::Dialog)
{
    m_ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete m_ui;
}

void Dialog::changeEvent(QEvent *e)
{
    switch(e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
