#ifndef PTPATTRIBUTEACTION_H
#define PTPATTRIBUTEACTION_H

#include "PTPAttribute.h"

#include <vector>
#include <algorithm>

class PTPObject;
class PTPObjectAsset;

#define PTPActionPointerSelectorSender(_SELECTOR) (PTPActionPointerSender)(&_SELECTOR)
typedef void (CCObject::*PTPActionPointerSender)( PTPObject* );

#define PTPActionPointerSelector(_SELECTOR) (PTPActionPointer)(&_SELECTOR)
typedef void (CCObject::*PTPActionPointer)();

#define PTPActionPointerSelectorSender(_SELECTOR) (PTPActionPointerSender)(&_SELECTOR)
typedef void (CCObject::*PTPActionPointerSender)( PTPObject* );

#define PTPActionPointerSelectorCollider(_SELECTOR) (PTPActionPointerCollider)(&_SELECTOR)
typedef void (CCObject::*PTPActionPointerCollider)( PTPObject*, PTPObjectAsset*  );

enum PTPObjectAssetEventType{
    PTPObjectAssetDeleteEvent = 0,
    PTPObjectAssetCollideEvent
};

struct PTActionSubscriberCollisionStruct{
    PTPObjectAssetEventType event;
    CCObject *target;
    PTPActionPointerCollider selector;
    unsigned int senderId;
};

struct PTActionSubscriberStruct{
    PTPObjectAssetEventType event;
    CCObject *target;
    PTPActionPointerSender selector;
    unsigned int senderId;
};

class PTPAttributeAction : public PTPAttribute {
public:
    PTPAttributeAction(PTModel *model, PTPAttributeValueType valueType = PTPAttributeValueExact);
    ~PTPAttributeAction();

    void initConnectionsWithDictionary(CCDictionary *container);
    CCDictionary* getConnectionDictionary();

    void match(PTPAttribute *attribute);

    void cleanup() { disconnect(); }

    void connect(PTPAttributeAction *action);
    void disconnect();
    void disconnect(PTPAttributeAction *action);

    inline PTPAttributeAction* target() const { return direction() == PTPAttributeOutput && !_connectedList.empty() ? _connectedList.front() : nullptr; }
    inline const std::vector<PTPAttributeAction*>& connectedList() const { return _connectedList; }

    inline bool isConnected() const { return !_connectedList.empty(); }
    inline bool isConnected(PTPAttributeAction *action) const { return std::find(_connectedList.begin(), _connectedList.end(), action) != _connectedList.end(); }

    inline void setConnectable(bool state) { _connectable = state; }
    inline bool isConnectable() const { return _connectable; }

    static inline void toggleBackToUpdate(bool state) { _updateBackTo = state; }
    static inline bool isBackToUpdateEnabled() { return _updateBackTo; }

private:
    static bool _updateBackTo;

    std::vector<PTPAttributeAction*> _connectedList;

    bool _connectable;
};

#endif // PTPATTRIBUTEACTION_H
