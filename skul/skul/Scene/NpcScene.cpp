#include "NpcScene.h"
#include "../Ui/PlaySceneUiMgr.h"
#include "../Scene/SceneMgr.h"
#include "../GameObject/PlayerDataStorage.h"
#include "../Framework/Framework.h"

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
	Vector2i size = FRAMEWORK->GetWindowSize();
	Vector2f worldViewCenter = worldView.getCenter();
	if (worldViewCenter.x < size.x * 0.25f)
		worldViewCenter.x = size.x * 0.25f;

	if (worldViewCenter.y < size.y * 0.25f)
		worldViewCenter.y = size.y * 0.25f;

	if (worldViewCenter.x > size.x * 1.75f)
		worldViewCenter.x = size.x * 1.75f;

	if (worldViewCenter.y > size.y * 1.75f)
		worldViewCenter.y = size.y * 1.75f;

	worldView.setCenter(worldViewCenter);
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
