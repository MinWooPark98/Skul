#include "FoxHuman.h"
#include "../../Framework/Animator.h"
#include "../../Framework/ResourceMgr.h"
#include "../../Scene/SceneMgr.h"
#include "../TextObj.h"
#include "../Player.h"

FoxHuman::FoxHuman()
	:NPC(Types::FoxHuman)
{
}

FoxHuman::~FoxHuman()
{
}

void FoxHuman::Init()
{
	NPC::Init();
	animator->AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("FoxHumanIdle"));
	animator->Play("FoxHumanIdle");
	SetHitBox({ 0.f, 0.f, 217.f, 144.f });
	effectLimitCnt = 2;
}

void FoxHuman::Activate()
{
	Scene* currScene = SCENE_MGR->GetCurrentScene();
	Player* player = (Player*)currScene->FindGameObj("player");
	player->SetAttackDmg(player->GetAttackDmg() * 1.5f);
	++effectCnt;
}
