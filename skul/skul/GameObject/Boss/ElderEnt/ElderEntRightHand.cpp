#include "ElderEntRightHand.h"
#include "../../Framework/ResourceMgr.h"
#include "../../Framework/Animator.h"

ElderEntRightHand::ElderEntRightHand()
{
}

ElderEntRightHand::~ElderEntRightHand()
{
}

void ElderEntRightHand::Init()
{
	ElderEntHand::Init();
	idlePos = { 630.f, 420.f };
	stompPos = { 630.f, 220.f };
	SetPos(idlePos);
	handAnim->AddClip(*RESOURCE_MGR->GetAnimationClip("ElderEntRightHand1Idle"));
	handAnim->AddClip(*RESOURCE_MGR->GetAnimationClip("ElderEntRightHand1CompleteStomp"));
	{
		AnimationEvent ev;
		ev.clipId = "ElderEntRightHand1CompleteStomp"; 
		ev.frame = ResourceMgr::GetInstance()->GetAnimationClip(ev.clipId)->GetFrameCount() - 1;
		ev.onEvent = bind(&ElderEntHand::ReturnStompPos, this);
		handAnim->AddEvent(ev);
	}
	handAnim->Play("ElderEntRightHand1Idle");
}

void ElderEntRightHand::Update(float dt)
{
	ElderEntHand::Update(dt);
}

void ElderEntRightHand::ReturnIdlePos()
{
	ElderEntHand::ReturnIdlePos();
	handAnim->Play("ElderEntRightHand1Idle");
}

void ElderEntRightHand::ReturnStompPos()
{
	ElderEntHand::ReturnStompPos();
	SetTexture(*RESOURCE_MGR->GetTexture("graphics/boss/elderent/fist_right1.png"));
	SetOrigin(Origins::BC);
}

void ElderEntRightHand::OnCompleteStomp()
{
	ElderEntHand::OnCompleteStomp();
	handAnim->Play("ElderEntRightHand1CompleteStomp");
}
