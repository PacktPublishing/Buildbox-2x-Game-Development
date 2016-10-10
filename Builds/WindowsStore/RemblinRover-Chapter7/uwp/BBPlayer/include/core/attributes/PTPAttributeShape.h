#ifndef PTPATTRIBUTESHAPE_H
#define PTPATTRIBUTESHAPE_H

#include "PTPAttribute.h"

enum PTPShapeType {
    PTPShapeUnknown,
    PTPShapePolygon,
    PTPShapeCircle
};

class PTModelPolygon;

class PTPAttributeShape: public PTPAttribute {
public:
    PTPAttributeShape(PTModel *node, PTPAttributeValueType valueType = PTPAttributeValueExact);

    virtual void initWithDictionary(CCDictionary *container);
    virtual CCDictionary *getDictionary();

    PTPShapeType shapeType() const;

    virtual void match(PTPAttribute *attribute);

    CCPoint oneWayCollisionVector();

    PTModelPolygon *value() const;
    void setValue(PTModelPolygon *value);        

private:
    void setShapeType(const CCString &className);
    PTModelPolygon *createShapeModel(PTPShapeType shapeType) const;

    PTModelPolygon *_value;
    PTPShapeType _shapeType;
};

#endif // PTPATTRIBUTESHAPE_H
