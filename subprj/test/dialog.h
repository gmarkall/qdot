#ifndef DIALOG_H
#define DIALOG_H

#include <QtGui/QDialog>

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(Dialog)
public:
    explicit Dialog(QWidget *parent = 0);
    virtual ~Dialog();

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::Dialog *m_ui;
};

#endif // DIALOG_H
