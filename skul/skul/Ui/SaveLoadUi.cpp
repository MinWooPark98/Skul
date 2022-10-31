#include "SaveLoadUi.h"
#include "../GameObject/RectTile.h"
#include "../GameObject/TextMouseButton.h"
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

	yesButton = new TextMouseButton();
	yesButton->Init();
	yesButton->SetFont(*RESOURCE_MGR->GetFont("fonts/NotoSansKR-Bold.otf"));
	yesButton->SetOutlineColor({ 255, 255, 255, 0 });
	yesButton->SetOutlineThickness(2.f);
	yesButton->SetText("Yes");
	yesButton->SetOrigin(Origins::BR);
	yesButton->SetPos({ windowSize.x * 0.8f - yesButton->GetSFMLText().getCharacterSize() * 2.f, windowSize.y * 0.8f});

	noButton = new TextMouseButton();
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
	mode = Mode::None;
}

void SaveLoadUi::Update(float dt)
{
	if (mode == Mode::None)
		return;

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
	auto ingList = InputMgr::GetKeyIngList();
	char addChar = NULL;
	for (auto key : downList)
	{
		if (key >= Keyboard::A && key <= Keyboard::Z)
		{
			addChar = 'a' + ((char)key - (char)Keyboard::A);
			for (auto ing : ingList)
			{
				if (ing == Keyboard::LShift || ing == Keyboard::RShift)
				{
					addChar = 'A' + ((char)key - (char)Keyboard::A);
					break;
				}
			}
			filePath = filePath + addChar;
			SetShowFilePath(filePath);
			break;
		}
		if (key >= Keyboard::Num0 && key <= Keyboard::Num9)
		{
			addChar = '0' + ((char)key - (char)Keyboard::Num0);
			filePath = filePath + addChar;
			SetShowFilePath(filePath);
			break;
		}
		if (key >= Keyboard::Numpad0 && key <= Keyboard::Numpad9)
		{
			addChar = '0' + ((char)key - (char)Keyboard::Numpad0);
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
			if (!dataMgr->LoadData(filePath))
				isFailed = true;
			break;
		}
		if (isFailed)
			showFailure->SetActive(true);
		else
		{
			mapEditorScene->SetPause(false);
			mode = Mode::None;
		}
		yesButton->Deselected();
		filePath.clear();
		SetShowFilePath(filePath);
	}
	noButton->Update(dt);
	if (noButton->GetSelected())
	{
		mapEditorScene->SetPause(false);
		noButton->Deselected();
		mode = Mode::None;
		filePath.clear();
		SetShowFilePath(filePath);
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
