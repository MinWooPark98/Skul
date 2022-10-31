#include "SaveLoadButtonUi.h"
#include "../GameObject/TextMouseButton.h"
#include "../Framework/ResourceMgr.h"
#include "../Framework/Utils.h"
#include "../Scene/SceneMgr.h"
#include "../Scene/MapEditorScene.h"
#include "SaveLoadUi.h"

SaveLoadButtonUi::SaveLoadButtonUi()
{
}

SaveLoadButtonUi::~SaveLoadButtonUi()
{
}

void SaveLoadButtonUi::Init()
{
	Object::Init();
	MapEditorScene* mapEditorScene = (MapEditorScene*)SCENE_MGR->GetScene(Scenes::MapEditor);
	for (int i = 0; i < (int)SaveLoadUi::Mode::Count; ++i)
	{
		TextMouseButton* button = new TextMouseButton();
		button->SetFont(*RESOURCE_MGR->GetFont("fonts/NotoSansKR-Bold.otf"));
		button->Init();
		button->SetOrigin(Origins::TL);
		button->SetOutlineThickness(2.f);
		switch ((SaveLoadUi::Mode)i)
		{
		case SaveLoadUi::Mode::Save:
			button->SetText("Save");
			button->SetPos({ 0.f, button->GetSFMLText().getCharacterSize() * (-1.5f) });
			button->ShowSelected = bind(&SaveLoadUi::SaveMode, mapEditorScene->GetSaveLoadUi());
			break;
		case SaveLoadUi::Mode::Load:
			button->SetText("Load");
			button->ShowSelected = bind(&SaveLoadUi::LoadMode, mapEditorScene->GetSaveLoadUi());
			break;
		}
		buttons.push_back(button);
	}
}

void SaveLoadButtonUi::Release()
{
}

void SaveLoadButtonUi::Reset()
{
	for (auto button : buttons)
	{
		button->Deselected();
	}
}

void SaveLoadButtonUi::Update(float dt)
{
	Object::Update(dt);
	for (auto button : buttons)
	{
		button->Deselected();
		button->Update(dt);
	}
}

void SaveLoadButtonUi::Draw(RenderWindow& window)
{
	Object::Draw(window);
	for (auto button : buttons)
	{
		button->Draw(window);
	}
}

void SaveLoadButtonUi::SetPos(const Vector2f& pos)
{
	Object::SetPos(pos);
	for (auto button : buttons)
	{
		button->Translate(pos);
	}
}
