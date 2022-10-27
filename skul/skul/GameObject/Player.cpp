#include "Player.h"
#include "Skul/Skul.h"
#include "../Framework/InputMgr.h"
#include "../Framework/Utils.h"

Player::Player()
	:mainSkul(nullptr), subSkul(nullptr),
	currState(States::None), isMoving(false), isDashing(false), isJumping(false), isAttacking(false), dashAble(true), jumpCount(0),
	dashTime(0.2f), dashTimer(0.f), doubleDashableTime(0.4f), doubleDashTimer(0.f), dashDelay(0.65f), dashDelayTimer(0.f), dashCount(0),
	speed(200.f), direction(1.f, 0.f), lastDirX(1.f)
{
}

Player::~Player()
{
}

void Player::Init()
{
	SetPos({ 1280.f / 2, 720.f });
	SetOrigin(Origins::BC);
}

void Player::Release()
{
}

void Player::Reset()
{
}

void Player::Update(float dt)
{
	mainSkul->Update(dt);

	if (isDashing)
	{
		if (dashCount > 1)
			dashAble = false;

		dashTimer += dt;
		if (dashTimer > dashTime)
			speed = 0.f;

		doubleDashTimer += dt;
		if (doubleDashTimer >= doubleDashableTime)
		{
			dashAble = false;
			isDashing = false;
			speed = 200.f;
			doubleDashTimer = 0.f;
			if (currState != States::Attack)
			{
				if (isJumping)
					SetState(States::Fall);
				else
					SetState(States::Idle);
			}
		}
	}
	if (!dashAble)
	{
		dashDelayTimer += dt;
		if (dashDelayTimer >= dashDelay)
		{
			dashAble = true;
			dashCount = 0;
			dashDelayTimer = 0.f;
		}
	}
	if (isJumping && currState != States::Attack && direction.y > 0.f)
		SetState(States::Fall);

	if (InputMgr::GetKeyDown(Keyboard::Z) && dashCount < 2 && dashAble)
	{
		SetState(States::Dash);
		isDashing = true;
		if (currState == States::Dash)
			mainSkul->Dash();
		dashTimer = 0.f;
		doubleDashTimer = 0.f;
		speed = 400.f;
		++dashCount;
	}

	if (InputMgr::GetKeyDown(Keyboard::C) && jumpCount < 2)
	{
		isJumping = true;
		direction.y = -2.5f;
		SetState(States::Jump);
		if (currState == States::Jump)
			mainSkul->Jump();
		++jumpCount;
	}

	if (InputMgr::GetKeyDown(Keyboard::X))
	{
		isAttacking = true;
		SetState(States::Attack);
	}

	switch (currState)
	{
	case Player::States::Idle:
		UpdateIdle(dt);
		break;
	case Player::States::Move:
		UpdateMove(dt);
		break;
	case Player::States::Jump:
		UpdateJump(dt);
		break;
	default:
		break;
	}

	if (currState == States::Dash)
	{
		direction.x = lastDirX;
		direction.y = 0.f;
	}
	else
	{
		if (currState == States::Attack && !isJumping)
			direction.x = 0.f;
		else
		{
			direction.x = InputMgr::GetAxisRaw(Axis::Horizontal);
			if (direction.x > 0.f)
				sprite.setScale(1, 1);
			else if (direction.x < 0.f)
				sprite.setScale(-1, 1);
		}
		speed = 200.f;

		if(position.y < 700.f)
			direction.y += dt * 8.f;
		if (direction.y > 5.f)
			direction.y = 5.f;
		if (position.y > 700.f)
		{
			position.y = 700.f;
			SetState(States::Idle);
			isJumping = false;
			jumpCount = 0;
			direction.y = 0.f;
		}
	}
	if (!(Utils::EqualFloat(direction.x, 0.f)))
	{
		lastDirX = direction.x;
		isMoving = true;
	}
	else
		isMoving = false;

	Translate(direction * speed * dt);
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
	mainSkul->QuitAttackA = bind(&Player::OnCompleteAttackA, this);
	mainSkul->QuitAttackB = bind(&Player::OnCompleteAttackB, this);
	mainSkul->QuitAttack = bind(&Player::SetState, this, States::Idle);
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
	case Player::States::Attack:
		isAttacking = false;
		if (isJumping)
			mainSkul->JumpAttack();
		else
			mainSkul->AttackA();
		break;
	case Player::States::Fall:
		mainSkul->FallRepeated();
		break;
	default:
		break;
	}
}

void Player::UpdateIdle(float dt)
{
	if (isMoving)
		SetState(States::Move);
}

void Player::UpdateMove(float dt)
{
	if (!isMoving)
		SetState(States::Idle);
}

void Player::UpdateJump(float dt)
{
	if (Utils::EqualFloat(direction.y, 0.f))
		mainSkul->Fall();
}

void Player::OnCompleteAttackA()
{
	if (isAttacking)
	{
		isAttacking = false;
		mainSkul->AttackB();
		return;
	}
	SetState(States::Idle);
}

void Player::OnCompleteAttackB()
{
	if (isAttacking)
	{
		isAttacking = false;
		mainSkul->AttackA();
		return;
	}
	SetState(States::Idle);
}

