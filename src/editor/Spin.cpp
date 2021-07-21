#include "Spin.h"

void Spin::update(float deltaTime) {
	owner->rotation.z += deltaTime * 90.f;
}
