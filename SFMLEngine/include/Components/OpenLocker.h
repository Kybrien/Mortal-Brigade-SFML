#pragma once
#include "ProximityPrompt.h"
#include <functional>

class OpenLocker : public ProximityPrompt
{
public:
    void Prompt() override;
    void SetFunc(const std::function<void()> _func) { func = _func; }
private:
    std::function<void()> func;
};