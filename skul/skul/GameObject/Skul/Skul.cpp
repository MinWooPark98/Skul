#include "Skul.h"

Skul::Skul(Types type, Tiers tier)
	:type(type), tier(tier), animator(nullptr), player(nullptr), symbol(nullptr)
{
}

Skul::~Skul()
{
}

void Skul::Init()
{
	animator = new Animator();
}

void Skul::Release()
{
	if (animator != nullptr)
	{
		delete animator;
		animator = nullptr;
	}
}

void Skul::Reset()
{
	animator->Stop();
}

void Skul::Update(float dt)
{
	Object::Update(dt);
	animator->Update(dt);
}

void Skul::OnCompleteAttackA()
{
	if (QuitAttackA != nullptr)
		QuitAttackA();
}

void Skul::OnCompleteAttackB()
{
	if (QuitAttackB != nullptr)
		QuitAttackB();
}

void Skul::OnCompleteAction()
{
	if (QuitAction != nullptr)
		QuitAction();
}
