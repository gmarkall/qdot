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
#ifndef DOTEDIT_H_
#define DOTEDIT_H_

#include <QTextEdit>
#include <QFont>
#include <QList>
#include <QKeyEvent>
#include "DotElement.h"
class DotEdit : public QTextEdit{
	Q_OBJECT
public:
	DotEdit(QWidget *parent);
	void setFileName(QString filename);
	QString getFileName();
	bool isSaved();
	void setSaved(bool);
        QList<DotElement>* getElements();
public slots:
	void importElements();
private:
	QString filename;
	bool saved;
        QList<DotElement> *elements;
protected:
        void keyPressEvent(QKeyEvent *);
};

#endif /*DOTEDIT_H_*/
