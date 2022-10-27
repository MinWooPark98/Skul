#include "DefaultSkul.h"
#include "../../Framework/ResourceMgr.h"

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
	{
		AnimationEvent ev;
		ev.clipId = "DefaultSkulJump";
		ev.frame = ResourceMgr::GetInstance()->GetAnimationClip("DefaultSkulJump")->GetFrameCount() - 1;
		ev.onEvent = bind(&Skul::Fall, this);
		animator->AddEvent(ev);
	}
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
