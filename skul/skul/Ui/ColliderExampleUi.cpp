#include "ColliderExampleUi.h"
#include "../GameObject/ExRectTile.h"
#include "../Scene/MapEditorScene.h"
#include "../Scene/SceneMgr.h"

ColliderExampleUi::ColliderExampleUi()
	:currType(ColliderTypes::None)
{
}

ColliderExampleUi::~ColliderExampleUi()
{
}

void ColliderExampleUi::Init()
{
	Object::Init();
	for (int i = 0; i < (int)ColliderTypes::Count; ++i)
	{
		ExRectTile* tile = new ExRectTile();
		tile->Init();
		tile->SetSize({ 80.f, 40.f });
		tile->SetPos({ 0.f, 48.f * (i % 2) });
		switch ((ColliderTypes)i)
		{
		case ColliderTypes::TopSide:
			tile->SetFillColor({ 0, 0, 255, 255 });
			tile->SetName("TopSide");
			break;
		case ColliderTypes::AllSide:
			tile->SetFillColor({ 255, 0, 0, 255 });
			tile->SetName("AllSide");
			break;
		}
		tiles.push_back(tile);
	}
}

void ColliderExampleUi::Release()
{
	for (auto tile : tiles)
	{
		tile->Release();
		delete tile;
		tile = nullptr;
	}
}

void ColliderExampleUi::Reset()
{
	if (currType != ColliderTypes::None)
	{
		tiles[(int)currType]->SetClicked(false);
		tiles[(int)currType]->ClickedOff();
	}
	currType = ColliderTypes::None;
	SetActive(false);
}

void ColliderExampleUi::Update(float dt)
{
	for (int i = 0; i < (int)ColliderTypes::Count; ++i)
	{
		tiles[i]->Update(dt);
		if (tiles[i]->GetClicked() && i != (int)currType)
		{
			if (currType != ColliderTypes::None)
			{
				tiles[(int)currType]->SetClicked(false);
				tiles[(int)currType]->ClickedOff();
			}
			currType = (ColliderTypes)i;
		}
	}
}

void ColliderExampleUi::Draw(RenderWindow& window)
{
	for (auto tile : tiles)
	{
		tile->Draw(window);
	}
}

void ColliderExampleUi::SetPos(const Vector2f& pos)
{
	Object::SetPos(pos);
	for (auto tile : tiles)
	{
		tile->Translate(pos);
	}
}
