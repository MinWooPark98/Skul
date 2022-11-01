#include "MonsterScene.h"
#include "../Ui/MonsterSceneUiMgr.h"

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
	uiMgr = new MonsterSceneUiMgr();
	uiMgr->Init();
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