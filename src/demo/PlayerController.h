#pragma once
#include "Behaviour.h"
class PlayerController : public Behaviour {
public:
	PlayerController(Object* owner) : Behaviour(owner) {}

	virtual void start() override { }
	virtual void update(float deltaTime) override;
};

