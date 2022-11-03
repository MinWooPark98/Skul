#include "Skul.h"
#include "../../Framework/SoundMgr.h"

Skul::Skul(OffensiveTypes offType, Types type, Tiers tier)
	:offType(offType), type(type), tier(tier), animator(nullptr), player(nullptr), symbol(nullptr), skillAIcon(nullptr), skillBIcon(nullptr)
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

void Skul::SetPlayer(Player* player)
{
	if (this->player != nullptr)
		return;
	this->player = player;
	SetAnimEvent();
}

void Skul::Dash()
{
	SOUND_MGR->Play("sound/Dash.wav");
}

void Skul::Jump()
{
	SOUND_MGR->Play("sound/Jump.wav");
}

void Skul::AttackA()
{
	SOUND_MGR->Play("sound/Skul_Atk_0.wav");
}

void Skul::AttackB()
{
	SOUND_MGR->Play("sound/Skul_Atk_1.wav");
}

void Skul::JumpAttack()
{
	SOUND_MGR->Play("sound/Skul_Jump_Atk.wav");
}
