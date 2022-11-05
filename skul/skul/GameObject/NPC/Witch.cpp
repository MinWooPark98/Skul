#include "Witch.h"
#include "../../Framework/Animator.h"
#include "../../Framework/ResourceMgr.h"
#include "../../Scene/SceneMgr.h"
#include "../TextObj.h"
#include "../Player.h"

Witch::Witch()
	:NPC(Types::Witch), applyingEffect(nullptr), effectInformTime(2.f), effectInformTimer(0.f), isActive(false)
{
}

Witch::~Witch()
{
}

void Witch::Init()
{
	NPC::Init();
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("WitchIdle"));
	animator->Play("WitchIdle");
	SetHitBox({ 0.f, 0.f, 135.f, 106.f });
	effectLimitCnt = 1;

	applyingEffect = new TextObj();
	applyingEffect->Init();
	applyingEffect->SetActive(false);
	applyingEffect->SetFont(*RESOURCE_MGR->GetFont("fonts/NotoSansKR-Bold.otf"));
	applyingEffect->SetSize(10.f);
	applyingEffect->SetOutlineColor({ 0, 0, 0, 255 });
	applyingEffect->SetOutlineThickness(2.f);
}

void Witch::Reset()
{
	NPC::Reset();
	isActive = false;
	effectInformTimer = 0.f;
}

void Witch::Update(float dt)
{
	NPC::Update(dt);
	if (isActive)
	{
		effectInformTimer += dt;
		if (effectInformTimer >= effectInformTime)
			applyingEffect->SetActive(false);
	}
}

void Witch::Draw(RenderWindow& window)
{
	NPC::Draw(window);
	if(applyingEffect->GetActive())
		applyingEffect->Draw(window);
}

void Witch::Activate()
{
	switch (Utils::RandomRange(0, 2))
	{
	case 0:
		player->SetSpeedAdd(100.f);
		applyingEffect->SetText("이동속도 증가");
		break;
	case 1:
		player->SetAttackAdd(30);
		applyingEffect->SetText("공격력 증가");
		break;
	}
	isActive = true;
	applyingEffect->AsciiToUnicode();
	auto bound = GetGlobalBounds();
	applyingEffect->SetOrigin(Origins::MC);
	applyingEffect->SetPos({ bound.left + bound.width * 0.5f, bound.top + bound.height * 0.5f });
	applyingEffect->SetActive(true);
	player->BuffApply();
	++effectCnt;
}
