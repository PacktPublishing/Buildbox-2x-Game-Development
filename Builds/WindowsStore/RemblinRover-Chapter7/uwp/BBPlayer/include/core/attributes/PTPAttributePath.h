#ifndef PTPATTRIBUTEPATH_H
#define PTPATTRIBUTEPATH_H

#include "PTPAttribute.h"
#include "models/PTModelPath.h"

class PTPAttributePath : public PTPAttribute {
public:
    PTPAttributePath(PTModel *node, PTPAttributeValueType valueType = PTPAttributeValueExact);

    void setValue(PTModelPath *value);
    PTModelPath *value();

private:
    PTModelPath *_value;
};

#endif // PTPATTRIBUTEPATH_H
