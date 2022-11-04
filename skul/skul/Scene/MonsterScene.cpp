#include "MonsterScene.h"
#include "../Ui/PlaySceneUiMgr.h"
#include "../GameObject/Player.h"
#include "../Scene/SceneMgr.h"
#include "../GameObject/PlayerDataStorage.h"

MonsterScene::MonsterScene()
	:PlayScene(Scenes::MonsterScene)
{
	SetMapFilePath("monsterscene.json");
}

MonsterScene::~MonsterScene()
{
}

void MonsterScene::Init()
{
	PlayScene::Init();
	Player* player = (Player*)FindGameObj("player");
	player->ObtainMainSkul(Skul::Types::Default, Skul::Tiers::Normal);

	uiMgr = new PlaySceneUiMgr(this);
	uiMgr->Init();
}

void MonsterScene::Reset()
{
	PlayScene::Reset();
	Player* player = (Player*)FindGameObj("player");
	player->ObtainMainSkul(Skul::Types::Default, Skul::Tiers::Normal);
}

void MonsterScene::Update(float dt)
{
	PlayScene::Update(dt);
	uiMgr->Update(dt);
}

void MonsterScene::Draw(RenderWindow& window)
{
	PlayScene::Draw(window);
	window.setView(uiView);
	uiMgr->Draw(window);
}

void MonsterScene::Enter()
{
	PlayScene::Enter();
	SCENE_MGR->GetPlayerDataStorage()->Reset();
}
