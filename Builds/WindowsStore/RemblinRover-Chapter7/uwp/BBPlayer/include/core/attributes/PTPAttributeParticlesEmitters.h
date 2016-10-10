#ifndef PTPATTRIBUTEPARTICLESEMITTERS_H
#define PTPATTRIBUTEPARTICLESEMITTERS_H

#include "PTPAttribute.h"

#include <vector>
#include <algorithm>

class PTModelObjectAssetParticlesEmitter;

class PTPAttributeParticlesEmitters : public PTPAttribute {
public:
    PTPAttributeParticlesEmitters(PTModel *model, PTPAttributeValueType valueType = PTPAttributeValueExact);

    void initConnectionsWithDictionary(cocos2d::CCDictionary *dict);
    cocos2d::CCDictionary* getConnectionDictionary();

    void cleanup();

    inline void addEmitter(PTModelObjectAssetParticlesEmitter *emitter) { _emitters.push_back(emitter); }
    inline void removeEmitter(PTModelObjectAssetParticlesEmitter *emitter) { _emitters.erase(std::find(_emitters.begin(), _emitters.end(), emitter)); }

    inline const std::vector<PTModelObjectAssetParticlesEmitter*>& emitters() const { return _emitters; }

    virtual void match( PTPAttribute* attribute );
private:
    std::vector<PTModelObjectAssetParticlesEmitter*> _emitters;
};

#endif // PTPATTRIBUTEPARTICLESEMITTERS_H
