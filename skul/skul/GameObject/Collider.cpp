#include "Collider.h"
#include "Player.h"

Collider::Collider()
	:type(Type::None), player(nullptr)
{
}

Collider::~Collider()
{
}

void Collider::Init()
{
	SetPos({ 0, 700.f });
	hitbox.setSize({ 10, 700.f });
}

void Collider::Update(float dt)
{
	if (player == nullptr)
		return;
	//if(player->GetDirection().y > 0.f && player->GetHitBounds().intersects(hitbox.getGlobalBounds()))

}

void Collider::SetPlayer(Player* player)
{
	this->player = player;
}
