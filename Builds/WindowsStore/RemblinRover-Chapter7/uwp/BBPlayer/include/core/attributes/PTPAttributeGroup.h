#ifndef PTPATTRIBUTEGROUP_H
#define PTPATTRIBUTEGROUP_H

#include "PTPAttribute.h"

class PTPAttributeGroup : public PTPAttribute {
public:
    PTPAttributeGroup(PTModel *node, PTPAttributeValueType valueType = PTPAttributeValueExact);
    ~PTPAttributeGroup();

    virtual void initWithDictionary(CCDictionary *container);
    virtual void initConnectionsWithDictionary(CCDictionary *container);
    virtual CCDictionary *getDictionary();

    virtual void update( float dt );

    void addAttribute(PTPAttribute *attribute);

    virtual void match(PTPAttribute* attribute);

    virtual void show();
    virtual void hide();

    int attributeCount() const;
    PTPAttribute *attributeAt(int index);

private:
    CCArray *_attributes;
};

#endif // PTPATTRIBUTEGROUP_H
