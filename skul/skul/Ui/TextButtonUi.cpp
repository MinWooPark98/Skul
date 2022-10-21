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
	case Modes::BackWall:
		text.setString("BackWall");
		break;
	case Modes::BackObject:
		text.setString("BackObject");
		break;
	case Modes::Platform:
		text.setString("Platform");
		break;
	case Modes::Player:
		text.setString("Player");
		break;
	case Modes::Enemies:
		text.setString("Enemies");
		break;
	case Modes::NPC:
		text.setString("NPC");
		break;
	case Modes::Reward:
		text.setString("Reward");
		break;
	case Modes::Erase:
		text.setString("Erase");
		break;
	default:
		break;
	}
	text.setCharacterSize(20);
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
	ChangeMode(mode);
	isSelected = true;
	ShowSelected();
}

void TextButtonUi::Deselected()
{
	isSelected = false;
	StopShowing();
}
