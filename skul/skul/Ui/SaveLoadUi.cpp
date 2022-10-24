#include "SaveLoadUi.h"
#include "../GameObject/RectTile.h"
#include "../GameObject/TextButton.h"
#include "../Framework/ResourceMgr.h"
#include "../Framework/Framework.h"
#include "../Scene/SceneMgr.h"
#include "../Scene/MapEditorScene.h"
#include "../GameObject/MapEditorDataMgr.h"
#include "../Framework/InputMgr.h"

SaveLoadUi::SaveLoadUi()
	:showFilePath(nullptr), confirm(nullptr), mode(Mode::None)
{
}

SaveLoadUi::~SaveLoadUi()
{
}


void SaveLoadUi::Init()
{
	Vector2f windowSize = (Vector2f)FRAMEWORK->GetWindowSize();

	frame.setFillColor({ 0, 0, 0, 200 });
	frame.setPosition(windowSize * 0.2f);
	frame.setSize(windowSize * 0.6f);

	showFilePath = new TextObj();
	showFilePath->Init();
	showFilePath->SetFont(*RESOURCE_MGR->GetFont("fonts/NotoSansKR-Bold.otf"));
	showFilePath->GetSFMLText().setCharacterSize(30);
	showFilePath->SetPos({ windowSize.x * 0.3f, windowSize.y * 0.5f });
	showFilePath->SetText("FilePath =   [   " + filePath + ".json   ]");
	showFilePath->SetOrigin(Origins::ML);

	confirm = new TextButton();
	confirm->Init();
	confirm->SetFont(*RESOURCE_MGR->GetFont("fonts/NotoSansKR-Bold.otf"));
	confirm->SetOutlineThickness(2.f);
	confirm->SetPos(windowSize * 0.7f);
	confirm->SetText("Yes");
	confirm->SetOrigin(Origins::BR);
}

void SaveLoadUi::Reset()
{
	confirm->Reset();
}

void SaveLoadUi::Update(float dt)
{
	auto downList = InputMgr::GetKeyDownList();
	auto ingList = InputMgr::GetKeyingList();
	char addChar;
	for (auto key : downList)
	{
		if (key >= Keyboard::A && key <= Keyboard::Z)
		{
			addChar = ((char)((int)key + 97));
			for (auto ing : ingList)
			{
				if (ing == Keyboard::LShift || ing == Keyboard::RShift)
				{
					addChar = ((char)((int)key + 65));
					break;
				}
			}
			filePath = filePath + addChar;
			showFilePath->SetText("FilePath =   [   " + filePath + ".json   ]");
			showFilePath->SetOrigin(Origins::ML);
			break;
		}
		if (key == Keyboard::Backspace && !filePath.empty())
		{
			filePath.pop_back();
			showFilePath->SetText("FilePath =   [   " + filePath + ".json   ]");
			showFilePath->SetOrigin(Origins::ML);
			break;
		}
	}
	confirm->Update(dt);
	if (confirm->GetSelected())
	{
		MapEditorScene* mapEditorScene = (MapEditorScene*)SCENE_MGR->GetScene(Scenes::MapEditor);
		MapEditorDataMgr* dataMgr = mapEditorScene->GetDataMgr();
		switch (mode)
		{
		case SaveLoadUi::Mode::Save:
			dataMgr->SaveData(filePath);
			Reset();
			mapEditorScene->SetPause(false);
			break;
		case SaveLoadUi::Mode::Load:
			break;
		}
	}
}

void SaveLoadUi::Draw(RenderWindow& window)
{
	window.draw(frame);
	showFilePath->Draw(window);
	confirm->Draw(window);
}

void SaveLoadUi::SaveMode()
{
	mode = Mode::Save;
	((MapEditorScene*)SCENE_MGR->GetScene(Scenes::MapEditor))->SetPause(true);
}

void SaveLoadUi::LoadMode()
{
	mode = Mode::Load;
	((MapEditorScene*)SCENE_MGR->GetScene(Scenes::MapEditor))->SetPause(true);
}
