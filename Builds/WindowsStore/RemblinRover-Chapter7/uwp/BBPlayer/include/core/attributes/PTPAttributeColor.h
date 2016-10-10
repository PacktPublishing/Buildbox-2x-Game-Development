#ifndef PTPATTRIBUTECOLOR_H
#define PTPATTRIBUTECOLOR_H

#include "PTPAttribute.h"

class PTPAttributeColor : public PTPAttribute
{
public:
    PTPAttributeColor(PTModel * parent, PTPAttributeValueType valueType = PTPAttributeValueExact);

    virtual void initWithDictionary(CCDictionary *container);
    virtual CCDictionary* getDictionary();

    virtual void match(PTPAttribute *attribute);

    ccColor4F value() const;
    void setValue(const ccColor4F &value);        
    void setDefaultValue(const ccColor4F &value);

    // Assign color from separated components
    void setValue(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

#ifdef __QT__
    // Assign color from Qt built-in color value
    void setValue(const QColor &value);
    QColor getQColorValue() const;
#endif

private:
    ccColor4F _value;
};

#endif // PTPATTRIBUTECOLOR_H
