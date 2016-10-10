#ifndef PTPATTRIBUTEKEY_H
#define PTPATTRIBUTEKEY_H

#include "PTPAttribute.h"

class PTPAttributeKey : public PTPAttribute {
public:
    PTPAttributeKey(PTModel *node, PTPAttributeValueType valueType = PTPAttributeValueExact);

    virtual void initWithDictionary(CCDictionary *container);
    virtual CCDictionary *getDictionary();

    virtual void match(PTPAttribute *attribute);

    void setDefaultValue(int value);

    int value() const;
    void setValue(int value);

private:
    int _value;
    int _defaultValue;
};

#endif // PTPATTRIBUTEKEY_H
