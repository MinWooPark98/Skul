#include "ElderEntHead.h"
#include "../../Framework/ResourceMgr.h"
#include "../../Framework/Animator.h"
#include "ElderEnt.h"
#include "../../SpriteObj.h"

ElderEntHead::ElderEntHead()
	:head(nullptr), headAnim(nullptr), mainBody(nullptr)
{
}

ElderEntHead::~ElderEntHead()
{
}

void ElderEntHead::Init()
{
	head = new SpriteObj();
	head->Init();

	headAnim = new Animator();
	headAnim->AddClip(*RESOURCE_MGR->GetAnimationClip("ElderEntHead1Idle"));
	headAnim->SetTarget(&head->GetSprite());
	headAnim->Play("ElderEntHead1Idle");
	
	head->SetHitBox({ 0.f, 0.f, head->GetGlobalBounds().width, head->GetGlobalBounds().height });
	head->SetHitBoxOrigin(headAnim->GetFrame().origin);
}

void ElderEntHead::Update(float dt)
{
	headAnim->Update(dt);
	head->SetHitBox({ 0.f, 0.f, head->GetGlobalBounds().width, head->GetGlobalBounds().height });
	hitbox.setOrigin(headAnim->GetFrame().origin);
}

void ElderEntHead::Draw(RenderWindow& window)
{
	Object::Draw(window);
	head->Draw(window);
}

void ElderEntHead::SetPos(const Vector2f& pos)
{
	Object::SetPos(pos);
	head->SetPos(pos);
}

void ElderEntHead::OnHit(int dmg)
{
	mainBody->OnHit(dmg);
}
