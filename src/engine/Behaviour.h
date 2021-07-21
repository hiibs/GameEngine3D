#pragma once
#include "Object.h"
#include "Input.h"

class Behaviour
{
public:
	Behaviour(Object* owner);
	~Behaviour();

	virtual void start() = 0;
	virtual void update(float deltaTime) = 0;

protected:
	Object* owner;

	const Input* getInput() const;
};

