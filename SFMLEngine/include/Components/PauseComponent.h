#pragma once
#include <functional>
#include "Component.h"

class PauseComponent : public Component {
public:
    void Execute(std::function<void()> _func) { execute = _func; }

    void Update(float _delta_time) override;

private:
    bool IsPaused = false;
    bool IsPressed = false;
    std::function<void()> execute;
};