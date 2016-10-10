#ifndef PTMODEL_H
#define PTMODEL_H

#include <cocos2d.h>

#include "attributes/PTPAttribute.h"

USING_NS_CC;

class PTModelSpriteContainer;
class PTPAttribute;
class PTPAttributeString;
class PTPAttributeGroup;

class PTModel : public CCObject {
public:
    PTModel(CCString className, CCString name = CCString());
    virtual ~PTModel();

    virtual void initWithDictionary(CCDictionary *container);
    virtual CCDictionary *getDictionary();
    virtual CCDictionary *getConnectionsDictionary();
    virtual void initConnectionsWithDictionary(CCDictionary *container);

    virtual void setDeleted(bool);
    bool isDeleted();

    virtual void cleanup();

    int id() const;
    CCString name() const;
    void setName(const CCString &name);

    CCString className() const;
    bool isKindOf(CCString className) const;

    float time() const;
    void setTime(float time);

    virtual PTModel* duplicated();
    virtual void match(PTModel* model); //match current model with input model

    virtual void update(float dt);
    virtual void attributeDidUpdated(PTPAttribute *attr);
    virtual void attributeDidConnected(PTPAttribute *attr);
    virtual void attributeWillDisconnected(PTPAttribute *attr);

    PTPAttribute *addAttribute(const CCString &name,
                               PTPAttributeType type,
                               PTPAttributeValueType valueType = PTPAttributeValueExact,
                               PTPAttributeGroup *group = NULL,
                               PTPAttributeDirection direction = PTPAttributeInput);
    void removeAttribute(PTPAttribute *attribute);
    inline void removeAttribute(const CCString &name) { removeAttribute(attributeByName(name)); }

    int attributeCount() const;
    PTPAttribute *attributeAt(int index) const;
    PTPAttribute *attributeByName(CCString name) const;
    int attributeIndex(PTPAttribute *) const;
    void setAttributeIndex(PTPAttribute *, int index);

#ifdef __QT__
    virtual bool usesContainer(const PTModelSpriteContainer *container) ;
#endif

protected:
    PTPAttributeString *_nameAttribute;

private:
    void setId( int );

private:        
    CCString _className;
    CCArray *_attributes;

    unsigned int _id;
    float _time;

    bool _deleted;

    friend class PTAnimationEditorWidget;
    friend class PTWorldEditorWidget;
    friend class PTUndoGraphicsObjectCommand;
};

#endif // PTMODEL_H
