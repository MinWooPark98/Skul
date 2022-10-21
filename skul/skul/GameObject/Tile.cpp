#include "Tile.h"
#include "../Framework/Utils.h"
#include "../Framework/InputMgr.h"
#include "../Framework/ResourceMgr.h"

Tile::Tile()
	:isMouseOn(false)
{
}

Tile::~Tile()
{
}

void Tile::Init()
{
	tile.setFillColor({ 255, 255, 255, 0 });
	tile.setOutlineColor(Color::White);
	tile.setOutlineThickness(1.f);
}

void Tile::Reset()
{
	Object::Reset();
	tile.setTexture(nullptr);
}

void Tile::Update(float dt)
{
	Vector2f mousePos = InputMgr::GetMousePos();
	FloatRect tileBound = tile.getGlobalBounds();

	if (mousePos.x < tileBound.left || mousePos.x > tileBound.left + tileBound.width ||
		mousePos.y < tileBound.top || mousePos.y > tileBound.top + tileBound.height)
	{
		if (isMouseOn)
		{
			MarkOff();
			isMouseOn = false;
		}
		return;
	}
	isMouseOn = true;
	MarkOn();
}

void Tile::Draw(RenderWindow& window)
{
	window.draw(tile);
}

void Tile::SetPos(const Vector2f& pos)
{
	Object::SetPos(pos);
	tile.setPosition(pos);
}

void Tile::DrawTexture(const Texture* tex)
{
	tile.setFillColor({ 255, 255, 255, 255 });
	tile.setTexture(tex, true);
}

void Tile::EraseTexture()
{
	tile.setFillColor({ 255, 255, 255, 0 });
	tile.setTexture(nullptr);
}

void Tile::MarkOn()
{	
	tile.setOutlineColor({ 255, 0, 0, 255 });
	tile.setOutlineThickness(2.f);
}

void Tile::MarkOff()
{
	tile.setOutlineColor(Color::White);
	tile.setOutlineThickness(1.f);
}

const Texture* Tile::GetTexture() const
{
	return tile.getTexture();
}
