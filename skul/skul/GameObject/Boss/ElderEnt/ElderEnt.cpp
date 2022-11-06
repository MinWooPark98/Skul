#include "ElderEnt.h"
#include "../../Framework/ResourceMgr.h"
#include "../../Framework/Animator.h"
#include "../../Scene/SceneMgr.h"
#include "../../SpriteObj.h"
#include "ElderEntHead.h"
#include "ElderEntJaw.h"

ElderEnt::ElderEnt()
	:currphase(Phase::Phase1), head(nullptr), jaw(nullptr), body(nullptr),
	leftHand(nullptr), leftHandAnim(nullptr), rightHand(nullptr), rightHandAnim(nullptr), playerHit(false)
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
	body->SetTexture(*RESOURCE_MGR->GetTexture("graphics/boss/elderent/body1.png"));
	body->SetOrigin(Origins::MC);

	head = new ElderEntHead();
	head->Init();

	jaw = new ElderEntJaw();
	jaw->Init();

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
	Object::Update(dt);
	head->Update(dt);
	jaw->Update(dt);
}

void ElderEnt::Draw(RenderWindow& window)
{
	Object::Draw(window);
	head->Draw(window);
	jaw->Draw(window);
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
	/*leftHand->SwitchDevMode();
	rightHand->SwitchDevMode();
	for (auto branch : branches)
	{
		branch->SwitchDevMode();;
	}*/
}

void ElderEnt::SetState(States state)
{
	if (currState == state)
		return;
	switch (state)
	{
	case ElderEnt::States::Idle:
		break;
	case ElderEnt::States::NormalStomp:
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
