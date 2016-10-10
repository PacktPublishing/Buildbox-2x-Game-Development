#ifndef PTPATTRIBUTE_H
#define PTPATTRIBUTE_H

#include "cocos2d.h"

class PTAnimationCurve;
class PTModelSpriteContainer;

enum PTPAttributeType {
    PTPAttributeTypeFloat,
    PTPAttributeTypePoint,
    PTPAttributeTypeSprite,
    PTPAttributeTypeObject,
    PTPAttributeTypeArray,
    PTPAttributeTypeAction,
    PTPAttributeTypeString,
    PTPAttributeTypeEnum,
    PTPAttributeTypeShape,
    PTPAttributeTypeAnimation,
    PTPAttributeTypePath,
    PTPAttributeTypeAsset,
    PTPAttributeTypeGroup,
    PTPAttributeTypeColor,
    PTPAttributeTypeBoolean,
    PTPAttributeTypeSound,
    PTPAttributeTypeKey,
    PTPAttributeTypeGradient,
    PTPAttributeTypeParticlesEmitters
};

enum PTPAttributeDirection {
    PTPAttributeInput = 0,
    PTPAttributeOutput
};

enum PTPAttributeValueType {
    PTPAttributeValueExact,
    PTPAttributeValueVariable
};

enum PTPAnimationState {
    OpenState = 0,
    IdleState = 1,
    CloseState = 2
};


typedef std::map<int, PTAnimationCurve*> PTAnimationCurveMap;
cocos2d::CCObject *animationCurveMapToContainer( PTAnimationCurveMap map );
PTAnimationCurveMap animationCurveContainerToMap( cocos2d::CCObject *container );
PTAnimationCurveMap animationCurveMapCopy( PTAnimationCurveMap map );

USING_NS_CC;

class PTModel;

class PTPAttribute : public CCObject {
public:
    PTPAttribute(PTModel *model, PTPAttributeType type, PTPAttributeValueType valueType);

    virtual void initWithDictionary(CCDictionary *container);
    virtual void initConnectionsWithDictionary(CCDictionary *container);
    virtual CCDictionary *getDictionary();
    virtual CCDictionary* getConnectionDictionary();

    virtual void cleanup();

    CCString name() const;
    CCString displayName() const;
    void setDisplayName( CCString );
    PTModel *model() const;
    PTPAttributeType type() const;

    bool isEditable() const;
    PTPAttributeDirection direction() const;

    void setEditable(bool editable);

    void setValueType(PTPAttributeValueType type);
    PTPAttributeValueType valueType() const;
    bool isVariableValue() const;

    virtual void attributeDidChanged();
    virtual void attributeDidConnected();
    virtual void attributeWillDisconnected();

    virtual void match( PTPAttribute* attribute ); // make current attribute with same set of values as input attribute

    virtual void show();
    virtual void hide();
    void setVisible( bool );
    bool isVisible() const;

    virtual void update(float dt);

    void setName(const CCString &name);

    virtual void print();
    virtual std::vector<int> keyFrameMarkers(int state );

    typedef std::vector<PTAnimationCurve*> CurveVector;
    virtual PTPAttribute::CurveVector animCurves( int state );
    virtual void setAnimCurves(PTPAttribute::CurveVector, PTPAnimationState);

#ifdef __QT__
    virtual bool usesContainer(const PTModelSpriteContainer *container);
    void setCanAnimate(bool animated);
    bool canAnimate();
#endif

protected:
    static CCDictionary *mergeContainers(CCDictionary *target, CCDictionary *source);
    PTModel *_model;

private:
    // Factory method to create all the attributes
    static PTPAttribute *createAttribute(PTModel *parent,
                                         PTPAttributeType type,
                                         PTPAttributeValueType valueType = PTPAttributeValueExact);

    void setDirection(PTPAttributeDirection direction);

    // variables that needed only for Buildbox Editor
    CCString _name;

#ifdef __QT__
    CCString _displayName;
    bool _canAnimate;
#endif

    bool _visible;

    PTPAttributeDirection _direction;
    PTPAttributeType _type;
    PTPAttributeValueType _valueType;

    bool _connectable;
    bool _editable;

    friend class PTModel;
    friend class PTMindMapEditorWidget;
    friend class PTNode;
    friend class PTNodeUIStart;
};

#endif // PTPATTRIBUTE_H
