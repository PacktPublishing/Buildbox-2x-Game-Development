#ifndef PTPATTRIBUTESOUND_H
#define PTPATTRIBUTESOUND_H

#include "PTPAttribute.h"

class PTModelSound;

class PTPAttributeSound : public PTPAttribute
{
public:
    PTPAttributeSound(PTModel *node, PTPAttributeValueType valueType = PTPAttributeValueExact);

    void match(PTPAttribute* attribute);

    virtual void initConnectionsWithDictionary(CCDictionary *container);
    virtual CCDictionary *getConnectionDictionary();

    PTModelSound *value() const;
    void setValue(PTModelSound *value);

private:
    PTModelSound *_value;
};

#endif // PTPATTRIBUTESOUND_H
