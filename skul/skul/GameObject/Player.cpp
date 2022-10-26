#include "Player.h"
#include "Skul/Skul.h"

Player::Player()
	:mainSkul(nullptr), subSkul(nullptr),
	currState(States::None), isMoving(false), isDashing(false), isJumping(false), isAttacking(false), dashCount(0),
	speed(200.f), direction(-1.f, 0.f), lastDirection(-1.f, 0.f)
{
}

Player::~Player()
{
}

void Player::Init()
{
	SetPos({ 1280.f / 2, 720.f / 2 });
}

void Player::Release()
{
}

void Player::Reset()
{
}

void Player::Update(float dt)
{
	SetState(currState);
	mainSkul->Update(dt);
}

void Player::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}

void Player::SetSkul(Skul* skul)
{
	mainSkul = skul;
	mainSkul->SetTarget(&sprite);
	SetState(States::Idle);
}

void Player::SetState(States newState)
{
	if (newState == currState)
		return;
	currState = newState;
	switch (currState)
	{
	case Player::States::Idle:
		mainSkul->Idle();
		break;
	case Player::States::Move:
		mainSkul->Move();
		break;
	case Player::States::Dash:
		mainSkul->Dash();
		break;
	case Player::States::Jump:
		mainSkul->Jump();
		break;
	case Player::States::AttackA:
		mainSkul->AttackA();
		break;
	case Player::States::AttackB:
		mainSkul->AttackB();
		break;
	case Player::States::JumpAttack:
		mainSkul->JumpAttack();
		break;
	default:
		break;
	}
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

void Player::UpdatAttack(float dt)
{
}
