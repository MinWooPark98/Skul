#include "BossScene.h"
#include "../Ui/PlaySceneUiMgr.h"
#include "../Scene/SceneMgr.h"
#include "../GameObject/PlayerDataStorage.h"
#include "../Framework/Framework.h"
#include "../GameObject/Boss/ElderEnt/ElderEnt.h"

BossScene::BossScene()
	:PlayScene(Scenes::BossScene)
{
	SetMapFilePath("bossscene.json");
}

BossScene::~BossScene()
{
}

void BossScene::Init()
{
	PlayScene::Init();

	ElderEnt* elderEnt = new ElderEnt();
	elderEnt->Init();
	layOut[(int)Layer::Boss]->push_back(elderEnt);
	objList.push_back(elderEnt);

	uiMgr = new PlaySceneUiMgr(this);
	uiMgr->Init();
}

void BossScene::Update(float dt)
{
	PlayScene::Update(dt);
	Vector2i size = FRAMEWORK->GetWindowSize();
	Vector2f worldViewCenter = worldView.getCenter();
	if (worldViewCenter.x < size.x * 0.25f)
		worldViewCenter.x = size.x * 0.25f;

	if (worldViewCenter.y < size.y * 0.25f)
		worldViewCenter.y = size.y * 0.25f;

	if (worldViewCenter.x > 900.f - size.x * 0.25f)
		worldViewCenter.x = 900.f - size.x * 0.25f;

	if (worldViewCenter.y > 320.f)
		worldViewCenter.y = 320.f;

	worldView.setCenter(worldViewCenter);
	uiMgr->Update(dt);
}

void BossScene::Draw(RenderWindow& window)
{
	PlayScene::Draw(window);
	window.setView(uiView);
	uiMgr->Draw(window);
}

void BossScene::Enter()
{
	PlayScene::Enter();
	SCENE_MGR->GetPlayerDataStorage()->Load();
}
