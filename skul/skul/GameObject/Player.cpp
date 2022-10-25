#include "Player.h"
#include "../Framework/ResourceMgr.h"

Player::Player()
	:type(Types::None), tier(Tiers::None), skul(nullptr),
	currState(States::None), isMoving(false), isDashing(false), isFloating(false), isAttacking(false), dashCount(0),
	speed(200.f), direction(-1.f, 0.f), lastDirection(-1.f, 0.f)
{
}

Player::~Player()
{
}

void Player::Init()
{
	SetPos({ 1280.f / 2, 720.f / 2 });
	skul = new Animator();
	skul->SetTarget(&sprite);
	skul->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("Idle"));
	skul->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("IdleLeft"));
	SetState(States::Idle);
}

void Player::Release()
{
}

void Player::Reset()
{
}

void Player::Update(float dt)
{
	skul->Update(dt);
}

void Player::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}

void Player::SetState(States newState)
{
	skul->Play("Idle");
}

void Player::UpdateIdle(float dt)
{
}

void Player::UpdateMove(float dt)
{
}

void Player::UpdateDash(float dt)
{
}

void Player::UpdateJump(float dt)
{
}

void Player::UpdateFall(float dt)
{
}

void Player::UpdatAttack(float dt)
{
}
