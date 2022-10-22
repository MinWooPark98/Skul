#include "ObjExampleUi.h"
#include "../GameObject/ExRectTile.h"
#include "../Framework/ResourceMgr.h"
#include "ListMoverUi.h"

ObjExampleUi::ObjExampleUi()
	:currTile(0), clickedTile(nullptr), listMover(nullptr)
{
}

ObjExampleUi::~ObjExampleUi()
{
}

void ObjExampleUi::Init()
{
	// ifstream ���� object ��� �ҷ����� 
	//(monster.txt)
	//sword
	//arrow
	//big

	// csv���Ͽ��� �о�� str�� key������ png���� ��� �� settexture
	// genereator���� ����, objlist�� ����ֱ�
	// mapDataMgr Ŭ�������� objlist ������(background, grid, MapObjGenerator�� uselist, tileCollider) �� �ܾ ����

	Object::Init();
	Vector2f frameSize = { 88.f, 184.f };
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

	listMover = new ListMoverUi();
	listMover->Init();
	listMover->SetSize(12);
	listMover->SetDistance(44.f);
	listMover->SetPos({ 12.f, 200.f });
	listMover->ShowPrev = bind(&ObjExampleUi::ShowPrevTiles, this);
	listMover->ShowNext = bind(&ObjExampleUi::ShowNextTiles, this);
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
	listMover->Update(dt);
}

void ObjExampleUi::Draw(RenderWindow& window)
{
	tiles[currTile]->Draw(window);
	listMover->Draw(window);
}

void ObjExampleUi::SetPos(const Vector2f& pos)
{
	Object::SetPos(pos);
	for (auto tile : tiles)
	{
		tile->Translate(pos);
	}
	listMover->Translate(pos);
}

void ObjExampleUi::ShowPrevTiles()
{
	if (currTile > 0)
		currTile -= 1;
}

void ObjExampleUi::ShowNextTiles()
{
	if (currTile < tiles.size() - 1)
		currTile += 1;
}
