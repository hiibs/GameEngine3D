#include "Behaviour.h"

Behaviour::Behaviour(Object* owner) :
	owner(owner)
{
	owner->addBehaviour(this);
}

Behaviour::~Behaviour() {
	owner->removeBehaviour(this);
}
