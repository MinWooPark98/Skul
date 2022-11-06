#include "ElderEntLeftHand.h"
#include "../../Framework/ResourceMgr.h"
#include "../../Framework/Animator.h"

ElderEntLeftHand::ElderEntLeftHand()
{
}

ElderEntLeftHand::~ElderEntLeftHand()
{
}

void ElderEntLeftHand::Init()
{
	ElderEntHand::Init();
	idlePos = { 270.f, 420.f };
	stompPos = { 270.f, 220.f };
	SetPos(idlePos);
	handAnim->AddClip(*RESOURCE_MGR->GetAnimationClip("ElderEntLeftHand1Idle"));
	handAnim->AddClip(*RESOURCE_MGR->GetAnimationClip("ElderEntLeftHand1CompleteStomp"));
	{
		AnimationEvent ev;
		ev.clipId = "ElderEntLeftHand1CompleteStomp";
		ev.frame = ResourceMgr::GetInstance()->GetAnimationClip(ev.clipId)->GetFrameCount() - 1;
		ev.onEvent = bind(&ElderEntHand::ReturnStompPos, this);
		handAnim->AddEvent(ev);
	}
	handAnim->Play("ElderEntLeftHand1Idle");
}

void ElderEntLeftHand::Update(float dt)
{
	ElderEntHand::Update(dt);
}

void ElderEntLeftHand::ReturnIdlePos()
{
	ElderEntHand::ReturnIdlePos();
	handAnim->Play("ElderEntLeftHand1Idle");
}

void ElderEntLeftHand::ReturnStompPos()
{
	ElderEntHand::ReturnStompPos();
	SetTexture(*RESOURCE_MGR->GetTexture("graphics/boss/elderent/fist_left1.png"));
	SetOrigin(Origins::BC);
}

void ElderEntLeftHand::OnCompleteStomp()
{
	ElderEntHand::OnCompleteStomp();
	handAnim->Play("ElderEntLeftHand1CompleteStomp");
}
