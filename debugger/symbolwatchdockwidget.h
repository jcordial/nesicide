#ifndef SYMBOLWATCHDOCKWIDGET_H
#define SYMBOLWATCHDOCKWIDGET_H

#include <QDockWidget>

#include "csymbolwatchmodel.h"
#include "cdebuggernumericitemdelegate.h"
#include "cdebuggersymboldelegate.h"
#include "ixmlserializable.h"

namespace Ui {
   class SymbolWatchDockWidget;
}

class SymbolWatchDockWidget : public QDockWidget, public IXMLSerializable
{
   Q_OBJECT

public:
   explicit SymbolWatchDockWidget(QWidget *parent = 0);
   ~SymbolWatchDockWidget();

   // IXMLSerializable interface
   virtual bool serialize(QDomDocument& doc, QDomNode& node);
   virtual bool deserialize(QDomDocument& doc, QDomNode& node, QString& errors);

protected:
   void keyPressEvent(QKeyEvent *event);
   void dragEnterEvent(QDragEnterEvent *event);
   void dragMoveEvent(QDragMoveEvent *event);
   void dropEvent(QDropEvent *event);

private:
   Ui::SymbolWatchDockWidget *ui;
   CSymbolWatchModel* model;
   CDebuggerSymbolDelegate* symbolDelegate;
   CDebuggerNumericItemDelegate* valueDelegate;
};

#endif // SYMBOLWATCHDOCKWIDGET_H
