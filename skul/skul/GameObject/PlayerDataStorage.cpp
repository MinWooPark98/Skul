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
	mainSkul->offType = player->GetMainSkul()->GetOffType();
	mainSkul->type = player->GetMainSkul()->GetType();
	mainSkul->tier = player->GetMainSkul()->GetTier();
	if (player->GetSubSkul() == nullptr)
		return;
	subSkul = new SkulData();
	subSkul->offType = player->GetSubSkul()->GetOffType();
	subSkul->type = player->GetSubSkul()->GetType();
	subSkul->tier = player->GetSubSkul()->GetTier();
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
	if (subSkul != nullptr)
		player->SetSubSkul(subSkul->type, subSkul->tier);
}
