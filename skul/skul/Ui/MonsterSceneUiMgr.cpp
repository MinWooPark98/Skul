#include "MonsterSceneUiMgr.h"
#include "PlayerUi.h"
#include "../Scene/SceneMgr.h"
#include "../Framework/Framework.h"
#include "../GameObject/Player.h"

MonsterSceneUiMgr::MonsterSceneUiMgr()
	:UiMgr(SCENE_MGR->GetScene(Scenes::MonsterScene))
{
}

MonsterSceneUiMgr::~MonsterSceneUiMgr()
{
}

void MonsterSceneUiMgr::Init()
{
	Scene* monsterScene = SCENE_MGR->GetScene(Scenes::MonsterScene);
	Player* player = (Player*)monsterScene->FindGameObj("player");
	PlayerUi* playerUi = new PlayerUi();
	playerUi->Init();
	playerUi->SetPlayer(player);
	player->ResetPlayerUi = bind(&PlayerUi::ResetUi, playerUi);
	playerUi->SetName("playerUi");
	playerUi->SetOrigin(Origins::BL);
	playerUi->SetPos(Vector2f(0.f, FRAMEWORK->GetWindowSize().y * 0.5f));
	uiObjList.push_back(playerUi);
}

void MonsterSceneUiMgr::Reset()
{
}

void MonsterSceneUiMgr::Update(float dt)
{
	UiMgr::Update(dt);
}

void MonsterSceneUiMgr::Draw(RenderWindow& window)
{
	UiMgr::Draw(window);
}
