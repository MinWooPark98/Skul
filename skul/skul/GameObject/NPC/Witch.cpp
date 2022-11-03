#include "Witch.h"
#include "../../Framework/Animator.h"
#include "../../Framework/ResourceMgr.h"
#include "../../Scene/SceneMgr.h"
#include "../TextObj.h"
#include "../Player.h"

Witch::Witch()
	:NPC(Types::Witch)
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
}

void Witch::Activate()
{
	Scene* currScene = SCENE_MGR->GetCurrentScene();
	Player* player = (Player*)currScene->FindGameObj("player");
	switch (Utils::RandomRange(0, 2))
	{
	case 0:
		player->SetSpeedAdd(100.f);
		break;
	case 1:
		player->SetAttackAdd(30);
		break;
	}
	player->BuffApply();
	++effectCnt;
}
