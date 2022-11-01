#include "NpcScene.h"
#include "../Ui/PlaySceneUiMgr.h"
#include "../Scene/SceneMgr.h"
#include "../GameObject/PlayerDataStorage.h"

NpcScene::NpcScene()
	:PlayScene(Scenes::NpcScene)
{
	SetMapFilePath("npcscene.json");
}

NpcScene::~NpcScene()
{
}

void NpcScene::Init()
{
	PlayScene::Init();
	uiMgr = new PlaySceneUiMgr(this);
	uiMgr->Init();
}

void NpcScene::Update(float dt)
{
	PlayScene::Update(dt);
	uiMgr->Update(dt);
}

void NpcScene::Draw(RenderWindow& window)
{
	PlayScene::Draw(window);
	window.setView(uiView);
	uiMgr->Draw(window);
}

void NpcScene::Enter()
{
	PlayScene::Enter();
	SCENE_MGR->GetPlayerDataStorage()->Load();
}
