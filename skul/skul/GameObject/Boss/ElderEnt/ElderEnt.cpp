#include "ElderEnt.h"
#include "../../Framework/ResourceMgr.h"
#include "../../Framework/Animator.h"
#include "../../Scene/SceneMgr.h"
#include "../../SpriteObj.h"
#include "ElderEntHead.h"
#include "ElderEntJaw.h"
#include "ElderEntLeftHand.h"
#include "ElderEntRightHand.h"
#include "../../Framework/InputMgr.h"

ElderEnt::ElderEnt()
	:currphase(Phase::Phase1), currState(States::Idle), head(nullptr), jaw(nullptr), body(nullptr),
	leftHand(nullptr), rightHand(nullptr), totalHp(0), currHp(0), stompMaxCount(3), stompCount(0)
{
}

ElderEnt::~ElderEnt()
{
}

void ElderEnt::Init()
{
	Object::Init();

	bodyIdlePos = { 450.f, 280.f };

	body = new SpriteObj();
	body->Init();
	body->SetTexture(*RESOURCE_MGR->GetTexture("graphics/boss/elderent/body1.png"));
	body->SetOrigin(Origins::MC);

	head = new ElderEntHead();
	head->Init();
	head->SetMainBody(this);

	jaw = new ElderEntJaw();
	jaw->Init();
	jaw->SetMainBody(this);

	leftHand = new ElderEntLeftHand();
	leftHand->Init();
	leftHand->SetMainBody(this);

	rightHand = new ElderEntRightHand();
	rightHand->Init();
	rightHand->SetMainBody(this);

	SetPos(bodyIdlePos);

	auto& layOut = SCENE_MGR->GetScene(Scenes::BossScene)->GetLayout();
	layOut[(int)Scene::Layer::BackObject]->push_back(body);
}

void ElderEnt::Release()
{
}

void ElderEnt::Reset()
{
	Object::Reset();
}

void ElderEnt::Update(float dt)
{
	if (InputMgr::GetKeyDown(Keyboard::F2))
		SetState(States::NormalStomp);
	if (InputMgr::GetKeyDown(Keyboard::F3))
		SetState(States::Idle);
	Object::Update(dt);
	head->Update(dt);
	jaw->Update(dt);
	switch (currState)
	{
	case ElderEnt::States::Idle:
		leftHand->UpdateIdle(dt);
		rightHand->UpdateIdle(dt);
		break;
	case ElderEnt::States::NormalStomp:
		if (leftHand->GetAttackable() && rightHand->GetAttackable())
			Utils::RandomRange(0, 2) == 0 ? leftHand->NormalStomp() : rightHand->NormalStomp();
		leftHand->UpdateNormalStomp(dt);
		rightHand->UpdateNormalStomp(dt);
		break;
	case ElderEnt::States::Sweep:
		break;
	case ElderEnt::States::EnergyCorps:
		break;
	case ElderEnt::States::Groggy:
		break;
	case ElderEnt::States::WideStomp:
		break;
	case ElderEnt::States::Dead:
		break;
	case ElderEnt::States::Invincible:
		break;
	default:
		break;
	}
}

void ElderEnt::Draw(RenderWindow& window)
{
	Object::Draw(window);
	head->Draw(window);
	jaw->Draw(window);
	leftHand->Draw(window);
	rightHand->Draw(window);
	//effect draw
}

void ElderEnt::SetPos(const Vector2f& pos)
{
	Object::SetPos(pos);
	body->SetPos(pos);
	head->SetPos(pos);
	jaw->SetPos(pos);
}

void ElderEnt::SwitchDevMode()
{
	Object::SwitchDevMode();
	body->SwitchDevMode();
	head->SwitchDevMode();
	jaw->SwitchDevMode();
	leftHand->SwitchDevMode();
	rightHand->SwitchDevMode();
	/*for (auto branch : branches)
	{
		branch->SwitchDevMode();;
	}*/
}

void ElderEnt::SetState(States state)
{
	if (currState == state)
		return;
	currState = state;
	switch (state)
	{
	case ElderEnt::States::Idle:
		leftHand->ReturnIdlePos();
		rightHand->ReturnIdlePos();
		break;
	case ElderEnt::States::NormalStomp:
		leftHand->ReturnStompPos();
		rightHand->ReturnStompPos();
		break;
	case ElderEnt::States::Sweep:
		break;
	case ElderEnt::States::EnergyCorps:
		break;
	case ElderEnt::States::Groggy:
		break;
	case ElderEnt::States::WideStomp:
		break;
	case ElderEnt::States::Dead:
		break;
	case ElderEnt::States::Invincible:
		break;
	default:
		break;
	}
}

void ElderEnt::NextPhase()
{
	switch (currphase)
	{
	case ElderEnt::Phase::Phase1:
		SetState(States::Invincible);
		// animator에서 phace2로 갈 때 거 재생
		break;
	case ElderEnt::Phase::Phase2:
		SetState(States::Dead);
		break;
	default:
		break;
	}
}

void ElderEnt::OnHit(int dmg)
{
	currHp -= dmg;
	if (currHp < 0.f)
		NextPhase();
}
