#include "WerewolfNormal.h"
#include "../../Framework/ResourceMgr.h"
#include "../Player.h"
#include "../../Framework/SoundMgr.h"

WerewolfNormal::WerewolfNormal()
{
}

WerewolfNormal::~WerewolfNormal()
{
}

void WerewolfNormal::Init()
{
	Werewolf::Init();
	tier = Tiers::Normal;
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
	Werewolf::Reset();
	SetRandomSkillA();
}

void WerewolfNormal::Dash()
{
	Werewolf::Dash();
	animator->Play("WerewolfNormalDash");
}

void WerewolfNormal::Jump()
{
	Werewolf::Jump();
	animator->Play("WerewolfNormalJump");
}

void WerewolfNormal::AttackA()
{
	Werewolf::AttackA();
	animator->Play("WerewolfNormalAttackA");
}

void WerewolfNormal::AttackB()
{
	Werewolf::AttackB();
	animator->Play("WerewolfNormalAttackB");
}

void WerewolfNormal::JumpAttack()
{
	Werewolf::JumpAttack();
	animator->Play("WerewolfNormalJumpAttack");
}

void WerewolfNormal::SkillA()
{
	switch (skillA)
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

void WerewolfNormal::SetSkillA(Skills skill)
{
	Werewolf::SetSkillA(skill);
	switch (skillA)
	{
	case WerewolfNormal::Skills::Predation:
		SetSkillAIcon(RESOURCE_MGR->GetTexture("graphics/player/werewolf/normal/Predation.png"));
		break;
	case WerewolfNormal::Skills::Ripper:
		SetSkillAIcon(RESOURCE_MGR->GetTexture("graphics/player/werewolf/normal/Ripper.png"));
		break;
	}
	if(player != nullptr && player->ResetPlayerUi != nullptr)
		player->ResetPlayerUi();
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
