#include "Puff.h"

Puff::Puff(Scene* scene) : Billboard(scene),
	lifetime(0.3f),
	timer(0.f),
	direction(glm::vec3(0.f, 0.f, 1.f))
{
	Texture* tex = new Texture("Puff.png");
	Material* mat = new Material("Diffuse", tex);
	material = mat;

	setScale(glm::vec3(0.4f));
}

void Puff::update(float deltaTime) {
	Billboard::update(deltaTime);

	timer += deltaTime;

	setScale(getScale() + deltaTime*4.f);
	move(direction * deltaTime * 3.f);
	material->tint.w = 1.f - timer / lifetime;

	if (timer >= lifetime)
		delete this;
}
