#ifndef PTPATTRIBUTEBOOLEAN_H
#define PTPATTRIBUTEBOOLEAN_H

#include "PTPAttribute.h"

class PTPAttributeBoolean : public PTPAttribute
{
public:
    PTPAttributeBoolean(PTModel * parent, PTPAttributeValueType valueType = PTPAttributeValueExact);

    virtual void initWithDictionary(CCDictionary *container);
    virtual CCDictionary *getDictionary();

    virtual std::vector<int> keyFrameMarkers(int state);

    bool value() const;
    void setValue(bool value, bool silentUpdate = false);

    float offsetValue(float time = 0, int state = 0);
    void setOffsetValue( float time = 0, int state = 0);

    void setKeyFrame(float value, float time, int state = 0);
    void deleteKeyFrame(float time, int state = 0);

    void setDefaultValue(bool value);

    virtual void match(PTPAttribute *attribute);

    virtual PTPAttribute::CurveVector animCurves( int state );

private:
    bool _value;
    bool _defaultValue;

    PTAnimationCurveMap _anim;
};

#endif // PTPATTRIBUTEBOOLEAN_H
