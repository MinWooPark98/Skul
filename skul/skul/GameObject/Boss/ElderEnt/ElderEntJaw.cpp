#include "ElderEntJaw.h"
#include "../../Framework/ResourceMgr.h"
#include "../../Framework/Animator.h"
#include "../../Framework/AnimationClip.h"
#include "ElderEnt.h"

ElderEntJaw::ElderEntJaw()
	:jawAnim(nullptr), mainBody(nullptr)
{
}

ElderEntJaw::~ElderEntJaw()
{
}

void ElderEntJaw::Init()
{
	jawAnim = new Animator();
	jawAnim->AddClip(*RESOURCE_MGR->GetAnimationClip("ElderEntJaw1Idle"));
	jawAnim->SetTarget(&sprite);
	jawAnim->Play("ElderEntJaw1Idle");
	SetHitBox({ 0.f, 0.f, GetGlobalBounds().width, GetGlobalBounds().height });
	hitbox.setOrigin(jawAnim->GetFrame().origin);
}

void ElderEntJaw::Update(float dt)
{
	jawAnim->Update(dt);
	SetHitBox({ 0.f, 0.f, GetGlobalBounds().width, GetGlobalBounds().height });
	hitbox.setOrigin(jawAnim->GetFrame().origin);
}

void ElderEntJaw::OnHit(int dmg)
{
	mainBody->OnHit(dmg);
}
