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
	// ifstream 으로 object 목록 불러오기 
	//(monster.txt)
	//sword
	//arrow
	//big

	// csv파일에서 읽어온 str을 key값으로 png파일 경로 얻어서 settexture
	// genereator에서 생성, objlist에 집어넣기
	// mapDataMgr 클래스에서 objlist 정보들(background, grid, MapObjGenerator의 uselist, tileCollider) 싹 긁어서 저장

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
