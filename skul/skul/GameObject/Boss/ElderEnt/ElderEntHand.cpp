#include "ElderEntHand.h"
#include "../../Framework/Animator.h"
#include "../../Scene/SceneMgr.h"
#include "ElderEnt.h"
#include "../../Player.h"
#include "../../Scene/PlayScene.h"

ElderEntHand::ElderEntHand()
	:handAnim(nullptr), isReady(true), attackable(false), attackDmg(40), player(nullptr), playerHit(0), mainBody(nullptr),
	cameraShake(false), shakedelay(0.05f), shakeTimer(0.f), currShake(0), totalshake(20)
{
}

ElderEntHand::~ElderEntHand()
{
}

void ElderEntHand::Init()
{
	SpriteObj::Init();
	handAnim = new Animator();
	handAnim->SetTarget(&sprite);
	shakedView = { -20.f, 0.f };
}

void ElderEntHand::Update(float dt)
{
	SpriteObj::Update(dt);
	handAnim->Update(dt);
}

void ElderEntHand::Draw(RenderWindow& window)
{
	if(isDevMode)
		window.draw(attackBox);
	SpriteObj::Draw(window);
}

void ElderEntHand::ReturnIdlePos()
{
	if (!Utils::EqualFloat(position.x, idlePos.x) || !Utils::EqualFloat(position.y, idlePos.y))
	{
		SetDirection(Utils::Normalize(idlePos - position));
		isReady = false;
	}
}

void ElderEntHand::UpdateIdle(float dt)
{
	if (mainBody->GetState() != ElderEnt::States::Idle)
		return;

	Update(dt);
	if (!isReady)
	{
		Translate(direction * 200.f * dt);
		if (Utils::Distance(position, idlePos) <= 11.f)
		{
			SetPos(idlePos);
			direction = { 0.f, 0.f };
			isReady = true;
		}
	}
}

void ElderEntHand::ReturnStompPos()
{
	if (!Utils::EqualFloat(position.x, stompPos.x) || !Utils::EqualFloat(position.y, stompPos.y))
	{
		SetDirection(Utils::Normalize(stompPos - position));
		isReady = false;
	}
	handAnim->Stop();
}

void ElderEntHand::UpdateNormalStomp(float dt)
{
	if (mainBody->GetState() != ElderEnt::States::NormalStomp)
		return;

	Update(dt);
	if (!isReady)
	{
		Translate(direction * 200.f * dt);
		if (Utils::Distance(position, stompPos) <= 11.f)
		{
			SetPos(stompPos);
			direction = { 0.f, 0.f };
			isReady = true;
			attackable = true;
			if (mainBody->GetStompCnt() >= mainBody->GetStompMaxCnt())
			{
				mainBody->SetStompCnt(0);
				mainBody->SetState(ElderEnt::States::Idle);
				attackable = false;
			}
		}
		return;
	}
	if (cameraShake)
	{
		auto currScene = SCENE_MGR->GetCurrentScene();
		shakeTimer += dt;
		if (shakeTimer >= shakedelay)
		{
			shakeTimer = 0.f;
			++currShake;
			float degree = Utils::RandomRange(10.f, 20.f);
			shakedView.x = shakedView.x > 0.f ? -degree : degree;
			if (currShake >= totalshake)
			{
				currShake = 0;
				cameraShake = false;
				OnCompleteStomp();
			}
		}
		currScene->SetWorldViewCenter(player->GetPos() + shakedView);
		return;
	}

	Translate(direction * 500.f * dt);
	attackBox.setPosition(position);
	if (player != nullptr && !playerHit)
	{
		if (attackBox.getGlobalBounds().intersects(player->GetHitBounds()))
		{
			player->OnHit(attackDmg);
			playerHit = true;
		}
	}

	if (position.y > 420.f)
	{
		SetPos({ position.x, 420.f });
		direction = { 0.f, 0.f };
		CameraShake();	// 카메라 흔드는 효과 시야 막힌 지점에선 안 떨림, scene에서 흔들림효과 제어하기
		attackBox.setSize({ 0.f, 0.f });
		mainBody->AddStompCnt();
		playerHit = false;
	}
}

void ElderEntHand::OnCompleteStomp()
{
	auto currScene = SCENE_MGR->GetCurrentScene();
	((PlayScene*)currScene)->SetViewFollowPlayer(true);
}

void ElderEntHand::CameraShake()
{
	cameraShake = true;
	auto currScene = SCENE_MGR->GetCurrentScene();
	((PlayScene*)currScene)->SetViewFollowPlayer(false);
}

void ElderEntHand::NormalStomp()
{
	auto currScene = SCENE_MGR->GetCurrentScene();
	player = (Player*)currScene->FindGameObj("player");
	SetDirection(Utils::Normalize(player->GetPos() - position));
	attackBox.setSize({ GetGlobalBounds().width, GetGlobalBounds().height });
	Utils::SetOrigin(attackBox, Origins::BC);
	attackable = false;
}
