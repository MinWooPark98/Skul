#include "TextButtonUi.h"
#include "../Framework/InputMgr.h"
#include "MapEditorUiMgr.h"

TextButtonUi::TextButtonUi(Modes mode)
	:mode(mode)
{
}

TextButtonUi::~TextButtonUi()
{
}

void TextButtonUi::Init()
{
	TextMouseButton::Init();
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
	case Modes::Gate:
		text.setString("Gate");
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

void TextButtonUi::Selected()
{
	ChangeMode((int)mode);
	TextMouseButton::Selected();
}

void TextButtonUi::Deselected()
{
	TextMouseButton::Deselected();
}
