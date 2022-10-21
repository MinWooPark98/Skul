#include "TileExampleUi.h"
#include "../GameObject/RectTile.h"
#include "../GameObject/TextObj.h"
#include "../Framework/Framework.h"
#include "../Framework/ResourceMgr.h"

TileExampleUi::TileExampleUi()
{
}

TileExampleUi::~TileExampleUi()
{
}

void TileExampleUi::Init()
{
	Object::Init();
	Vector2i windowSize = FRAMEWORK->GetWindowSize();
	for (int i = 0; i < 8; ++i)
	{
		RectTile* tile = new RectTile();
		tile->Init();
		tile->SetSize({ 40.f, 40.f });
		tile->SetPos({ 48.f * (i % 2), 48.f * (i / 2) });
		tiles.push_back(tile);
	}
}

void TileExampleUi::Release()
{
}

void TileExampleUi::Reset()
{
	enabled = false;
}

void TileExampleUi::Update(float dt)
{
	for (auto tile : tiles)
	{
		tile->Update(dt);
	}
}

void TileExampleUi::Draw(RenderWindow& window)
{
	for (auto tile : tiles)
	{
		tile->Draw(window);
	}
}

void TileExampleUi::SetPos(const Vector2f& pos)
{
	Object::SetPos(pos);
	for (auto tile : tiles)
	{
		tile->Translate(pos);
	}
}
