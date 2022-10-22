#include "ListMoverUi.h"
#include "../GameObject/TriangleTile.h"

ListMoverUi::ListMoverUi()
	:listPrev(nullptr), listNext(nullptr), distance(0.f)
{
}

ListMoverUi::~ListMoverUi()
{
}

void ListMoverUi::Init()
{
	Object::Init();
	listPrev = new TriangleTile();
	listNext = new TriangleTile();
	listPrev->Init();
	listNext->Init();
	listPrev->SetRotation(30);
	listNext->SetRotation(-30);
	listNext->Translate({ 0, listNext->GetSize() });
	listPrev->ClickOn = bind(&ListMoverUi::ShowPrevTile, this);
	listNext->ClickOn = bind(&ListMoverUi::ShowNextTile, this);
}

void ListMoverUi::Release()
{
	Object::Release();
	if (listPrev != nullptr)
		delete listPrev;
	if (listNext != nullptr)
		delete listNext;
}

void ListMoverUi::Update(float dt)
{
	Object::Update(dt);
	listPrev->Update(dt);
	listNext->Update(dt);
}

void ListMoverUi::Draw(RenderWindow& window)
{
	Object::Draw(window);
	listPrev->Draw(window);
	listNext->Draw(window);
}

void ListMoverUi::SetPos(const Vector2f& pos)
{
	Object::SetPos(pos);
	listPrev->SetPos(pos);
	listNext->SetPos({ pos.x + distance, pos.y + listNext->GetSize() });
}

void ListMoverUi::SetDistance(float distance)
{
	this->distance = distance;
	listNext->Translate({ distance, 0 });
}

void ListMoverUi::SetSize(float rad)
{
	listPrev->SetSize(rad);
	listNext->SetSize(rad);
}
