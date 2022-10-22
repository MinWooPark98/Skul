#include "TextButtonUi.h"
#include "../Framework/InputMgr.h"
#include "MapEditorUiMgr.h"

TextButtonUi::TextButtonUi(Modes mode)
	:isMouseOn(false), isSelected(false), mode(mode)
{
}

TextButtonUi::~TextButtonUi()
{
}

void TextButtonUi::Init()
{
	Object::Init();
	switch (mode)
	{
	case Modes::BackGround:
		text.setString("BackGround");
		break;
	case Modes::BackObject:
		text.setString("BackObject");
		break;
	case Modes::Enemies:
		text.setString("Enemies");
		break;
	case Modes::NPC:
		text.setString("NPC");
		break;
	case Modes::Player:
		text.setString("Player");
		break;
	case Modes::Reward:
		text.setString("Reward");
		break;
	case Modes::Tile:
		text.setString("Tile");
		break;
	case Modes::TileCollider:
		text.setString("TileCollider");
		break;
	default:
		break;
	}
	text.setCharacterSize(15);
	text.setOutlineColor({ 255, 0, 0, 0 });
	text.setOutlineThickness(1.5f);
}

void TextButtonUi::Update(float dt)
{
	Vector2f mousePos = InputMgr::GetMousePos();
	FloatRect textBound = text.getGlobalBounds();

	if (mousePos.x < textBound.left || mousePos.x > textBound.left + textBound.width ||
		mousePos.y < textBound.top || mousePos.y > textBound.top + textBound.height)
	{
		if (isMouseOn)
		{
			MouseOff();
			isMouseOn = false;
		}
		return;
	}
	isMouseOn = true;
	MouseOn();
	if (InputMgr::GetMouseButtonDown(Mouse::Left))
		Selected();
}

void TextButtonUi::MouseOn()
{
	text.setOutlineColor({ 255, 255, 255, 255 });
}

void TextButtonUi::MouseOff()
{
	text.setOutlineColor({ 255, 255, 255, 0 });
}

bool TextButtonUi::GetSelected() const
{
	return isSelected;
}

void TextButtonUi::Selected()
{
	ChangeMode((int)mode);
	isSelected = true;
	if(ShowSelected != nullptr)
		ShowSelected();
}

void TextButtonUi::Deselected()
{
	isSelected = false;
	if(StopShowing != nullptr)
		StopShowing();
}
