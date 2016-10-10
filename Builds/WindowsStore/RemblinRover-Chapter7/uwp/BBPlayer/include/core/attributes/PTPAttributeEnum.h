#ifndef PTPATTRIBUTEENUM_H
#define PTPATTRIBUTEENUM_H

#include "PTPAttribute.h"

class PTPAttributeEnum : public PTPAttribute
{
public:
    PTPAttributeEnum(PTModel* node, PTPAttributeValueType valueType = PTPAttributeValueExact);

    virtual void initWithDictionary(CCDictionary *container);
    virtual CCDictionary* getDictionary();

    virtual void match(PTPAttribute* attribute);

    void setStringValue(const CCString value);
    const CCString& stringValue() const;

    void addItem(const CCString &value, const CCString &key);
    bool hasItem(const CCString &key) const;
    void removeItems();

#ifdef __QT__
    void setItemEnabled(const QString &key, bool state);

    QString mappedStringValue() const;

    inline const QList<QPair<QString, QPair<QString, bool>>>& items() const { return _items; }
#endif

private:
#ifdef __QT__
    QList<QPair<QString, QPair<QString, bool>>> _items;
#endif

    CCString _stringValue;

};

#endif // PTPATTRIBUTEENUM_H
