#ifndef CSYNTAXHIGHLIGHTEDTEXTEDIT_H
#define CSYNTAXHIGHLIGHTEDTEXTEDIT_H

#include <QPlainTextEdit>
#include <QObject>
#include <QPainter>
#include <QTextBlock>
#include "csyntaxhighlighter.h"

class LineNumberArea;


class CSyntaxHighlightedTextEdit : public QPlainTextEdit
{
    Q_OBJECT

public:
    CSyntaxHighlightedTextEdit(QWidget *parent = 0);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);

private:
    QWidget *lineNumberArea;
    CSyntaxHighlighter *highlighter;
};


class LineNumberArea : public QWidget
{
public:
    LineNumberArea(CSyntaxHighlightedTextEdit *editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    CSyntaxHighlightedTextEdit *codeEditor;
};


#endif // CSYNTAXHIGHLIGHTEDTEXTEDIT_H