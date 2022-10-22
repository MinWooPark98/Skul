#include "ObjExampleUi.h"
#include "../GameObject/ExRectTile.h"
#include "../Framework/Framework.h"
#include "../Framework/ResourceMgr.h"

ObjExampleUi::ObjExampleUi()
	:currTile(0), clickedTile(nullptr)
{
}

ObjExampleUi::~ObjExampleUi()
{
}

void ObjExampleUi::Init()
{
	Object::Init();
	Vector2i windowSize = FRAMEWORK->GetWindowSize();
	Vector2f frameSize = { 88.f, 240.f };
	Vector2f tileSize;
	for (int i = 0; i < 3; ++i)
	{
		ExRectTile* tile = new ExRectTile();
		Texture* tex = RESOURCE_MGR->GetTexture("graphics/player3.png");
		Vector2f texSize = Vector2f((*tex).getSize());
		if (texSize.x / frameSize.x > texSize.y / frameSize.y)
			tileSize = { frameSize.x, texSize.y / (texSize.x / frameSize.x) };
		else
			tileSize = { texSize.x / (texSize.y / frameSize.y), frameSize.y };
		tile->Init();
		tile->SetSize(tileSize);
		tile->SetTexture(tex);
		tiles.push_back(tile);
	}
}

void ObjExampleUi::Release()
{
}

void ObjExampleUi::Reset()
{
	enabled = false;
}

void ObjExampleUi::Update(float dt)
{
	tiles[currTile]->Update(dt);
	if (tiles[currTile]->GetClicked() && tiles[currTile] != clickedTile)
	{
		if (clickedTile != nullptr)
		{
			clickedTile->SetClicked(false);
			clickedTile->ClickedOff();
		}
		clickedTile = tiles[currTile];
	}
}

void ObjExampleUi::Draw(RenderWindow& window)
{
	tiles[currTile]->Draw(window);
}

void ObjExampleUi::SetPos(const Vector2f& pos)
{
	Object::SetPos(pos);
	for (auto tile : tiles)
	{
		tile->Translate(pos);
	}
}
