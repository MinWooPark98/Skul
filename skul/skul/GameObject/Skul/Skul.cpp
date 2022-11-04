#include "Skul.h"
#include "../../Framework/SoundMgr.h"
#include "../../Framework/Utils.h"

Skul::Skul(OffensiveTypes offType, Types type, Tiers tier)
	:offType(offType), type(type), tier(tier), animator(nullptr), player(nullptr), symbol(nullptr),
	skillAIcon(nullptr), skillBIcon(nullptr), skillA(Skills::None), skillB(Skills::None)
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
	Object::Reset();
	player = nullptr;
	animator->Stop();
	skillA = Skills::None;
	skillB = Skills::None;
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
	if (tier >= Tiers::Unique && skillB == Skills::None)
		SetRandomSkillB();
	this->player = player;
	SetAnimEvent();
}

void Skul::SetRandomSkillA()
{
	SetSkillA(skillSet[Utils::RandomRange(0, skillSet.size())]);
}

void Skul::SetRandomSkillB()
{
	if (tier < Tiers::Unique)
		return;
	int vecIdx = -1;
	do {
		vecIdx = Utils::RandomRange(0, skillSet.size());
	} while (skillSet[vecIdx] == skillA);
	SetSkillB(skillSet[vecIdx]);
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
