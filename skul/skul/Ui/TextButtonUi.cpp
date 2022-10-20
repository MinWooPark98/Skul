#include "TextButtonUi.h"
#include "../Framework/InputMgr.h"

TextButtonUi::TextButtonUi()
	:isMouseOn(false)
{
}

TextButtonUi::~TextButtonUi()
{
}

void TextButtonUi::Init()
{
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
			EffectOff();
			isMouseOn = false;
		}
		return;
	}
	isMouseOn = true;
	EffectOn();
}

void TextButtonUi::EffectOn()
{
	text.setOutlineColor({ 255, 255, 255, 255 });
}

void TextButtonUi::EffectOff()
{
	text.setOutlineColor({ 255, 255, 255, 0 });
}
