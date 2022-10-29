#include "Player.h"
#include "Skul/Skul.h"
#include "../Framework/InputMgr.h"
#include "../Framework/Utils.h"
#include "../Framework/RayCast.h"
#include "../Scene/SceneMgr.h"
#include "Collider.h"

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
	SpriteObj::Init();
	SetPos({ 1280.f / 2, 650.f });
	direction = { 1.f, 0.f };
	gravityApply = true;
	gravity = 8.f;
	SetOrigin(Origins::BC);
	for (int i = 0; i < 3; ++i)
	{
		RayCast* ray = new RayCast();
		ray->SetDirection({ 0.f, 1.f });
		ray->SetRayLength(1.0f);
		ray->SetLayerMask((int)Scene::Layer::Collider);
		rays.push_back(ray);
	}
	// 임시 hitbox size (default skul hitbox size 아래 사이즈로 고정)
	SetHitBox({ 0.f, 0.f, 20.f, 32.f });
	attackBox.setOutlineColor({ 0, 255, 0, 255 });
	attackBox.setOutlineThickness(2.f);
	attackBox.setFillColor({ 255, 255, 255, 0 });
	isDevMode = true;
}

void Player::Release()
{
}

void Player::Reset()
{
}

void Player::Update(float dt)
{
	gravityApply = true;
	mainSkul->Update(dt);
	SetBoxes();

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
		gravityApply = false;
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

	FloatRect hitBound = hitbox.getGlobalBounds();
	rays[0]->SetStartPos({ hitBound.left, hitBound.top + hitBound.height });
	rays[1]->SetStartPos({ hitBound.left + hitBound.width * 0.5f, hitBound.top + hitBound.height });
	rays[2]->SetStartPos({ hitBound.left + hitBound.width, hitBound.top + hitBound.height });
	for (int i = 0; i < 3; ++i)
	{
		if (direction.y < 0.f)
			break;
		rays[i]->Update(dt);
		if (rays[i]->RayHit())
		{
			auto collider = rays[i]->GetClosestObj();
			auto colliderBound = collider->GetHitBounds();
			if (Utils::EqualFloat(rays[i]->RayHitDistance(), 0.f) && rays[i]->GetHittingPoint().y - colliderBound.top < hitBound.height * 0.2f)
			{
				gravityApply = false;
				direction.y = 0.f;
				position.y = colliderBound.top;
				isJumping = false;
				jumpCount = 0;
				break;
			}
		}
	}
	Scene* playScene = SCENE_MGR->GetCurrentScene();
	auto& layOut = playScene->GetLayout();
	for (auto collider : *layOut[(int)Scene::Layer::Collider])
	{
		if (((Collider*)collider)->GetType() == Collider::Type::AllSide)
			OnCollisionBlock(collider->GetHitBounds());
	}

	Object::Update(dt);
	if (direction.y > 5.f)
		direction.y = 5.f;

	Translate(direction * speed * dt);
}

void Player::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
	if(isDevMode)
		window.draw(attackBox);
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

void Player::SetBoxes()
{
	if(currState != States::Attack)
		attackBox.setSize({ 0.f, 0.f });
	Utils::SetOrigin(hitbox, Origins::BC);
	attackBox.setPosition(position);
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

void Player::OnCollisionBlock(const FloatRect& blockBound)
{
	FloatRect hitBound = hitbox.getGlobalBounds();
	if (!hitBound.intersects(blockBound))
		return;
	Vector2f hitCenter(hitBound.left + hitBound.width * 0.5f, hitBound.top + hitBound.height * 0.5f);
	if (hitCenter.y - hitBound.height * 0.3f > blockBound.top + blockBound.height && direction.y < 0.f)
	{
		Translate({ 0.f, blockBound.top + blockBound.height - hitBound.top });
		direction.y = 0.f;
		return;
	}
	if (hitCenter.y + hitBound.height * 0.3f <= blockBound.top)
		return;

	if (hitCenter.x > blockBound.left + blockBound.width && direction.x < 0.f && hitBound.top + hitBound.height > blockBound.top)
	{
		Translate({ blockBound.left + blockBound.width - hitBound.left, 0.f });
		return;
	}
	else if (hitCenter.x < blockBound.left && direction.x > 0.f && hitBound.top < blockBound.top + blockBound.height)
	{
		Translate({ blockBound.left - (hitBound.left + hitBound.width), 0.f });
		return;
	}
}

void Player::MeleeAttack()
{
	attackBox.setSize({ sprite.getGlobalBounds().width, sprite.getGlobalBounds().height });
	Utils::SetOrigin(attackBox, Origins::BC);
	Scene* playScene = SCENE_MGR->GetCurrentScene();
	auto& layOut = playScene->GetLayout();
	for (auto enemy : *layOut[(int)Scene::Layer::Enemy])
	{
		// 적과 충돌 검사
	}
}
