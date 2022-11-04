#include "WerewolfRare.h"
#include "../../Framework/ResourceMgr.h"
#include "../Player.h"
#include "../../Framework/SoundMgr.h"

WerewolfRare::WerewolfRare()
{
}

WerewolfRare::~WerewolfRare()
{
}

void WerewolfRare::Init()
{
	Werewolf::Init();
	tier = Tiers::Rare;
	SetSymbol(RESOURCE_MGR->GetTexture("graphics/player/werewolf/rare/symbol.png"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfRareIdle"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfRareWalk"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfRareDash"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfRareJump"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfRareFall"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfRareFallRepeat"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfRareAttackA"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfRareAttackB"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfRareJumpAttack"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfRarePredation"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfRareRipper"));
	{
		AnimationEvent ev;
		ev.clipId = "WerewolfRareFall";
		ev.frame = ResourceMgr::GetInstance()->GetAnimationClip("WerewolfRareFall")->GetFrameCount() - 1;
		ev.onEvent = bind(&Skul::FallRepeated, this);
		animator->AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "WerewolfRareAttackA";
		ev.frame = ResourceMgr::GetInstance()->GetAnimationClip("WerewolfRareAttackA")->GetFrameCount() - 1;
		ev.onEvent = bind(&Skul::OnCompleteAttackA, this);
		animator->AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "WerewolfRareAttackB";
		ev.frame = ResourceMgr::GetInstance()->GetAnimationClip("WerewolfRareAttackB")->GetFrameCount() - 1;
		ev.onEvent = bind(&Skul::OnCompleteAttackB, this);
		animator->AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "WerewolfRareJumpAttack";
		ev.frame = ResourceMgr::GetInstance()->GetAnimationClip("WerewolfRareJumpAttack")->GetFrameCount() - 1;
		ev.onEvent = bind(&Skul::OnCompleteAction, this);
		animator->AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "WerewolfRarePredation";
		ev.frame = ResourceMgr::GetInstance()->GetAnimationClip(ev.clipId)->GetFrameCount() - 1;
		ev.onEvent = bind(&Skul::OnCompleteAction, this);
		animator->AddEvent(ev);
		AnimationEvent ev2;
		ev2.clipId = "WerewolfRarePredation";
		ev2.frame = 3;
		ev2.onEvent = bind(&WerewolfRare::Predation, this);
		animator->AddEvent(ev2);
	}
	{
		AnimationEvent ev;
		ev.clipId = "WerewolfRareRipper";
		ev.frame = ResourceMgr::GetInstance()->GetAnimationClip(ev.clipId)->GetFrameCount() - 1;
		ev.onEvent = bind(&Skul::OnCompleteAction, this);
		animator->AddEvent(ev);
		AnimationEvent ev2;
		ev2.clipId = "WerewolfRareRipper";
		ev2.frame = 4;
		ev2.onEvent = bind(&WerewolfRare::Ripper, this);
		animator->AddEvent(ev2);
	}
}

void WerewolfRare::SkillA()
{
	switch (skillA)
	{
	case WerewolfRare::Skills::Predation:
		animator->Play("WerewolfRarePredation");
		break;
	case WerewolfRare::Skills::Ripper:
		animator->Play("WerewolfRareRipper");
		break;
	}
}

void WerewolfRare::SkillB()
{
	player->SetState(Player::States::Idle);
}

void WerewolfRare::SetSkillA(Skills skill)
{
	Werewolf::SetSkillA(skill);
	switch (skillA)
	{
	case WerewolfRare::Skills::Predation:
		SetSkillAIcon(RESOURCE_MGR->GetTexture("graphics/player/werewolf/rare/predation_2.png"));
		break;
	case WerewolfRare::Skills::Ripper:
		SetSkillAIcon(RESOURCE_MGR->GetTexture("graphics/player/werewolf/rare/ripper_2.png"));
		break;
	}
	if (player != nullptr && player->ResetPlayerUi != nullptr)
		player->ResetPlayerUi();
}

void WerewolfRare::SetAnimEvent()
{
	AnimationEvent ev;
	ev.clipId = "WerewolfRareAttackA";
	ev.frame = 2;
	ev.onEvent = bind(&Player::NormalAttack, player);
	animator->AddEvent(ev);
	AnimationEvent ev2;
	ev2.clipId = "WerewolfRareAttackB";
	ev2.frame = 2;
	ev2.onEvent = bind(&Player::NormalAttack, player);
	animator->AddEvent(ev2);
	AnimationEvent ev3;
	ev3.clipId = "WerewolfRareJumpAttack";
	ev3.frame = 2;
	ev3.onEvent = bind(&Player::NormalAttack, player);
	animator->AddEvent(ev3);
}
