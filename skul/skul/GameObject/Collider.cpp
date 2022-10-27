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
	SetPos({ 0, 700.f });
	hitbox.setSize({ 1280.f, 64.f });
}

