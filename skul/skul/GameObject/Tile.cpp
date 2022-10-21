#include "tile.h"
#include "../Framework/Utils.h"
#include "../Framework/InputMgr.h"
#include "../Framework/ResourceMgr.h"
#include "../Ui/MapEditorUiMgr.h"
#include "../Scene/SceneMgr.h"

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
	Vector2f mousePos = InputMgr::GetMousePos();
	FloatRect tileBound = tile->getGlobalBounds();
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

void Tile::SetTextureChosen()
{
	SetTexture(((MapEditorUiMgr*)(SCENE_MGR->GetScene(Scenes::MapEditor)->GetUiMgr()))->GetTexture());
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
