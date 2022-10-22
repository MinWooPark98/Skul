#include "MapEditorUiMgr.h"
#include "../Scene/SceneMgr.h"
#include "../Framework/ResourceMgr.h"
#include "../Framework/Utils.h"
#include "../Framework/Framework.h"
#include "TileExampleUi.h"
#include "ObjExampleUi.h"
#include "../GameObject/RectTile.h"
#include "../Scene/MapEditorScene.h"
#include "../DataTable/DataTableMGR.h"
#include "../DataTable/FilePathTable.h"

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
	FilePathTable* paths = DATATABLE_MGR->Get<FilePathTable>(DataTable::Types::FilePath);
	
	for (int i = 0; i < (int)MapEditorScene::Modes::Count; ++i)
	{
		TextButtonUi* text = new TextButtonUi(TextButtonUi::Modes(i));
		text->SetFont(*RESOURCE_MGR->GetFont("fonts/NotoSansKR-Bold.otf"));
		text->Init();
		text->SetOrigin(Origins::TL);
		text->SetPos({ windowSize.x * 0.91f, windowSize.y * 0.1f + text->GetSFMLText().getCharacterSize() * i * 1.5f });
		text->ChangeMode = bind(&MapEditorScene::ChangeMode, ((MapEditorScene*)SCENE_MGR->GetScene(Scenes::MapEditor)), placeholders::_1);
		switch ((MapEditorScene::Modes)i)
		{
		case MapEditorScene::Modes::BackGround:
			{
				text->SetName("BackGroundTextButton");
				ObjExampleUi* exTiles = new ObjExampleUi();
				exTiles->SetName("BackGroundExampleUi");
				exTiles->SetTileNames("tables/mapeditor/background.txt");
				paths->SetObjType(FilePathTable::ObjTypes::Background);
				exTiles->Init();
				exTiles->SetPos({ windowSize.x * 0.91f, windowSize.y * 0.45f });
				text->ShowSelected = bind(&ObjExampleUi::SetActive, exTiles, true);
				text->StopShowing = bind(&ObjExampleUi::SetActive, exTiles, false);
				uiObjList.push_back(exTiles);
			}
			break;
		case MapEditorScene::Modes::BackObject:
			{
				text->SetName("BackObjectTextButton");
				ObjExampleUi* exTiles = new ObjExampleUi();
				exTiles->SetName("BackObjectExampleUi");
				exTiles->SetTileNames("tables/mapeditor/backobject.txt");
				paths->SetObjType(FilePathTable::ObjTypes::Backobject);
				exTiles->Init();
				exTiles->SetPos({ windowSize.x * 0.91f, windowSize.y * 0.45f });
				text->ShowSelected = bind(&ObjExampleUi::SetActive, exTiles, true);
				text->StopShowing = bind(&ObjExampleUi::SetActive, exTiles, false);
				uiObjList.push_back(exTiles);
			}
			break;
		case MapEditorScene::Modes::Enemies:
			{
				text->SetName("EnemiesTextButton");
				ObjExampleUi* exTiles = new ObjExampleUi();
				exTiles->SetName("EnemiesExampleUi");
				exTiles->SetTileNames("tables/mapeditor/enemy.txt");
				paths->SetObjType(FilePathTable::ObjTypes::Enemy);
				exTiles->Init();
				exTiles->SetPos({ windowSize.x * 0.91f, windowSize.y * 0.45f });
				text->ShowSelected = bind(&ObjExampleUi::SetActive, exTiles, true);
				text->StopShowing = bind(&ObjExampleUi::SetActive, exTiles, false);
				uiObjList.push_back(exTiles);
			}
			break;
		case MapEditorScene::Modes::NPC:
			{
				text->SetName("NPCTextButton");
				ObjExampleUi* exTiles = new ObjExampleUi();
				exTiles->SetName("NPCExampleUi");
				exTiles->SetTileNames("tables/mapeditor/npc.txt");
				paths->SetObjType(FilePathTable::ObjTypes::NPC);
				exTiles->Init();
				exTiles->SetPos({ windowSize.x * 0.91f, windowSize.y * 0.45f });
				text->ShowSelected = bind(&ObjExampleUi::SetActive, exTiles, true);
				text->StopShowing = bind(&ObjExampleUi::SetActive, exTiles, false);
				uiObjList.push_back(exTiles);
			}
			break;
		case MapEditorScene::Modes::Player:
			{
				text->SetName("PlayerTextButton");
				ObjExampleUi* exTiles = new ObjExampleUi();
				exTiles->SetName("PlayerExampleUi");
				exTiles->SetTileNames("tables/mapeditor/player.txt");
				paths->SetObjType(FilePathTable::ObjTypes::Player);
				exTiles->Init();
				exTiles->SetPos({ windowSize.x * 0.91f, windowSize.y * 0.45f });
				text->ShowSelected = bind(&ObjExampleUi::SetActive, exTiles, true);
				text->StopShowing = bind(&ObjExampleUi::SetActive, exTiles, false);
				uiObjList.push_back(exTiles);
			}
			break;
		case MapEditorScene::Modes::Reward:
			{
				text->SetName("RewardTextButton");
				ObjExampleUi* exTiles = new ObjExampleUi();
				exTiles->SetName("RewardExampleUi");
				exTiles->SetTileNames("tables/mapeditor/reward.txt");
				paths->SetObjType(FilePathTable::ObjTypes::Reward);
				exTiles->Init();
				exTiles->SetPos({ windowSize.x * 0.91f, windowSize.y * 0.45f });
				text->ShowSelected = bind(&ObjExampleUi::SetActive, exTiles, true);
				text->StopShowing = bind(&ObjExampleUi::SetActive, exTiles, false);
				uiObjList.push_back(exTiles);
			}
			break;
		case MapEditorScene::Modes::Tile:
			{
				text->SetName("TileTextButton");
				TileExampleUi* exTiles = new TileExampleUi();
				exTiles->SetName("TileExampleUi");
				exTiles->SetTileNames("tables/mapeditor/tiles.txt");
				paths->SetObjType(FilePathTable::ObjTypes::Tile);
				exTiles->Init();
				exTiles->SetPos({ windowSize.x * 0.91f, windowSize.y * 0.45f });
				text->ShowSelected = bind(&TileExampleUi::SetActive, exTiles, true);
				text->StopShowing = bind(&TileExampleUi::SetActive, exTiles, false);
				uiObjList.push_back(exTiles);
			}
			break;
		case MapEditorScene::Modes::TileCollider:
			break;
		}
		textButtons.push_back(text);
		uiObjList.push_back(text);
	}

	RectTile* exTileFrame = new RectTile();
	exTileFrame->SetName("exTileFrame");
	exTileFrame->Init();
	exTileFrame->SetSize({ 98.f, 194.f });
	exTileFrame->SetPos({ windowSize.x * 0.91f - 5.f, windowSize.y * 0.45f - 5.f });
	exTileFrame->SetFillColor({ 255, 255, 255, 0 });
	exTileFrame->SetOutlineColor({ 255, 255, 255, 255 });
	uiObjList.push_back(exTileFrame);
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

void MapEditorUiMgr::ResetButton()
{
	for (auto text : textButtons)
	{
		if (text->GetSelected())
			text->Deselected();
	}
}
