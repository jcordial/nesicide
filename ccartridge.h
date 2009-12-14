#ifndef CCARTRIDGE_H
#define CCARTRIDGE_H

#include "ixmlserializable.h"
#include "iprojecttreeviewitem.h"
#include "cprgrombanks.h"
#include "cchrrombanks.h"

class CCartridge : public IXMLSerializable, public IProjectTreeViewItem
{
public:
    CCartridge();

    typedef enum {
        NoMirroring = 0,
        HorizontalMirroring = 1,
        VerticalMirroring = 2,
        FourScreenMirroring = 3
    } eGameMirrorMode;

    eGameMirrorMode mirrorMode;
    qint8 mapperNumber;
    bool hasBatteryBackedRam;

    CPRGROMBanks *prgromBanks;
    CCHRROMBanks *chrromBanks;

    // IXMLSerializable Interface Implementation
    virtual bool serialize(QDomDocument &doc, QDomNode &node);
    virtual bool deserialize(QDomDocument &doc, QDomNode &node);

    // IProjectTreeViewItem Interface Implmentation
    QString caption() const;
    virtual void contextMenuEvent(QContextMenuEvent *event, QTreeView *parent) {};
    virtual void openItemEvent(QTabWidget *tabWidget) {};
};

#endif // CCARTRIDGE_H
