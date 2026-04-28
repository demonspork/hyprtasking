#pragma once

#include <hyprland/src/render/pass/PassElement.hpp>

class HTPassElement: public IPassElement {
  public:
    HTPassElement();
    virtual ~HTPassElement() = default;

    virtual std::vector<UP<IPassElement>> draw();
    virtual bool needsLiveBlur();
    virtual bool needsPrecomputeBlur();
    virtual bool disableSimplification();

    virtual ePassElementType type() {
        return EK_CUSTOM;
    }

    virtual const char* passName() {
        return "HTDisableSimplification";
    }
};
