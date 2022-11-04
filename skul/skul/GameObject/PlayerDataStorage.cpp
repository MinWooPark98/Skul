#include "PlayerDataStorage.h"
#include "../Scene/SceneMgr.h"
#include "Player.h"

PlayerDataStorage::PlayerDataStorage()
	:totalHp(0), currHp(0), mainSkul(nullptr), subSkul(nullptr)
{
}

PlayerDataStorage::~PlayerDataStorage()
{
}

void PlayerDataStorage::Reset()
{
	if (mainSkul != nullptr)
		delete mainSkul;
	mainSkul = nullptr;
	if (subSkul != nullptr)
		delete mainSkul;
	subSkul = nullptr;
}

void PlayerDataStorage::Save()
{
	Scene* currScene = SCENE_MGR->GetCurrentScene();
	Player* player = (Player*)currScene->FindGameObj("player");
	totalHp = player->GetTotalHp();
	currHp = player->GetCurrHp();
	speedAdd = player->GetSpeedAdd();
	attackAdd = player->GetAttackAdd();
	mainSkul = new SkulData();
	auto currMainSkul = player->GetMainSkul();
	mainSkul->offType = currMainSkul->GetOffType();
	mainSkul->type = currMainSkul->GetType();
	mainSkul->tier = currMainSkul->GetTier();
	mainSkul->skillA = currMainSkul->GetSkillA();
	mainSkul->skillB = currMainSkul->GetSkillB();
	if (player->GetSubSkul() == nullptr)
		return;
	subSkul = new SkulData();
	auto currSubSkul = player->GetSubSkul();
	subSkul->offType = currSubSkul->GetOffType();
	subSkul->type = currSubSkul->GetType();
	subSkul->tier = currSubSkul->GetTier();
	subSkul->skillA = currSubSkul->GetSkillA();
	subSkul->skillB = currSubSkul->GetSkillB();
}

void PlayerDataStorage::Load()
{
	Scene* currScene = SCENE_MGR->GetCurrentScene();
	Player* player = (Player*)currScene->FindGameObj("player");
	player->SetTotalHp(totalHp);
	player->SetCurrHp(currHp);
	player->SetSpeedAdd(speedAdd);
	player->SetAttackAdd(attackAdd);
	player->SetMainSkul(mainSkul->type, mainSkul->tier);
	player->GetMainSkul()->SetSkillA(mainSkul->skillA);
	player->GetMainSkul()->SetSkillB(mainSkul->skillB);
	if (subSkul == nullptr)
		return;
	player->SetSubSkul(subSkul->type, subSkul->tier);
	player->GetSubSkul()->SetSkillA(subSkul->skillA);
	player->GetSubSkul()->SetSkillB(subSkul->skillB);
}
