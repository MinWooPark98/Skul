#include "ElderEntHead.h"
#include "../../Framework/ResourceMgr.h"
#include "../../Framework/Animator.h"
#include "ElderEnt.h"

ElderEntHead::ElderEntHead()
	:headAnim(nullptr), mainBody(nullptr)
{
}

ElderEntHead::~ElderEntHead()
{
}

void ElderEntHead::Init()
{
	headAnim = new Animator();
	headAnim->AddClip(*RESOURCE_MGR->GetAnimationClip("ElderEntHead1Idle"));
	headAnim->SetTarget(&sprite);
	headAnim->Play("ElderEntHead1Idle");
	SetHitBox({ 0.f, 0.f, GetGlobalBounds().width, GetGlobalBounds().height });
	hitbox.setOrigin(headAnim->GetFrame().origin);
}

void ElderEntHead::Update(float dt)
{
	headAnim->Update(dt);
	SetHitBox({ 0.f, 0.f, GetGlobalBounds().width, GetGlobalBounds().height });
	hitbox.setOrigin(headAnim->GetFrame().origin);
}

void ElderEntHead::OnHit(int dmg)
{
	mainBody->OnHit(dmg);
}
