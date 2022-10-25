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
	:mode(Mode::None), showMode(nullptr), showFailure(nullptr), showFilePath(nullptr), yesButton(nullptr), noButton(nullptr), isFailed(false), showFailureTimer(1.f)
{
}

SaveLoadUi::~SaveLoadUi()
{
}


void SaveLoadUi::Init()
{
	Vector2f windowSize = (Vector2f)FRAMEWORK->GetWindowSize();

	frame.setFillColor({ 0, 0, 255, 150 });
	frame.setPosition(windowSize * 0.15f);
	frame.setSize(windowSize * 0.7f);

	showMode = new TextObj();
	showMode->Init();
	showMode->SetFont(*RESOURCE_MGR->GetFont("fonts/NotoSansKR-Bold.otf"));
	showMode->GetSFMLText().setCharacterSize(40);
	showMode->SetPos(windowSize * 0.2f);

	showFilePath = new TextObj();
	showFilePath->Init();
	showFilePath->SetFont(*RESOURCE_MGR->GetFont("fonts/NotoSansKR-Bold.otf"));
	showFilePath->GetSFMLText().setCharacterSize(30);
	showFilePath->SetPos({ windowSize.x * 0.25f, windowSize.y * 0.5f });
	showFilePath->SetText("FilePath =   [   " + filePath + ".json   ]");
	showFilePath->SetOrigin(Origins::ML);

	showFailure = new TextObj();
	showFailure->Init();
	showFailure->SetActive(false);
	showFailure->SetFont(*RESOURCE_MGR->GetFont("fonts/NotoSansKR-Bold.otf"));
	showFailure->GetSFMLText().setCharacterSize(20);
	showFailure->SetPos({ windowSize.x * 0.7f, windowSize.y * 0.6f });
	showFailure->SetText("Wrong filepath");
	showFailure->SetOrigin(Origins::MR);

	yesButton = new TextButton();
	yesButton->Init();
	yesButton->SetFont(*RESOURCE_MGR->GetFont("fonts/NotoSansKR-Bold.otf"));
	yesButton->SetOutlineColor({ 255, 255, 255, 0 });
	yesButton->SetOutlineThickness(2.f);
	yesButton->SetText("Yes");
	yesButton->SetOrigin(Origins::BR);
	yesButton->SetPos({ windowSize.x * 0.8f - yesButton->GetSFMLText().getCharacterSize() * 2.f, windowSize.y * 0.8f});

	noButton = new TextButton();
	noButton->Init();
	noButton->SetFont(*RESOURCE_MGR->GetFont("fonts/NotoSansKR-Bold.otf"));
	noButton->SetOutlineColor({ 255, 255, 255, 0 });
	noButton->SetOutlineThickness(2.f);
	noButton->SetText("No");
	noButton->SetOrigin(Origins::BR);
	noButton->SetPos(windowSize * 0.8f);
}

void SaveLoadUi::Reset()
{
	yesButton->Deselected();
	noButton->Deselected();
	filePath.clear();
	SetShowFilePath(filePath);
	isFailed = false;
}

void SaveLoadUi::Update(float dt)
{
	if (isFailed)
	{
		showFailureTimer -= dt;
		if (showFailureTimer < 0.f)
		{
			isFailed = false;
			showFailure->SetActive(false);
			showFailureTimer = 1.f;
		}
	}
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
			SetShowFilePath(filePath);
			break;
		}
		if (key == Keyboard::Slash)
		{
			addChar = '/';
			filePath = filePath + addChar;
			SetShowFilePath(filePath);
			break;
		}
		if (key == Keyboard::Backspace && !filePath.empty())
		{
			filePath.pop_back();
			SetShowFilePath(filePath);
			break;
		}
	}
	MapEditorScene* mapEditorScene = (MapEditorScene*)SCENE_MGR->GetScene(Scenes::MapEditor);
	yesButton->Update(dt);
	if (yesButton->GetSelected())
	{
		MapEditorDataMgr* dataMgr = mapEditorScene->GetDataMgr();
		switch (mode)
		{
		case SaveLoadUi::Mode::Save:
			if (!dataMgr->SaveData(filePath))
				isFailed = true;
			break;
		case SaveLoadUi::Mode::Load:
			// 추가할 예정
			if (!dataMgr->LoadData(filePath))
				isFailed = true;
			break;
		}
		if (isFailed)
			showFailure->SetActive(true);
		else
			mapEditorScene->SetPause(false);
		yesButton->Deselected();
	}
	noButton->Update(dt);
	if (noButton->GetSelected())
	{
		mapEditorScene->SetPause(false);
		noButton->Deselected();
	}
}

void SaveLoadUi::Draw(RenderWindow& window)
{
	window.draw(frame);
	showMode->Draw(window);
	if (showFailure->GetActive())
		showFailure->Draw(window);
	showFilePath->Draw(window);
	yesButton->Draw(window);
	noButton->Draw(window);
}

void SaveLoadUi::SetShowFilePath(const string& filePath)
{
	showFilePath->SetText("FilePath =   [   " + filePath + ".json   ]");
	showFilePath->SetOrigin(Origins::ML);
}

void SaveLoadUi::SaveMode()
{
	mode = Mode::Save;
	showMode->SetText("Save Mode");
	((MapEditorScene*)SCENE_MGR->GetScene(Scenes::MapEditor))->SetPause(true);
}

void SaveLoadUi::LoadMode()
{
	mode = Mode::Load;
	showMode->SetText("Load Mode");
	((MapEditorScene*)SCENE_MGR->GetScene(Scenes::MapEditor))->SetPause(true);
}
