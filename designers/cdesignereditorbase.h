#ifndef CDESIGNEREDITORBASE_H
#define CDESIGNEREDITORBASE_H

#include <QWidget>
#include <QUndoStack>

#include "icenterwidgetitem.h"
#include "iprojecttreeviewitem.h"

class CDesignerEditorBase : public QWidget, public ICenterWidgetItem
{
   Q_OBJECT
public:
   explicit CDesignerEditorBase(IProjectTreeViewItem* link,QWidget *parent = 0);
   virtual ~CDesignerEditorBase() {};

   virtual bool isModified() { return m_isModified; }
   virtual void setModified(bool modified) { m_isModified = modified; emit editor_modified(modified); }

   // ICenterWidgetItem Interface Implmentation
   virtual bool onCloseQuery();
   virtual void onClose();
   virtual bool onSaveQuery();
   virtual void onSave();
   virtual QList<QAction*> editorMenu();

protected:
   void keyPressEvent(QKeyEvent *e);

public slots:
   virtual void snapTo(QString item) {}
   virtual void replaceText(QString from,QString to,bool replaceAll) {}
   virtual void applyChangesToTab(QString uuid) {}

signals:
   void editor_modified(bool m);
   void markProjectDirty(bool dirty);
   void breakpointsChanged();
   void activateSearchBar();
   void snapToTab(QString item);
   void addWatchedItem(QString item);
   void applyChanges(QString uuid);

protected:
   QUndoStack m_undoStack;
   bool m_isModified;
};

#endif // CDESIGNEREDITORBASE_H
