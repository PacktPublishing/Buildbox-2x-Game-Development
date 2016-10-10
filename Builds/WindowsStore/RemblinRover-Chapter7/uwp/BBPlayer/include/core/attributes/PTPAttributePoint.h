#ifndef PTPATTRIBUTEPOINT_H
#define PTPATTRIBUTEPOINT_H

#include "PTPAttribute.h"
#include "PTAnimationCurve.h"

class PTPAttributePoint : public PTPAttribute {
public:
    PTPAttributePoint(PTModel *node, PTPAttributeValueType valueType = PTPAttributeValueVariable);

    virtual void initWithDictionary(CCDictionary *container);
    virtual CCDictionary *getDictionary();

    bool isKeyExist(float time, int stateId);
    std::vector<int> keyFrameMarkers( int state );
    std::vector<int> secondKeyFrameMarkers( int state );

    // return original value that include affect of variableValue();
    CCPoint valueVariated();

    CCPoint value();
    void setValue(const CCPoint &value, bool silentUpdate = false);

    CCPoint offsetValue(float time = 0, int stateId = 0);
    void setKeyFrame(CCPoint value, float time, int stateId = 0);
    void deleteKeyFrame(float time, int stateId = 0);

    void setXEmpty(bool);
    bool isXEmpty();

    void setYEmpty(bool);
    bool isYEmpty();

    void setDefaultValue(const CCPoint &value);
    void setUseDefaultValue(bool value);
    bool useDefaultValue() const;

    CCPoint variableValue() const;
    void setVariableValue(const CCPoint &value);

    virtual void match(PTPAttribute* attribute);
    virtual void print();

    virtual PTPAttribute::CurveVector animCurves(int state);
    virtual void setAnimCurves(PTPAttribute::CurveVector, PTPAnimationState);


#ifdef __QT__
    void setValueScale(CCPoint scale);
    CCPoint valueScale();

    void setValueInverted( bool );
    bool isValueInverted();

    CCPoint mapFromView( CCPoint );
    CCPoint viewValue();

    inline void setPrecision(unsigned precision) { _precision = precision; }
    inline unsigned precision() const { return _precision; }
#endif

private:

#ifdef __QT__
    CCPoint _valueScale;
    bool _isValueInverted;

    unsigned _precision;
#endif

    CCPoint _variableValue;
    CCPoint _value;
    CCPoint _defaultValue;

    bool _isXEmpty;
    bool _isYEmpty;
    bool _useDefault;


    PTAnimationCurveMap _animX;
    PTAnimationCurveMap _animY;


    friend class PTAttributeWidgetPoint;
    friend class PTAnimationEditorWidget;
    friend class PTInterfaceEditorWidget;
    friend class PTUndoObjectSetMoveKeyCommand;
    friend class PTUndoObjectSetScaleKeyCommand;
};

#endif // PTPATTRIBUTEPOINT_H
