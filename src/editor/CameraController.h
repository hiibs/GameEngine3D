#pragma once
#include "Behaviour.h"
class CameraController : public Behaviour {
public:
	CameraController(Object* owner) : Behaviour(owner) {}

	virtual void start() override { }
	virtual void update(float deltaTime) override;
};

