#include "DefaultSkul.h"
#include "../../Framework/ResourceMgr.h"
#include "../Player.h"
#include "../../Scene/SceneMgr.h"
#include "../../Scene/PlayScene.h"

DefaultSkul::DefaultSkul()
	:Skul(Types::Default, Tiers::Normal)
{
}

DefaultSkul::~DefaultSkul()
{
}

void DefaultSkul::Init()
{
	Skul::Init();
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulIdle"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulWalk"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulDash"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulJump"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulFall"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulFallRepeat"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulAttackA"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulAttackB"));
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulJumpAttack"));
	PlayScene* playScene = (PlayScene*)SCENE_MGR->GetCurrentScene();
	Player* player = (Player*)playScene->FindGameObj("player");
	{
		AnimationEvent ev;
		ev.clipId = "DefaultSkulFall";
		ev.frame = ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulFall")->GetFrameCount() - 1;
		ev.onEvent = bind(&Skul::FallRepeated, this);
		animator->AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "DefaultSkulAttackA";
		ev.frame = ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulAttackA")->GetFrameCount() - 1;
		ev.onEvent = bind(&Skul::OnCompleteAttackA, this);
		animator->AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "DefaultSkulAttackB";
		ev.frame = ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulAttackB")->GetFrameCount() - 1;
		ev.onEvent = bind(&Skul::OnCompleteAttackB, this);
		animator->AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "DefaultSkulJumpAttack";
		ev.frame = ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulJumpAttack")->GetFrameCount() - 1;
		ev.onEvent = bind(&Skul::OnCompleteAttack, this);
		animator->AddEvent(ev);
	}
}

void DefaultSkul::SetAnimEvent(Player* player)
{
	AnimationEvent ev;
	ev.clipId = "DefaultSkulAttackA";
	ev.frame = 2;
	ev.onEvent = bind(&Player::MeleeAttack, player);
	animator->AddEvent(ev);
	AnimationEvent ev2;
	ev2.clipId = "DefaultSkulAttackB";
	ev2.frame = 1;
	ev2.onEvent = bind(&Player::MeleeAttack, player);
	animator->AddEvent(ev2);
	AnimationEvent ev3;
	ev3.clipId = "DefaultSkulJumpAttack";
	ev3.frame = 1;
	ev3.onEvent = bind(&Player::MeleeAttack, player);
	animator->AddEvent(ev3);
}
