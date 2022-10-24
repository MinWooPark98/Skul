#include "SaveLoadButtonUi.h"
#include "../GameObject/TextButton.h"
#include "../Framework/ResourceMgr.h"
#include "../Framework/Utils.h"

SaveLoadButtonUi::SaveLoadButtonUi()
{
}

SaveLoadButtonUi::~SaveLoadButtonUi()
{
}

void SaveLoadButtonUi::Init()
{
	Object::Init();
	for (int i = 0; i < (int)Type::Count; ++i)
	{
		TextButton* button = new TextButton();
		button->SetFont(*RESOURCE_MGR->GetFont("fonts/NotoSansKR-Bold.otf"));
		button->Init();
		button->SetOrigin(Origins::TL);
		button->SetOutlineThickness(2.f);
		switch ((Type)i)
		{
		case Type::Save:
			button->SetText("Save");
			button->SetPos({ 0.f, button->GetSFMLText().getCharacterSize() * (-1.5f) });
			//button->ShowSelected = 
			break;
		case Type::Load:
			button->SetText("Load");
			//button->ShowSelected =
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
