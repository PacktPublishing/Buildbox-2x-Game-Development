#ifndef PTPATTRIBUTEANIMATION_H
#define PTPATTRIBUTEANIMATION_H

#include "PTPAttribute.h"
#include "models/PTModelAnimation.h"
#include "models/PTModelSpriteContainer.h"

class PTPAttributeAnimation : public PTPAttribute {
public:
    PTPAttributeAnimation(PTModel *node, PTPAttributeValueType valueType = PTPAttributeValueExact);

    virtual void initConnectionsWithDictionary(CCDictionary *container);
    virtual CCDictionary *getConnectionDictionary();

    virtual void cleanup();

    virtual void match(PTPAttribute *attribute);

    PTModelAnimation *value() const;
    void setValue(PTModelAnimation *value);

    PTModelSpriteContainer *spriteValue();
    void setSpriteValue(PTModelSpriteContainer *value);

#ifdef __QT__
    void buildPixmap();

    virtual bool usesContainer(const PTModelSpriteContainer *container);
#endif

private:
#ifdef __QT__
    void scheduleSpriteUpdate();
    void scheduleUsersSpriteUpdate();
#endif

private:
    PTModelAnimation *_value;
    PTModelSpriteContainer *_spriteValue;

#ifdef __QT__
    bool _spriteUpdateState;
#endif
};

#endif // PTPATTRIBUTEANIMATION_H
