#include "PlaySceneUiMgr.h"
#include "PlayerUi.h"
#include "../Scene/SceneMgr.h"
#include "../Framework/Framework.h"
#include "../GameObject/Player.h"
#include "GameOverUi.h"

PlaySceneUiMgr::PlaySceneUiMgr(Scene* parentScene)
	:UiMgr(parentScene)
{
}

PlaySceneUiMgr::~PlaySceneUiMgr()
{
}

void PlaySceneUiMgr::Init()
{
	Player* player = (Player*)parentScene->FindGameObj("player");
	PlayerUi* playerUi = new PlayerUi();
	playerUi->Init();
	playerUi->SetPlayer(player);
	player->ResetPlayerUi = bind(&PlayerUi::ResetUi, playerUi);
	playerUi->SetName("playerUi");
	playerUi->SetOrigin(Origins::BL);
	playerUi->SetPos(Vector2f(0.f, FRAMEWORK->GetWindowSize().y * 0.5f));
	uiObjList.push_back(playerUi);

	GameOverUi* gameOverUi = new GameOverUi();
	gameOverUi->Init();
	gameOverUi->SetName("gameOverUi");
	uiObjList.push_back(gameOverUi);
}

void PlaySceneUiMgr::Reset()
{
	UiMgr::Reset();
}

void PlaySceneUiMgr::Update(float dt)
{
	Player* player = (Player*)parentScene->FindGameObj("player");
	if (!player->GetActive())
		FindUiObj("gameOverUi")->SetActive(true);
	UiMgr::Update(dt);
}

void PlaySceneUiMgr::Draw(RenderWindow& window)
{
	UiMgr::Draw(window);
}
