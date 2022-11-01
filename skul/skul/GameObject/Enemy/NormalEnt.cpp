#include "NormalEnt.h"
#include "../../Framework/RayCast.h"
#include "../../Framework/Framework.h"
#include "../../Framework/Animator.h"
#include "../../Framework/ResourceMgr.h"
#include "../../Scene/SceneMgr.h"
#include "../Player.h"
#include "../../Ui/EnemyHpBarUi.h"
#include "../../Framework/SoundMgr.h"

NormalEnt::NormalEnt()
	:Enemy(Types::NormalEnt), detectingRay(nullptr), detectRange(160.f), attackRange(40.f), lastDirX(1.f), speed(0.f), normalSpeed(60.f), chasingSpeed(100.f),
	attackDelay(3.f), attackTimer(3.f), changeDirDelay(4.f), changeDirTimer(0.f)
{
}

NormalEnt::~NormalEnt()
{
}

void NormalEnt::Init()
{
	Enemy::Init();
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("NormalEntIdle"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("NormalEntWalk"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("NormalEntAttack"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("NormalEntHit"));
	{
		AnimationEvent ev;
		ev.clipId = "NormalEntAttack";
		ev.frame = 1;
		ev.onEvent = bind(&NormalEnt::MeleeAttack, this);
		animator->AddEvent(ev);
		AnimationEvent ev2;
		ev2.clipId = "NormalEntAttack";
		ev2.frame = ResourceMgr::GetInstance()->GetAnimationClip("NormalEntAttack")->GetFrameCount() - 1;
		ev2.onEvent = bind(&NormalEnt::OnCompleteAttack, this);
		animator->AddEvent(ev2);
	}
	detectingRay = new RayCast();
	detectingRay->SetLayerMask((int)Scene::Layer::Player);
	detectingRay->SetDirection({ lastDirX, 0.f });
	detectingRay->SetRayLength(detectRange);
	SetHitBox({ 0.f, 0.f, 40.f, 65.f });
	attackBox.setOutlineColor({ 0, 255, 0, 255 });
	attackBox.setOutlineThickness(2.f);
	attackBox.setFillColor({ 255, 255, 255, 0 });
	speed = normalSpeed;
	stiffDistance = 5.f;
	totalHp = 120;
	currHp = totalHp;
	hpBar->SetEnemy(this);
	hpBar->Init();
	attackDmg = 30;
}

void NormalEnt::Release()
{
}

void NormalEnt::Reset()
{
	Enemy::Reset();
}

void NormalEnt::Update(float dt)
{
	Enemy::Update(dt);

	if (currState != States::Attack)
		attackBox.setSize({ 0.f, 0.f });
	Utils::SetOrigin(hitbox, Origins::BC);
	attackBox.setPosition(position);

	FloatRect hitBound = hitbox.getGlobalBounds();
	detectingRay->SetStartPos({ hitBound.left + hitBound.width * 0.5f, hitBound.top + hitBound.height * 0.6f });
	detectingRay->SetDirection(direction);
	detectingRay->Update(dt);
	
	attackTimer += dt;
	if (currState != States::Hit)
	{
		Scene* currScene = SCENE_MGR->GetCurrentScene();
		if (detectingRay->RayHit())
		{
			if (!playerDetected)
			{
				playerDetected = true;
				auto& layOut = currScene->GetLayout();
				for (auto& obj : *layOut[(int)Scene::Layer::Enemy])
				{
					Enemy* enemy = (Enemy*)obj;
					if (enemy->GetPlatform() == platform)
						enemy->SetPlayerDetected(true);
				}
			}
			if (detectingRay->RayHitDistance() < attackRange)
			{
				if (attackTimer >= attackDelay)
					SetState(States::Attack);
			}
		}
		Player* player = (Player*)currScene->FindGameObj("player");
		if (player->GetPlatform() == platform)
		{
			if (player->GetActive())
			{
				speed = chasingSpeed;
				if (fabs(player->GetPos().x - position.x) >= player->GetHitBounds().width * 0.5f)
					direction.x = Utils::UnitizationFloat((player->GetPos().x) - position.x);
			}
		}
		else
		{
			speed = normalSpeed;
			changeDirTimer += dt;
			if (changeDirTimer >= changeDirDelay)
			{
				int dirDraw = Utils::RandomRange(0, 4);
				switch (dirDraw)
				{
				case 0:
					direction.x = -1.f;
					lastDirX = direction.x;
					break;
				case 1:
					direction.x = 1.f;
					lastDirX = direction.x;
					break;
				default:
					direction.x = 0.f;
					break;
				}
				detectingRay->SetDirection({ lastDirX, 0.f });
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

		if (currState != States::Attack)
			Translate(speed * direction * dt);

		if (direction.x > 0.f)
			sprite.setScale(1, 1);
		else if (direction.x < 0.f)
			sprite.setScale(-1, 1);
	}
	hpBar->SetPos(position);
}

void NormalEnt::Draw(RenderWindow& window)
{
	Enemy::Draw(window);
	if (isDevMode)
	{
		window.draw(attackBox);
		detectingRay->Draw(window);
	}
}

void NormalEnt::SetState(States newState)
{
	if (newState != States::Hit && newState == currState)
		return;
	currState = newState;
	switch (currState)
	{
	case Enemy::States::Idle:
		animator->Play("NormalEntIdle");
		break;
	case Enemy::States::Move:
		animator->Play("NormalEntWalk");
		break;
	case Enemy::States::Attack:
		animator->Play("NormalEntAttack");
		SOUND_MGR->Play("sound/Atk_Stomp.wav");
		break;
	case Enemy::States::Hit:
		animator->Play("NormalEntHit");
		break;
	default:
		break;
	}
}

void NormalEnt::MeleeAttack()
{
	attackBox.setSize({ sprite.getGlobalBounds().width, sprite.getGlobalBounds().height });
	Utils::SetOrigin(attackBox, Origins::BC);
	Scene* playScene = SCENE_MGR->GetCurrentScene();
	Player* player = (Player*)playScene->FindGameObj("player");
	attackTimer = 0.f;
	if (!player->GetActive())
		return;
	if (attackBox.getGlobalBounds().intersects(player->GetHitBounds()))
		player->OnHit(attackDmg);
}

void NormalEnt::OnCompleteAttack()
{
	SetState(States::Idle);
}
