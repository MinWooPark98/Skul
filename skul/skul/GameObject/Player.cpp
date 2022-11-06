#include "Player.h"
#include "Skul/Skul.h"
#include "../Framework/InputMgr.h"
#include "../Framework/Utils.h"
#include "../Framework/RayCast.h"
#include "../Scene/SceneMgr.h"
#include "Collider.h"
#include "Enemy/Enemy.h"
#include "../Framework/SoundMgr.h"
#include "Skul/SkulSet.h"
#include "../DataTable/DataTableMGR.h"
#include "../DataTable/StatTable.h"
#include "Boss/Boss.h"

Player::Player()
	:mainSkul(nullptr), subSkul(nullptr),
	currState(States::None), isMoving(false), isDashing(false), isJumping(false), isAttacking(false), jumpingDown(false), dashAble(true), jumpCount(0), jumpableCount(2),
	dashTime(0.2f), dashTimer(0.f), doubleDashableTime(0.4f), doubleDashTimer(0.f), dashDelay(0.65f), dashDelayTimer(0.f), dashCount(0), dashableCount(0),
	currSpeed(200.f), lastDirX(1.f), attackDmg(25), totalHp(100), currHp(100), platform(nullptr), speed(200.f), skulSet(nullptr), speedAdd(0.f), attackAdd(0),
	isForcedMode(false), forcedAnimUpdate(true)
{
}

Player::~Player()
{
}

void Player::Init()
{
	SetName("player");
	direction = { 1.f, 0.f };
	gravityApply = true;
	gravity = 8.f;
	SetOrigin(Origins::BC);
	for (int i = 0; i < 3; ++i)
	{
		RayCast* ray = new RayCast();
		ray->SetDirection({ 0.f, 1.f });
		ray->SetRayLength(10.f);
		ray->SetLayerMask((int)Scene::Layer::Collider);
		rays.push_back(ray);
	}
	// 임시 hitbox size (default skul hitbox size 아래 사이즈로 고정)
	SetHitBox({ 0.f, 0.f, 20.f, 32.f });
	attackBox.setOutlineColor({ 0, 255, 0, 255 });
	attackBox.setOutlineThickness(2.f);
	attackBox.setFillColor({ 255, 255, 255, 0 });

	skulSet = new SkulSet();
	skulSet->Init();

	SpriteObj::Init();
}

void Player::Release()
{
	SpriteObj::Init();
}

void Player::Reset()
{
	SpriteObj::Reset();
	mainSkul = nullptr;
	subSkul = nullptr;
	subSkul = nullptr;
	isMoving = false;
	isDashing = false;
	isJumping = false;
	isAttacking = false;
	currSpeed = speed;
	currHp = totalHp;
	dashTimer = 0.f;
	dashCount = 0;
	doubleDashTimer = 0.f;
	dashDelayTimer = 0.f;
	jumpCount = 0;
	platform = nullptr;
	SetPos(startPos);
	skulSet->Reset();
}

