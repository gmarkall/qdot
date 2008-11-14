#ifndef DOTHIGHLIGHT_H
#define DOTHIGHLIGHT_H
#include <QSyntaxHighlighter>

class DotHighlight : public QSyntaxHighlighter{
    Q_OBJECT
public:
    DotHighlight(QTextEdit *edt);
protected:
    void highlightBlock(const QString & text);
};

#endif // DOTHIGHLIGHT_H
