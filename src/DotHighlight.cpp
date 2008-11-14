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
#include "DotHighlight.h"
#include <QTextCharFormat>
#include <QRegExp>
#include <QDebug>
#include <QFont>
DotHighlight::DotHighlight(QTextEdit *edt):QSyntaxHighlighter(edt){
}

void DotHighlight::highlightBlock(const QString &text){
    //STRINGHE
    QTextCharFormat stringFormat;
    stringFormat.setForeground(Qt::blue);
    QRegExp stringExp("[\"][a-zA-Z0-9 \\-_]*[\"]");
    int stringStart=text.indexOf(stringExp);
    while (stringStart>=0){
        int stringLength=stringExp.matchedLength();
        setFormat(stringStart,stringLength,stringFormat);
        stringStart=text.indexOf(stringExp,stringStart+stringLength);
    }
    //PAROLE CHIAVE
    QTextCharFormat keywordFormat;
    keywordFormat.setFontWeight(QFont::Bold);
    QRegExp keywordExp("node|graph|digraph");
    int keywordStart=text.indexOf(keywordExp);
    while (keywordStart>=0){
           int keywordLegth=keywordExp.matchedLength();
           setFormat(keywordStart,keywordLegth,keywordFormat);
           keywordStart=text.indexOf(keywordExp,keywordStart+keywordLegth);
    }
}
