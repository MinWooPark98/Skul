#include "tile.h"
#include "../Framework/Utils.h"
#include "../Framework/InputMgr.h"

Tile::~Tile()
{
}

void Tile::Init()
{
	Object::Init();
	tile->setFillColor({ 255, 255, 255, 255 });
	tile->setOutlineColor({0, 0, 0, 255});
	tile->setOutlineThickness(2.f);
}

void Tile::Reset()
{
	Object::Reset();
	isMouseOn = false;
}

void Tile::Update(float dt)
{
	Object::Update(dt);
}

void Tile::Draw(RenderWindow& window)
{
	window.draw(*tile);
}

void Tile::SetPos(const Vector2f& pos)
{
	Object::SetPos(pos);
	tile->setPosition(pos);
}

void Tile::SetRotation(float rotation)
{
	Object::SetRotation(rotation);
	tile->setRotation(rotation);
}

void Tile::SetTexture(const Texture* tex)
{
	tile->setTexture(tex, true);
}

void Tile::MarkOn()
{	
	tile->setOutlineColor({ 0, 255, 0, 255 });
}

void Tile::MarkOff()
{
	tile->setOutlineColor({ 0, 0, 0, 255 });
}

const Texture* Tile::GetTexture() const
{
	return tile->getTexture();
}
