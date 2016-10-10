#ifndef PTPATTRIBUTEFLOAT_H
#define PTPATTRIBUTEFLOAT_H

#include "PTPAttribute.h"
#include "PTAnimationCurve.h"

class PTPAttributeFloat : public PTPAttribute {
public:
    PTPAttributeFloat(PTModel *node, PTPAttributeValueType valueType = PTPAttributeValueVariable);

    virtual void initWithDictionary(CCDictionary *container);
    virtual CCDictionary *getDictionary();

    virtual std::vector<int> keyFrameMarkers(int state);
    bool isKeyExist(float time, int stateId);

    void setDefaultValue(float value);
    void setUseDefaultValue(bool value);
    bool useDefaultValue() const;

    void setDefaultVariableValue(float value);
    void setUseDefaultVariableValue(bool value);
    bool useDefaultVariableValue() const;

    // include original value and variableValue
    float valueVariated();

    float value();
    float offsetValue(float time = 0, int state = 0);
    void setOffsetValue( float time = 0, int state = 0);
    void setValue(float value, bool silentUpdate = false);
    void setKeyFrame(float value, float time, int state = 0);
    void deleteKeyFrame(float time, int state = 0);

    void setEmpty(bool);
    bool isEmpty();

    int intValue();
    void setIntValue(int value);

    float variableValue() const;
    void setVariableValue(float variableValue);

    virtual void match(PTPAttribute *attribute);

    float minValue() const;
    void setMinValue(float);

    float maxValue() const;
    void setMaxValue(float);

    float bound(float) const;
    virtual void print();

    virtual PTPAttribute::CurveVector animCurves( int state );
    virtual void setAnimCurves(PTPAttribute::CurveVector, PTPAnimationState);

#ifdef __QT__
    void setValueScale(float scale);
    float valueScale();

    void setValueInverted( bool );
    bool isValueInverted();

    float mapFromView( float );
    float viewValue();

    inline void setPrecision(unsigned precision) { _precision = precision; }
    inline unsigned precision() const { return _precision; }
#endif

private:

#ifdef __QT__
    float _valueScale;
    bool _isValueInverted;

    unsigned _precision;
#endif

    float _minValue;
    float _maxValue;

    bool _isEmpty;
    bool _useDefault;
    bool _useDefaultVarible;

    float _defaultValue;
    float _defaultVariableValue;

    float _variableValue;
    float _value;


    PTAnimationCurveMap _anim;


    friend class PTAttributeWidgetFloat;
    friend class PTAnimationEditorWidget;
    friend class PTInterfaceEditorWidget;
    friend class PTUndoObjectSetRotateKeyCommand;
    friend class PTUndoFloatAttributeSetKeyCommand;
};

#endif // PTPATTRIBUTEFLOAT_H
