#include "Collider.h"
#include "Player.h"

Collider::Collider()
	:type(Type::None)
{
}

Collider::~Collider()
{
}

void Collider::Init()
{
	Object::Init();
	isDevMode = true;
}

