#include "WerewolfLegendary.h"
#include "../../Framework/ResourceMgr.h"
#include "../Player.h"
#include "../../Framework/SoundMgr.h"

WerewolfLegendary::WerewolfLegendary()
{
}

WerewolfLegendary::~WerewolfLegendary()
{
}

void WerewolfLegendary::Init()
{
	Werewolf::Init();
	tier = Tiers::Legendary;
	SetSymbol(RESOURCE_MGR->GetTexture("graphics/player/werewolf/legendary/symbol.png"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfLegendaryIdle"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfLegendaryWalk"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfLegendaryDash"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfLegendaryJump"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfLegendaryFall"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfLegendaryFallRepeat"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfLegendaryAttackA"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfLegendaryAttackB"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfLegendaryJumpAttack"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfLegendaryPredation"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfLegendaryRipper"));
	{
		AnimationEvent ev;
		ev.clipId = "WerewolfLegendaryFall";
		ev.frame = ResourceMgr::GetInstance()->GetAnimationClip("WerewolfLegendaryFall")->GetFrameCount() - 1;
		ev.onEvent = bind(&Skul::FallRepeated, this);
		animator->AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "WerewolfLegendaryAttackA";
		ev.frame = ResourceMgr::GetInstance()->GetAnimationClip("WerewolfLegendaryAttackA")->GetFrameCount() - 1;
		ev.onEvent = bind(&Skul::OnCompleteAttackA, this);
		animator->AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "WerewolfLegendaryAttackB";
		ev.frame = ResourceMgr::GetInstance()->GetAnimationClip("WerewolfLegendaryAttackB")->GetFrameCount() - 1;
		ev.onEvent = bind(&Skul::OnCompleteAttackB, this);
		animator->AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "WerewolfLegendaryJumpAttack";
		ev.frame = ResourceMgr::GetInstance()->GetAnimationClip("WerewolfLegendaryJumpAttack")->GetFrameCount() - 1;
		ev.onEvent = bind(&Skul::OnCompleteAction, this);
		animator->AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "WerewolfLegendaryPredation";
		ev.frame = ResourceMgr::GetInstance()->GetAnimationClip(ev.clipId)->GetFrameCount() - 1;
		ev.onEvent = bind(&Skul::OnCompleteAction, this);
		animator->AddEvent(ev);
		AnimationEvent ev2;
		ev2.clipId = "WerewolfLegendaryPredation";
		ev2.frame = 3;
		ev2.onEvent = bind(&WerewolfLegendary::Predation, this);
		animator->AddEvent(ev2);
	}
	{
		AnimationEvent ev;
		ev.clipId = "WerewolfLegendaryRipper";
		ev.frame = ResourceMgr::GetInstance()->GetAnimationClip(ev.clipId)->GetFrameCount() - 1;
		ev.onEvent = bind(&Skul::OnCompleteAction, this);
		animator->AddEvent(ev);
		AnimationEvent ev2;
		ev2.clipId = "WerewolfLegendaryRipper";
		ev2.frame = 4;
		ev2.onEvent = bind(&WerewolfLegendary::Ripper, this);
		animator->AddEvent(ev2);
	}
}

void WerewolfLegendary::SkillA()
{
	switch (skillA)
	{
	case WerewolfLegendary::Skills::Predation:
		animator->Play("WerewolfLegendaryPredation");
		break;
	case WerewolfLegendary::Skills::Ripper:
		animator->Play("WerewolfLegendaryRipper");
		break;
	}
	if (player != nullptr && player->ResetPlayerUi != nullptr)
		player->ResetPlayerUi();
}

void WerewolfLegendary::SkillB()
{
	switch (skillB)
	{
	case WerewolfLegendary::Skills::Predation:
		animator->Play("WerewolfLegendaryPredation");
		break;
	case WerewolfLegendary::Skills::Ripper:
		animator->Play("WerewolfLegendaryRipper");
		break;
	}
	if (player != nullptr && player->ResetPlayerUi != nullptr)
		player->ResetPlayerUi();
}

void WerewolfLegendary::SetSkillA(Skills skill)
{
	Werewolf::SetSkillA(skill);
	switch (skillA)
	{
	case WerewolfLegendary::Skills::Predation:
		SetSkillAIcon(RESOURCE_MGR->GetTexture("graphics/player/werewolf/legendary/Predation_4.png"));
		break;
	case WerewolfLegendary::Skills::Ripper:
		SetSkillAIcon(RESOURCE_MGR->GetTexture("graphics/player/werewolf/legendary/Ripper_4.png"));
		break;
	}
	if (player != nullptr && player->ResetPlayerUi != nullptr)
		player->ResetPlayerUi();
}

void WerewolfLegendary::SetSkillB(Skills skill)
{
	Werewolf::SetSkillB(skill);
	switch (skillB)
	{
	case WerewolfLegendary::Skills::Predation:
		SetSkillBIcon(RESOURCE_MGR->GetTexture("graphics/player/werewolf/legendary/Predation_4.png"));
		break;
	case WerewolfLegendary::Skills::Ripper:
		SetSkillBIcon(RESOURCE_MGR->GetTexture("graphics/player/werewolf/legendary/Ripper_4.png"));
		break;
	}
	if (player != nullptr && player->ResetPlayerUi != nullptr)
		player->ResetPlayerUi();
}

void WerewolfLegendary::SetAnimEvent()
{
	AnimationEvent ev;
	ev.clipId = "WerewolfLegendaryAttackA";
	ev.frame = 2;
	ev.onEvent = bind(&Player::NormalAttack, player);
	animator->AddEvent(ev);
	AnimationEvent ev2;
	ev2.clipId = "WerewolfLegendaryAttackB";
	ev2.frame = 2;
	ev2.onEvent = bind(&Player::NormalAttack, player);
	animator->AddEvent(ev2);
	AnimationEvent ev3;
	ev3.clipId = "WerewolfLegendaryJumpAttack";
	ev3.frame = 2;
	ev3.onEvent = bind(&Player::NormalAttack, player);
	animator->AddEvent(ev3);
}
