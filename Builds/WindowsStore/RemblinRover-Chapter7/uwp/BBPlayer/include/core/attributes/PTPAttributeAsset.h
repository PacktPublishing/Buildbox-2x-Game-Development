#ifndef PTPATTRIBUTEASSET_H
#define PTPATTRIBUTEASSET_H

#include "PTPAttribute.h"
#include "models/objects/PTModelAsset.h"

class PTPAttributeAsset : public PTPAttribute {
public:
    PTPAttributeAsset(PTModel *node, PTPAttributeValueType valueType = PTPAttributeValueExact);

    virtual void initConnectionsWithDictionary(CCDictionary *container);
    virtual CCDictionary *getConnectionDictionary();

    PTModelAsset *value() const;
    void setValue(PTModelAsset *value);

    virtual void match(PTPAttribute *attribute);

private:
    PTModelAsset *_value;
};

#endif // PTPATTRIBUTEASSET_H
