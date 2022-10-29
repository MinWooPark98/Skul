#include "SwordsMan.h"
#include "../../Framework/RayCast.h"
#include "../../Framework/Framework.h"
#include "../../Framework/Animator.h"
#include "../../Framework/ResourceMgr.h"
#include "../../Scene/SceneMgr.h"
#include "../Player.h"

SwordsMan::SwordsMan()
	:Enemy(Types::SwordsMan), detectRange(nullptr), lastDirX(1.f), speed(100.f), attackDelay(2.f), attackTimer(2.f), changeDirDelay(3.f), changeDirTimer(0.f)
{
}

SwordsMan::~SwordsMan()
{
}

void SwordsMan::Init()
{
	Enemy::Init();
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("SwordsManIdle"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("SwordsManWalk"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("SwordsManAttack"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("SwordsManHit"));
	{
		AnimationEvent ev;
		ev.clipId = "SwordsManAttack";
		ev.frame = 1;
		ev.onEvent = bind(&SwordsMan::MeleeAttack, this);
		animator->AddEvent(ev);
		AnimationEvent ev2;
		ev2.clipId = "SwordsManAttack";
		ev2.frame = ResourceMgr::GetInstance()->GetAnimationClip("SwordsManAttack")->GetFrameCount() - 1;
		ev2.onEvent = bind(&SwordsMan::OnCompleteAttack, this);
		animator->AddEvent(ev2);
	}
	detectRange = new RayCast();
	detectRange->SetLayerMask((int)Scene::Layer::Player);
	detectRange->SetDirection({ lastDirX, 0.f });
	detectRange->SetRayLength(FRAMEWORK->GetWindowSize().x * 0.5f);
	SetHitBox({ 0.f, 0.f, 30.f, 50.f });
	attackBox.setOutlineColor({ 0, 255, 0, 255 });
	attackBox.setOutlineThickness(2.f);
	attackBox.setFillColor({ 255, 255, 255, 0 });
	isDevMode = true;
}

void SwordsMan::Release()
{
}

void SwordsMan::Reset()
{
	Enemy::Reset();
}

void SwordsMan::Update(float dt)
{
	Enemy::Update(dt);

	if (currState != States::Attack)
		attackBox.setSize({ 0.f, 0.f });
	Utils::SetOrigin(hitbox, Origins::BC);
	attackBox.setPosition(position);

	FloatRect hitBound = hitbox.getGlobalBounds();
	detectRange->SetStartPos({ hitBound.left + hitBound.width * 0.5f, hitBound.top + hitBound.height * 0.5f });
	detectRange->SetDirection(direction);
	detectRange->Update(dt);

	if (detectRange->RayHit())
	{
		attackTimer += dt;
		speed = 150.f;
		if (!playerDetected)
			playerDetected = true;
		if (detectRange->RayHitDistance() < 50.f)
		{
			if (attackTimer >= attackDelay)
				SetState(States::Attack);
		}
		direction.x = Utils::UnitizationFloat((detectRange->GetClosestObj()->GetPos().x) - position.x);
	}
	else
	{
		speed = 100.f;
		changeDirTimer += dt;
		if (changeDirTimer >= changeDirDelay)
		{
			if (Utils::EqualFloat(direction.x, 0.f))
			{
				int dirDraw = Utils::RandomRange(0, 2);
				if (dirDraw == 0)
					direction.x = -1.f;
				else
					direction.x = 1.f;
				lastDirX = direction.x;
			}
			else
				direction.x = 0.f;
			detectRange->SetDirection({ lastDirX, 0.f });
			changeDirTimer = 0.f;
		}
	}
	if (platform == nullptr)
		direction.x = 0.f;
	
	if (currState != States::Attack)
	{
		if (Utils::EqualFloat(direction.x, 0.f))
			SetState(States::Idle);
		else
			SetState(States::Move);
	}

	if (direction.x > 0.f)
		sprite.setScale(1, 1);
	else if (direction.x < 0.f)
		sprite.setScale(-1, 1);

	if(currState != States::Attack)
		Translate(speed * direction * dt);
}

void SwordsMan::Draw(RenderWindow& window)
{
	Enemy::Draw(window);
	if (isDevMode)
		window.draw(attackBox);
}

void SwordsMan::SetState(States newState)
{
	if (newState == currState)
		return;
	currState = newState;
	switch (currState)
	{
	case Enemy::States::Idle:
		animator->Play("SwordsManIdle");
		break;
	case Enemy::States::Move:
		animator->Play("SwordsManWalk");
		break;
	case Enemy::States::Attack:
		animator->Play("SwordsManAttack");
		break;
	case Enemy::States::Hit:
		animator->Play("SwordsManHit");
		break;
	default:
		break;
	}
}

void SwordsMan::MeleeAttack()
{
	attackBox.setSize({ sprite.getGlobalBounds().width, sprite.getGlobalBounds().height });
	Utils::SetOrigin(attackBox, Origins::BC);
	Scene* playScene = SCENE_MGR->GetCurrentScene();
	Player* player = (Player*)playScene->FindGameObj("player");
	//if (attackBox.getGlobalBounds().intersects(player->GetHitBounds()))
	//	player->SetActive(false); // 임시 테스트
}

void SwordsMan::OnCompleteAttack()
{
	attackTimer = 0.f;
	SetState(States::Idle);
	/*if (Utils::EqualFloat(direction.x, 0.f))
		SetState(States::Idle);
	else
		SetState(States::Move);*/
}
