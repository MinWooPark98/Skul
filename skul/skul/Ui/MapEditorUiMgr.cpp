#include "MapEditorUiMgr.h"
#include "../Scene/SceneMgr.h"
#include "../Framework/ResourceMgr.h"
#include "../Framework/Utils.h"
#include "../Framework/Framework.h"
#include "TileExampleUi.h"

MapEditorUiMgr::MapEditorUiMgr()
	:UiMgr(SCENE_MGR->GetScene(Scenes::MapEditor)), currTex(nullptr), mode(Modes::None)
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
		TextButtonUi* text = new TextButtonUi(TextButtonUi::Modes(i));
		text->SetFont(*RESOURCE_MGR->GetFont("fonts/NotoSansKR-Bold.otf"));
		text->Init();
		text->SetOrigin(Origins::TL);
		text->SetPos({ windowSize.x * 0.9f, windowSize.y * 0.1f + text->GetSFMLText().getCharacterSize() * i * 1.5f });
		text->ShowSelected = bind(&TileExampleUi::SetActive, exTiles, true);
		text->ChangeMode = bind(&MapEditorUiMgr::ChangeMode, this, placeholders::_1);
		text->StopShowing = bind(&TileExampleUi::SetActive, exTiles, false);
		uiObjList.push_back(exTiles);
		textButtons.push_back(text);
		uiObjList.push_back(text);
	}
}

void MapEditorUiMgr::Reset()
{
	UiMgr::Reset();
}

void MapEditorUiMgr::Update(float dt)
{
	UiMgr::Update(dt);
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
