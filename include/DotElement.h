#ifndef DOTELEMENT_H
#define DOTELEMENT_H
#include <QObject>

class DotElement : public QObject{
	Q_OBJECT
	public:
		DotElement();
		DotElement (const DotElement &);
		void setName(QString name);
		void setParameter(QString parameter);
		QString getName();
		QString getParameter();
		bool operator==(const DotElement &)const ;
		DotElement& operator=(const DotElement &);
	private:
		QString name;
		QString parameter;

};
uint qHash(const DotElement &key);
#endif


