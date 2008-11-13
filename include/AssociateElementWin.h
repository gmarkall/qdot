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
