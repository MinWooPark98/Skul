#include "Collider.h"
#include "Player.h"

Collider::Collider()
	:type(Types::None)
{
}

Collider::~Collider()
{
}

void Collider::Init()
{
	Object::Init();
}

void Collider::SetType(Types type)
{
	this->type = type;
	switch (type)
	{
	case Types::TopSide:
		hitbox.setFillColor({ 0, 0, 255, 255 });
		break;
	case Types::AllSide:
		hitbox.setFillColor({ 255, 0, 0, 255 });
		break;
	}
}

void Collider::SetHitBox(const FloatRect rect)
{
	Object::SetHitBox(rect);
	if(type == Types::TopSide)
		hitbox.setFillColor({ 0, 0, 255, 255 });
}

