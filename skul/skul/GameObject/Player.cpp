#include "Player.h"
#include "Skul/Skul.h"
#include "../Framework/InputMgr.h"
#include "../Framework/Utils.h"

Player::Player()
	:mainSkul(nullptr), subSkul(nullptr),
	currState(States::None), isMoving(false), isDashing(false), isJumping(false), isAttacking(false), dashAble(true), jumpCount(0),
	dashTime(0.2f), dashTimer(0.f), doubleDashableTime(0.4f), doubleDashTimer(0.f), dashDelay(0.65f), dashDelayTimer(0.f), dashCount(0),
	speed(200.f), lastDirX(1.f)
{
}

Player::~Player()
{
}

void Player::Init()
{
	SetPos({ 1280.f / 2, 720.f });
	direction = { 1.f, 0.f };
	gravityApply = true;
	gravity = 8.f;
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
	Object::Update(dt);
	mainSkul->Update(dt);
	//// �ӽ� �浹 ó��
	//auto size = sprite.getGlobalBounds();
	//hitbox.setSize({ size.width, size.height });
	////

	// �߷�, �浹�������� ��ü�ؾ� ��
	if (position.y > 700.f)
	{
		position.y = 700.f;
		isJumping = false;
		jumpCount = 0;
		direction.y = 0.f;
	}

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

	if (currState != States::Attack && currState != States::Dash)
	{
		if (isJumping && direction.y > 0.f)
			SetState(States::Fall);
		if (!isJumping)
		{
			if (isMoving)
				SetState(States::Move);
			else
				SetState(States::Idle);
		}
	}

	float inputX = InputMgr::GetAxisRaw(Axis::Horizontal);
	if (currState == States::Dash)
	{
		if (dashTimer >= dashTime && !(Utils::EqualFloat(inputX, 0.f)))
		{
			direction.x = inputX;
			if (direction.x > 0.f)
				sprite.setScale(1, 1);
			else if (direction.x < 0.f)
				sprite.setScale(-1, 1);
			lastDirX = direction.x;
		}
		direction.x = lastDirX;
		direction.y = 0.f;
	}
	else
	{
		if (currState == States::Attack && !isJumping)
			direction.x = 0.f;
		else
		{
			direction.x = inputX;
			if (direction.x > 0.f)
				sprite.setScale(1, 1);
			else if (direction.x < 0.f)
				sprite.setScale(-1, 1);
		}
		speed = 200.f;
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
		mainSkul->Fall();
		break;
	default:
		break;
	}
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

