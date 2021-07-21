#pragma once
#include "Behaviour.h"
class Spin : public Behaviour {
public:
	Spin(Object* owner) : Behaviour(owner) {}

	virtual void start() override { }
	virtual void update(float deltaTime) override;
};

