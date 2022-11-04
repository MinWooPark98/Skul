#include "WerewolfUnique.h"
#include "../../Framework/ResourceMgr.h"
#include "../Player.h"
#include "../../Framework/SoundMgr.h"

WerewolfUnique::WerewolfUnique()
{
}

WerewolfUnique::~WerewolfUnique()
{
}

void WerewolfUnique::Init()
{
	Werewolf::Init();
	tier = Tiers::Unique;
	SetSymbol(RESOURCE_MGR->GetTexture("graphics/player/werewolf/unique/symbol.png"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfUniqueIdle"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfUniqueWalk"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfUniqueDash"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfUniqueJump"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfUniqueFall"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfUniqueFallRepeat"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfUniqueAttackA"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfUniqueAttackB"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfUniqueJumpAttack"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfUniquePredation"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WerewolfUniqueRipper"));
	{
		AnimationEvent ev;
		ev.clipId = "WerewolfUniqueFall";
		ev.frame = ResourceMgr::GetInstance()->GetAnimationClip("WerewolfUniqueFall")->GetFrameCount() - 1;
		ev.onEvent = bind(&Skul::FallRepeated, this);
		animator->AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "WerewolfUniqueAttackA";
		ev.frame = ResourceMgr::GetInstance()->GetAnimationClip("WerewolfUniqueAttackA")->GetFrameCount() - 1;
		ev.onEvent = bind(&Skul::OnCompleteAttackA, this);
		animator->AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "WerewolfUniqueAttackB";
		ev.frame = ResourceMgr::GetInstance()->GetAnimationClip("WerewolfUniqueAttackB")->GetFrameCount() - 1;
		ev.onEvent = bind(&Skul::OnCompleteAttackB, this);
		animator->AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "WerewolfUniqueJumpAttack";
		ev.frame = ResourceMgr::GetInstance()->GetAnimationClip("WerewolfUniqueJumpAttack")->GetFrameCount() - 1;
		ev.onEvent = bind(&Skul::OnCompleteAction, this);
		animator->AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "WerewolfUniquePredation";
		ev.frame = ResourceMgr::GetInstance()->GetAnimationClip(ev.clipId)->GetFrameCount() - 1;
		ev.onEvent = bind(&Skul::OnCompleteAction, this);
		animator->AddEvent(ev);
		AnimationEvent ev2;
		ev2.clipId = "WerewolfUniquePredation";
		ev2.frame = 3;
		ev2.onEvent = bind(&WerewolfUnique::Predation, this);
		animator->AddEvent(ev2);
	}
	{
		AnimationEvent ev;
		ev.clipId = "WerewolfUniqueRipper";
		ev.frame = ResourceMgr::GetInstance()->GetAnimationClip(ev.clipId)->GetFrameCount() - 1;
		ev.onEvent = bind(&Skul::OnCompleteAction, this);
		animator->AddEvent(ev);
		AnimationEvent ev2;
		ev2.clipId = "WerewolfUniqueRipper";
		ev2.frame = 4;
		ev2.onEvent = bind(&WerewolfUnique::Ripper, this);
		animator->AddEvent(ev2);
	}
}

void WerewolfUnique::Dash()
{
	Werewolf::Dash();
	animator->Play("WerewolfUniqueDash");
}

void WerewolfUnique::Jump()
{
	Werewolf::Jump();
	animator->Play("WerewolfUniqueJump");
}

void WerewolfUnique::AttackA()
{
	Werewolf::AttackA();
	animator->Play("WerewolfUniqueAttackA");
}

void WerewolfUnique::AttackB()
{
	Werewolf::AttackB();
	animator->Play("WerewolfUniqueAttackB");
}

void WerewolfUnique::JumpAttack()
{
	Werewolf::JumpAttack();
	animator->Play("WerewolfUniqueJumpAttack");
}

void WerewolfUnique::SkillA()
{
	switch (skillA)
	{
	case WerewolfUnique::Skills::Predation:
		animator->Play("WerewolfUniquePredation");
		break;
	case WerewolfUnique::Skills::Ripper:
		animator->Play("WerewolfUniqueRipper");
		break;
	}
	if (player != nullptr && player->ResetPlayerUi != nullptr)
		player->ResetPlayerUi();
}

void WerewolfUnique::SkillB()
{
	switch (skillB)
	{
	case WerewolfUnique::Skills::Predation:
		animator->Play("WerewolfUniquePredation");
		break;
	case WerewolfUnique::Skills::Ripper:
		animator->Play("WerewolfUniqueRipper");
		break;
	}
	if (player != nullptr && player->ResetPlayerUi != nullptr)
		player->ResetPlayerUi();
}

void WerewolfUnique::SetSkillA(Skills skill)
{
	Werewolf::SetSkillA(skill);
	switch (skillA)
	{
	case WerewolfUnique::Skills::Predation:
		SetSkillAIcon(RESOURCE_MGR->GetTexture("graphics/player/werewolf/unique/Predation_3.png"));
		break;
	case WerewolfUnique::Skills::Ripper:
		SetSkillAIcon(RESOURCE_MGR->GetTexture("graphics/player/werewolf/unique/Ripper_3.png"));
		break;
	}
	if (player != nullptr && player->ResetPlayerUi != nullptr)
		player->ResetPlayerUi();
}

void WerewolfUnique::SetSkillB(Skills skill)
{
	Werewolf::SetSkillB(skill);
	switch (skillB)
	{
	case WerewolfUnique::Skills::Predation:
		SetSkillBIcon(RESOURCE_MGR->GetTexture("graphics/player/werewolf/unique/Predation_3.png"));
		break;
	case WerewolfUnique::Skills::Ripper:
		SetSkillBIcon(RESOURCE_MGR->GetTexture("graphics/player/werewolf/unique/Ripper_3.png"));
		break;
	}
	if (player != nullptr && player->ResetPlayerUi != nullptr)
		player->ResetPlayerUi();
}

void WerewolfUnique::SetAnimEvent()
{
	AnimationEvent ev;
	ev.clipId = "WerewolfUniqueAttackA";
	ev.frame = 2;
	ev.onEvent = bind(&Player::NormalAttack, player);
	animator->AddEvent(ev);
	AnimationEvent ev2;
	ev2.clipId = "WerewolfUniqueAttackB";
	ev2.frame = 2;
	ev2.onEvent = bind(&Player::NormalAttack, player);
	animator->AddEvent(ev2);
	AnimationEvent ev3;
	ev3.clipId = "WerewolfUniqueJumpAttack";
	ev3.frame = 2;
	ev3.onEvent = bind(&Player::NormalAttack, player);
	animator->AddEvent(ev3);
}
