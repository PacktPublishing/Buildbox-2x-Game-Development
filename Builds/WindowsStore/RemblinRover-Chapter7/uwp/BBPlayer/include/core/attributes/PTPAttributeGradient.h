#ifndef PTPATTRIBUTEGRADIENT_H
#define PTPATTRIBUTEGRADIENT_H

#include "PTPAttribute.h"

#include <unordered_map>
#include <utility>

class PTPAttributeGradient : public PTPAttribute {
public:
    PTPAttributeGradient(PTModel *node, PTPAttributeValueType valueType = PTPAttributeValueVariable);

    void initWithDictionary(CCDictionary *container);
    CCDictionary *getDictionary();

    void match(PTPAttribute *attribute);

    inline void setColor(float pos, const ccColor4F &color) { _gradient[pos] = color; }
    inline void eraseColor(float pos) { _gradient.erase(pos); }
    inline bool hasColor(float pos) const { return _gradient.count(pos); }
    inline ccColor4F color(float pos) const
    { std::unordered_map<float, ccColor4F>::const_iterator it = _gradient.find(pos); return it != _gradient.end() ? it->second : ccc4f(0, 0, 0, 1); }

    inline void setGradient(const std::unordered_map<float, ccColor4F> &gradient) { _gradient = gradient; }
    inline void setGradient(std::unordered_map<float, ccColor4F> &&gradient) { _gradient = std::move(gradient); }
    inline const std::unordered_map<float, ccColor4F>& gradient() const { return _gradient; }

    inline bool isEmpty() const { return _gradient.empty(); }

    inline bool isFixed() const { return _fixedState; }
    inline void setFixed(bool state) { _fixedState = state; }

private:
    std::unordered_map<float, ccColor4F> _gradient;

    bool _fixedState;
};

#endif // PTPATTRIBUTEGRADIENT_H
