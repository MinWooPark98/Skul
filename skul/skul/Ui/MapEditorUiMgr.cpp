#include "MapEditorUiMgr.h"
#include "../Scene/SceneMgr.h"
#include "../Framework/ResourceMgr.h"
#include "../Framework/Utils.h"
#include "../Ui/TextButtonUi.h"
#include "../Framework/Framework.h"

MapEditorUiMgr::MapEditorUiMgr()
	:UiMgr(SCENE_MGR->GetScene(Scenes::MapEditor))
{
}

MapEditorUiMgr::~MapEditorUiMgr()
{
}

void MapEditorUiMgr::Init()
{
	UiMgr::Init();
	Vector2i windowSize = FRAMEWORK->GetWindowSize();
	string setTexts[] = { "BackWall", "BackObject", "Platform" };
	for (int i = 0; i < 3; ++i)
	{
		TextButtonUi* text = new TextButtonUi;
		text->SetFont(*RESOURCE_MGR->GetFont("fonts/NotoSansKR-Bold.otf"));
		text->SetText(setTexts[i]);
		text->Init();
		text->SetOrigin(Origins::MC);
		text->SetPos({ windowSize.x * 0.95f, windowSize.y * 0.25f * (i + 1) });
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
