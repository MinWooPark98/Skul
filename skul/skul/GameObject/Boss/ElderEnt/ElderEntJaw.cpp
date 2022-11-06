#include "ElderEntJaw.h"
#include "../../Framework/ResourceMgr.h"
#include "../../Framework/Animator.h"
#include "../../Framework/AnimationClip.h"
#include "ElderEnt.h"
#include "../../SpriteObj.h"

ElderEntJaw::ElderEntJaw()
	:jaw(nullptr), jawAnim(nullptr), mainBody(nullptr)
{
}

ElderEntJaw::~ElderEntJaw()
{
}

void ElderEntJaw::Init()
{
	jaw = new SpriteObj();
	jaw->Init();

	jawAnim = new Animator();
	jawAnim->AddClip(*RESOURCE_MGR->GetAnimationClip("ElderEntJaw1Idle"));
	jawAnim->SetTarget(&jaw->GetSprite());
	jawAnim->Play("ElderEntJaw1Idle");
	jaw->SetHitBox({ 0.f, 0.f, jaw->GetGlobalBounds().width, jaw->GetGlobalBounds().height });
	jaw->SetHitBoxOrigin(jawAnim->GetFrame().origin);
}

void ElderEntJaw::Update(float dt)
{
	jawAnim->Update(dt);
	jaw->SetHitBox({ 0.f, 0.f, jaw->GetGlobalBounds().width, jaw->GetGlobalBounds().height });
	jaw->SetHitBoxOrigin(jawAnim->GetFrame().origin);
}

void ElderEntJaw::Draw(RenderWindow& window)
{
	Object::Draw(window);
	jaw->Draw(window);
}

void ElderEntJaw::SetPos(const Vector2f& pos)
{
	Object::SetPos(pos);
	jaw->SetPos(pos);
}

void ElderEntJaw::OnHit(int dmg)
{
	mainBody->OnHit(dmg);
}
