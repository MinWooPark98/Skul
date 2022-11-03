#include "PlayerDataStorage.h"
#include "../Scene/SceneMgr.h"
#include "Player.h"

PlayerDataStorage::PlayerDataStorage()
	:totalHp(0), currHp(0), attackDmg(0), speed(0.f), jumpableCnt(0)
{
}

PlayerDataStorage::~PlayerDataStorage()
{
}

void PlayerDataStorage::Save()
{
	Scene* currScene = SCENE_MGR->GetCurrentScene();
	Player* player = (Player*)currScene->FindGameObj("player");
	totalHp = player->GetTotalHp();
	currHp = player->GetCurrHp();
	attackDmg = player->GetAttackDmg();
	speed = player->GetSpeed();
	jumpableCnt = player->GetJumpableCount();
}

void PlayerDataStorage::Load()
{
	Scene* currScene = SCENE_MGR->GetCurrentScene();
	Player* player = (Player*)currScene->FindGameObj("player");
	player->SetTotalHp(totalHp);
	player->SetCurrHp(currHp);
	player->SetAttackDmg(attackDmg);
	player->SetSpeed(speed);
	player->SetJumpableCount(jumpableCnt);
}
