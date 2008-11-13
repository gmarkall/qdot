#ifndef ASSOCIATEELEMENTWIN_H_
#define ASSOCIATEELEMENTWIN_H_

#include <QDialog>
#include <QSet>
#include "DotElement.h"
#include "DotEdit.h"
#include "ui_AssociateElementWin.h"
using namespace Ui;

class AssociateElementWin : public QDialog{
	Q_OBJECT
	private:
		AssociateElementWin_ui ui;
		DotEdit* editor;
	public:
		AssociateElementWin(QWidget * ,DotEdit*);
	private slots:
		void arrowConnect();
                void lineConnect();
                void openAddElementWin();
                void refreshRight();
                void refreshLeft();
                void refresh(bool);
                void filterLeft();
                void filterRight();
                void filter(bool);
        signals:
                void elementInserted();
};


#endif /* ASSOCIATEELEMENTWIN_H_ */
