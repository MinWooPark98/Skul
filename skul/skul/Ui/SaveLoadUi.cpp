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
	:showFilePath(nullptr), confirm(nullptr)
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
	showFilePath->SetText("filePath = " + filePath + ".json");

	confirm = new TextButton();
	confirm->Init();
	confirm->SetFont(*RESOURCE_MGR->GetFont("fonts/NotoSansKR-Bold.otf"));
	confirm->SetText("Yes");
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
			addChar = ((char)((int)key + 65));
			for (auto ing : ingList)
			{
				if (ing == Keyboard::LShift || ing == Keyboard::RShift)
				{
					addChar = ((char)((int)key + 97));
					break;
				}
			}
			filePath = filePath + addChar;
			showFilePath->SetText("filePath = " + filePath + ".json");
		}
	}
	confirm->Update(dt);
	if (confirm->GetSelected())
	{
		MapEditorDataMgr* dataMgr = ((MapEditorScene*)SCENE_MGR->GetScene(Scenes::MapEditor))->GetDataMgr();
		dataMgr->SaveData(filePath);
	}
}

void SaveLoadUi::Draw(RenderWindow& window)
{
	window.draw(frame);
	showFilePath->Draw(window);
	confirm->Draw(window);
}

void SaveLoadUi::Save()
{
}

void SaveLoadUi::Load()
{
}
