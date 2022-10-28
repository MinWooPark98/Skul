#include "Enemy.h"
#include "../Framework/Animator.h"

Enemy::Enemy()
	:type(Types::None), animator(nullptr), playerDetected(false)
{
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
	SpriteObj::Init();
	animator = new Animator();
}

void Enemy::Release()
{
}

void Enemy::Reset()
{
}

void Enemy::Update(float dt)
{
}

void Enemy::Draw(RenderWindow& window)
{
}
