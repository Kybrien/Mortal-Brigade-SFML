#include "Components/CoolDownComponent.h"
#include <iostream>

void CoolDown::Update(float _deltatime){
	coolDown += _deltatime;
	if (coolDown >= timeToWait) {
		coolDown = 0.f;
		func();
	}
}