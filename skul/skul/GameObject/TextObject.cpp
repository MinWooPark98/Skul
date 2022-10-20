#include "TextObject.h"
#include "../Framework/ResourceMgr.h"

TextObject::TextObject()
{
}

TextObject::~TextObject()
{
}

void TextObject::Init()
{
}

void TextObject::Update(float dt)
{
	text.setPosition(position);
}

void TextObject::Draw(RenderWindow& window)
{
	window.draw(text);
}

void TextObject::SetString(const string& string)
{
	text.setString(string);
}

void TextObject::SetFont(const Font& font)
{
	text.setFont(font);
}
