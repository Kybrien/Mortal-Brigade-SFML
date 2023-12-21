#pragma once
#include "Component.h"
#include <functional>

class CoolDown : public Component {
public:
	void SetFunc(const std::function<void()> _func) { func = _func; }
	void SetTimeToWait(float _timeToWait) { timeToWait = _timeToWait; }
	void Update(float _delta_time) override;
private:
	float timeToWait;
	float coolDown = 0.f;
	std::function<void()> func;
};