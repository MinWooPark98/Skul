#include "MapEditorUiMgr.h"
#include "../Scene/SceneMgr.h"
#include "../Framework/ResourceMgr.h"
#include "../Framework/Utils.h"
#include "../Framework/Framework.h"
#include "TileExampleUi.h"
#include "ListMoverUi.h"
#include "../GameObject/RectTile.h"

MapEditorUiMgr::MapEditorUiMgr()
	:UiMgr(SCENE_MGR->GetScene(Scenes::MapEditor)), mode(Modes::None)
{
}

MapEditorUiMgr::~MapEditorUiMgr()
{
}

void MapEditorUiMgr::Init()
{
	UiMgr::Init();
	Vector2i windowSize = FRAMEWORK->GetWindowSize();

	for (int i = 0; i < 8; ++i)
	{
		TileExampleUi* exTiles = new TileExampleUi();
		exTiles->Init();
		exTiles->SetPos({ windowSize.x * 0.91f, windowSize.y * 0.45f });
		TextButtonUi* text = new TextButtonUi(TextButtonUi::Modes(i));
		text->SetFont(*RESOURCE_MGR->GetFont("fonts/NotoSansKR-Bold.otf"));
		text->Init();
		text->SetOrigin(Origins::TL);
		text->SetPos({ windowSize.x * 0.91f, windowSize.y * 0.1f + text->GetSFMLText().getCharacterSize() * i * 1.5f });
		text->ShowSelected = bind(&TileExampleUi::SetActive, exTiles, true);
		text->ChangeMode = bind(&MapEditorUiMgr::ChangeMode, this, placeholders::_1);
		text->StopShowing = bind(&TileExampleUi::SetActive, exTiles, false);
		uiObjList.push_back(exTiles);
		textButtons.push_back(text);
		uiObjList.push_back(text);
	}

	RectTile* exTileFrame = new RectTile();
	exTileFrame->Init();
	exTileFrame->SetSize({ 98.f, 250.f });
	exTileFrame->SetPos({ windowSize.x * 0.91f - 5.f, windowSize.y * 0.45f - 5.f });
	exTileFrame->SetFillColor({ 255, 255, 255, 0 });
	exTileFrame->SetOutlineThickness(1.f);
	uiObjList.push_back(exTileFrame);

	ListMoverUi* listMover = new ListMoverUi();
	listMover->Init();
	listMover->SetSize(12);
	listMover->SetDistance(44.f);
	listMover->SetPos({ windowSize.x * 0.91f + 10.f, windowSize.y * 0.45f + 200.f });
	uiObjList.push_back(listMover);
}

void MapEditorUiMgr::Reset()
{
	UiMgr::Reset();
}

void MapEditorUiMgr::Update(float dt)
{
	UiMgr::Update(dt);
}

void MapEditorUiMgr::Draw(RenderWindow& window)
{
	UiMgr::Draw(window);
}

void MapEditorUiMgr::ChangeMode(TextButtonUi::Modes mode)
{
	for (auto text : textButtons)
	{
		if (text->GetSelected())
			text->Deselected();
	}
	this->mode = (Modes)((int)mode);
}