void Player::Update(float dt)
{
	if (isForcedMode)
	{
		if(forcedAnimUpdate)
			mainSkul->Update(dt);
		Translate(direction * speed * dt);
		return;
	}

	if (InputMgr::GetKeyDown(Keyboard::Space))
	{
		if (subSkul == nullptr)
			ObtainMainSkul(Skul::Types::Werewolf, Skul::Tiers::Normal);
		else
			SwitchSkul();
	}

	if (InputMgr::GetKeyDown(Keyboard::Q))
		EvolveSkul();

	mainSkul->Update(dt);

	if (InputMgr::GetKeyDown(Keyboard::A))
	{
		SetState(States::SkillA);
		direction.y = 0.f;
	}
	else if (InputMgr::GetKeyDown(Keyboard::S))
	{
		SetState(States::SkillB);
		direction.y = 0.f;
	}

	if (currState == States::SkillA || currState == States::SkillB)
	{
		if (lastDirX > 0.f)
			sprite.setScale(1, 1);
		else if (lastDirX < 0.f)
			sprite.setScale(-1, 1);
		return;
	}

	gravityApply = true;
	SetBoxes();

	if (isDashing)
	{
		if (dashCount >= dashableCount)
			dashAble = false;

		dashTimer += dt;
		if (dashTimer > dashTime)
			currSpeed = 0.f;

		doubleDashTimer += dt;
		if (doubleDashTimer >= doubleDashableTime)
		{
			dashAble = false;
			isDashing = false;
			currSpeed = speed;
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

	if (InputMgr::GetKeyDown(Keyboard::Z) && dashCount < dashableCount && dashAble)
	{
		SetState(States::Dash);
		isDashing = true;
		if (currState == States::Dash)
			mainSkul->Dash();
		if (direction.x > 0.f)
			sprite.setScale(1, 1);
		else if (direction.x < 0.f)
			sprite.setScale(-1, 1);
		dashTimer = 0.f;
		doubleDashTimer = 0.f;
		currSpeed = speed * 2.f;
		++dashCount;
	}

	if (InputMgr::GetKeyDown(Keyboard::C) && jumpCount < jumpableCount)
	{
		isJumping = true;
		if (InputMgr::GetKey(Keyboard::Down))
			jumpingDown = true;
		else
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
	float inputX = 0.f;
	if(!InputMgr::GetKey(Keyboard::A) && !InputMgr::GetKey(Keyboard::D))
		inputX = InputMgr::GetAxisRaw(Axis::Horizontal);
	
	if (currState == States::Dash)
	{
		if (dashTimer >= dashTime && !(Utils::EqualFloat(inputX, 0.f)))
		{
			direction.x = inputX;
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
			if (lastDirX > 0.f)
				sprite.setScale(1, 1);
			else if (lastDirX < 0.f)
				sprite.setScale(-1, 1);
		}
		currSpeed = speed;
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
			if (Utils::EqualFloat(rays[i]->RayHitDistance(), 0.f) && rays[i]->GetHittingPoint().y - colliderBound.top < 25.f)
			{
				if (jumpingDown && ((Collider*)collider)->GetType() == Collider::Types::TopSide)
				{
					platform = collider;
					break;
				}
				gravityApply = false;
				direction.y = 0.f;
				position.y = colliderBound.top;
				isJumping = false;
				jumpCount = 0;
				platform = collider;
				break;
			}
		}
		platform = nullptr;
	}

	if (platform == nullptr)
		jumpingDown = false;

	Scene* playScene = SCENE_MGR->GetCurrentScene();
	auto& layOut = playScene->GetLayout();
	for (auto collider : *layOut[(int)Scene::Layer::Collider])
	{
		if (((Collider*)collider)->GetType() == Collider::Types::AllSide)
			OnCollisionBlock(collider->GetHitBounds());
	}

	Object::Update(dt);
	if (direction.y > 2.5f)
		direction.y = 2.5f;

	Translate(direction * currSpeed * dt);
}

void Player::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
	mainSkul->Draw(window);
	if (isDevMode)
	{
		window.draw(attackBox);
		for (auto ray : rays)
			ray->Draw(window);
	}
}

void Player::SetPos(const Vector2f& pos)
{
	SpriteObj::SetPos(pos);
	attackBox.setPosition(pos);
}

void Player::SwitchDevMode()
{
	Object::SwitchDevMode();
	mainSkul->SwitchDevMode();
}

void Player::ObtainMainSkul(Skul::Types type, Skul::Tiers tier)
{
	if (mainSkul != nullptr)
	{
		if (subSkul == nullptr)
			subSkul = mainSkul;
		//else
			// mainSkul, subSkul 다 꽉 차 있으면, 현재 mainSkul의 type, tier을 담은 머리 아이템 배출하는 기능 추가해야 함
	}
	SetMainSkul(skulSet->Get(type, tier));
	mainSkul->QuitAttackA = bind(&Player::OnCompleteAttackA, this);
	mainSkul->QuitAttackB = bind(&Player::OnCompleteAttackB, this);
	mainSkul->QuitAction = bind(&Player::SetState, this, States::Idle);
	if (ResetPlayerUi != nullptr)
		ResetPlayerUi();
}

void Player::SetMainSkul(Skul* skul)
{
	mainSkul = skul;
	mainSkul->SetPlayer(this);
	mainSkul->SetTarget(&sprite);
	ResetStat();
	SetState(States::Idle);
	mainSkul->Idle();
}

void Player::SetSubSkul(Skul::Types type, Skul::Tiers tier)
{
	subSkul = skulSet->Get(type, tier);
	subSkul->SetPlayer(this);
	subSkul->SetTarget(&sprite);
	subSkul->QuitAttackA = bind(&Player::OnCompleteAttackA, this);
	subSkul->QuitAttackB = bind(&Player::OnCompleteAttackB, this);
	subSkul->QuitAction = bind(&Player::SetState, this, States::Idle);
}

void Player::SwitchSkul()
{
	if (subSkul == nullptr)
		return;
	Skul* temp = mainSkul;
	SetMainSkul(subSkul);
	subSkul = temp;
	ResetPlayerUi();
	mainSkul->SwitchSkul();
}

bool Player::Evolvable()
{
	if (!skulSet->Evolvable(mainSkul))
		return false;
	return true;
}

bool Player::EvolveSkul()
{
	if (!Evolvable())
		return false;
	Skul* newSkul = skulSet->Get(mainSkul->GetType(), (Skul::Tiers)((int)mainSkul->GetTier() + 1));
	newSkul->SetSkillA(mainSkul->GetSkillA());
	newSkul->SetSkillB(mainSkul->GetSkillB());
	SetMainSkul(newSkul);
	mainSkul->QuitAttackA = bind(&Player::OnCompleteAttackA, this);
	mainSkul->QuitAttackB = bind(&Player::OnCompleteAttackB, this);
	mainSkul->QuitAction = bind(&Player::SetState, this, States::Idle);
	ResetPlayerUi();
	mainSkul->SwitchSkul();
	return true;
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
	case Player::States::SkillA:
		mainSkul->SkillA();
		break;
	case Player::States::SkillB:
		mainSkul->SkillB();
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

void Player::ResetStat()
{
	auto statTable = DATATABLE_MGR->Get<StatTable>(DataTable::Types::Stat);
	auto& stat = statTable->Get((int)mainSkul->GetOffType(), (int)mainSkul->GetTier());
	speed = stat.speed;
	attackDmg = stat.attackDmg;
	dashableCount = stat.dashableCount;
	BuffApply();
}

void Player::BuffApply()
{
	speed += speedAdd;
	attackDmg += attackAdd;
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

void Player::MeleeAttack(int dmg)
{
	auto attackBound = sprite.getGlobalBounds();
	attackBox.setSize({ attackBound.width, attackBound.height });
	Utils::SetOrigin(attackBox, Origins::BC);
	Scene* playScene = SCENE_MGR->GetCurrentScene();
	auto& layOut = playScene->GetLayout();
	for (auto enemy : *layOut[(int)Scene::Layer::Enemy])
	{
		if (!enemy->GetActive())
			continue;
		if (attackBox.getGlobalBounds().intersects(enemy->GetHitBounds()))
		{
			((Enemy*)enemy)->OnHit(dmg);
		}
	}
	for (auto boss : *layOut[(int)Scene::Layer::Boss])
	{
		if (!boss->GetActive())
			continue;
		if (attackBox.getGlobalBounds().intersects(boss->GetHitBounds()))
		{
			((Boss*)boss)->OnHit(dmg);
		}
	}
}

void Player::OnHit(int dmg)
{
	if (currState == States::Dash)
		return;
	currHp -= dmg;
		
	if (currHp <= 0)
	{
		SOUND_MGR->Play("sound/Dead.wav");
		SetActive(false);
		return;
	}
}
