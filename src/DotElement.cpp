#include "DotElement.h"
#include <QDebug>

DotElement::DotElement():QObject(){

}

DotElement::DotElement (const DotElement &cpy):QObject(){
	this->name=cpy.name;
	this->parameter=cpy.parameter;
}

void DotElement::setName(QString name){
	this->name=name;
}

void DotElement::setParameter(QString parameter){
	this->parameter=parameter;
}

QString DotElement::getName(){
	return this->name;
}

QString DotElement::getParameter(){
	return this->parameter;
}

 bool DotElement::operator==( const DotElement &cmp) const {
	return name==cmp.name;
}

 DotElement& DotElement::operator=(const DotElement &) {
	 return *this;
 }

 uint qHash(const DotElement &key){
	 DotElement ele=key;
 	return qHash(ele.getName());
 }
