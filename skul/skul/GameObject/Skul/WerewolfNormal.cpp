#include "WerewolfNormal.h"
#include "../../Framework/ResourceMgr.h"
#include "../Player.h"
#include "../../Scene/SceneMgr.h"
#include "../../Scene/PlayScene.h"
#include "../../Framework/SoundMgr.h"
#include "../../Scene/SceneMgr.h"
#include "../Collider.h"

WerewolfNormal::WerewolfNormal()
	:Skul(OffensiveTypes::Speed, Types::Werewolf, Tiers::Normal), skill(Skills::None)
{
}

WerewolfNormal::~WerewolfNormal()
{
}

void WerewolfNormal::Init()
{
	Skul::Init();
	SetSymbol(RESOURCE_MGR->GetTexture("graphics/player/werewolf/normal/symbol.png"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfNormalIdle"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfNormalWalk"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfNormalDash"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfNormalJump"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfNormalFall"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfNormalFallRepeat"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfNormalAttackA"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfNormalAttackB"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfNormalJumpAttack"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfNormalPredation"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfNormalRipper"));
	{
		AnimationEvent ev;
		ev.clipId = "WerewolfNormalFall";
		ev.frame = ResourceMgr::GetInstance()->GetAnimationClip("WerewolfNormalFall")->GetFrameCount() - 1;
		ev.onEvent = bind(&Skul::FallRepeated, this);
		animator->AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "WerewolfNormalAttackA";
		ev.frame = ResourceMgr::GetInstance()->GetAnimationClip("WerewolfNormalAttackA")->GetFrameCount() - 1;
		ev.onEvent = bind(&Skul::OnCompleteAttackA, this);
		animator->AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "WerewolfNormalAttackB";
		ev.frame = ResourceMgr::GetInstance()->GetAnimationClip("WerewolfNormalAttackB")->GetFrameCount() - 1;
		ev.onEvent = bind(&Skul::OnCompleteAttackB, this);
		animator->AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "WerewolfNormalJumpAttack";
		ev.frame = ResourceMgr::GetInstance()->GetAnimationClip("WerewolfNormalJumpAttack")->GetFrameCount() - 1;
		ev.onEvent = bind(&Skul::OnCompleteAction, this);
		animator->AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "WerewolfNormalPredation";
		ev.frame = ResourceMgr::GetInstance()->GetAnimationClip(ev.clipId)->GetFrameCount() - 1;
		ev.onEvent = bind(&Skul::OnCompleteAction, this);
		animator->AddEvent(ev);
		AnimationEvent ev2;
		ev2.clipId = "WerewolfNormalPredation";
		ev2.frame = 3;
		ev2.onEvent = bind(&WerewolfNormal::Predation, this);
		animator->AddEvent(ev2);
	}
	{
		AnimationEvent ev;
		ev.clipId = "WerewolfNormalRipper";
		ev.frame = ResourceMgr::GetInstance()->GetAnimationClip(ev.clipId)->GetFrameCount() - 1;
		ev.onEvent = bind(&Skul::OnCompleteAction, this);
		animator->AddEvent(ev);
		AnimationEvent ev2;
		ev2.clipId = "WerewolfNormalRipper";
		ev2.frame = 4;
		ev2.onEvent = bind(&WerewolfNormal::Ripper, this);
		animator->AddEvent(ev2);
	}
}

void WerewolfNormal::Reset()
{
	Skul::Reset();
	skill = (Skills)Utils::RandomRange(0, (int)Skills::Count);
	switch (skill)
	{
	case WerewolfNormal::Skills::Predation:
		SetSkillAIcon(RESOURCE_MGR->GetTexture("graphics/player/werewolf/normal/predation.png"));
		break;
	case WerewolfNormal::Skills::Ripper:
		SetSkillAIcon(RESOURCE_MGR->GetTexture("graphics/player/werewolf/normal/ripper.png"));
		break;
	}
}

void WerewolfNormal::SkillA()
{
	switch (skill)
	{
	case WerewolfNormal::Skills::Predation:
		animator->Play("WerewolfNormalPredation");
		break;
	case WerewolfNormal::Skills::Ripper:
		animator->Play("WerewolfNormalRipper");
		break;
	}
}

void WerewolfNormal::SkillB()
{
	player->SetState(Player::States::Idle);
}

void WerewolfNormal::SetAnimEvent()
{
	AnimationEvent ev;
	ev.clipId = "WerewolfNormalAttackA";
	ev.frame = 2;
	ev.onEvent = bind(&Player::NormalAttack, player);
	animator->AddEvent(ev);
	AnimationEvent ev2;
	ev2.clipId = "WerewolfNormalAttackB";
	ev2.frame = 2;
	ev2.onEvent = bind(&Player::NormalAttack, player);
	animator->AddEvent(ev2);
	AnimationEvent ev3;
	ev3.clipId = "WerewolfNormalJumpAttack";
	ev3.frame = 2;
	ev3.onEvent = bind(&Player::NormalAttack, player);
	animator->AddEvent(ev3);
}

void WerewolfNormal::Predation()
{
	auto playerDirX = Utils::UnitizationFloat(player->GetLastDirX());
	player->Translate({ player->GetGlobalBounds().width * playerDirX, 0.f});
	Scene* currScene = SCENE_MGR->GetCurrentScene();
	auto& layOut = currScene->GetLayout();
	for (auto obj : *layOut[(int)Scene::Layer::Collider])
	{
		if (((Collider*)obj)->GetType() != Collider::Types::AllSide)
			continue;
		if (player->GetHitBounds().intersects(obj->GetHitBounds()))
		{
			if (playerDirX > 0.f)
				player->SetPos({ obj->GetHitBounds().left - player->GetHitBounds().width * 0.5f, player->GetPos().y });
			else
				player->SetPos({ obj->GetHitBounds().left + obj->GetHitBounds().width + player->GetHitBounds().width * 0.5f, player->GetPos().y });
			break;
		}
	}
	player->MeleeAttack(player->GetAttackDmg() * 2);
}

void WerewolfNormal::Ripper()
{
	player->MeleeAttack(player->GetAttackDmg() * 2);
}
