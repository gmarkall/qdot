#ifndef DOTEDIT_H_
#define DOTEDIT_H_

#include <QTextEdit>
#include <QFont>
#include <QList>
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
};

#endif /*DOTEDIT_H_*/
