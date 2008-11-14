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
