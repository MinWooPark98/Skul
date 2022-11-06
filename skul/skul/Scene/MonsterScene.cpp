#include "MonsterScene.h"
#include "../Ui/PlaySceneUiMgr.h"
#include "../GameObject/Player.h"
#include "../Scene/SceneMgr.h"
#include "../GameObject/PlayerDataStorage.h"
#include "../Framework/Framework.h"

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
