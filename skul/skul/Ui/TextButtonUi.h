#pragma once
#include "../GameObject/TextButton.h"
#include <functional>

class TextButtonUi : public TextButton
{
public:
	enum class Modes
	{
		BackGround,
		BackObject,
		Enemies,
		NPC,
		Player,
		Reward,
		Tile,
		TileCollider,
	};

protected:
	Modes mode;

public:
	TextButtonUi(Modes mode);
	virtual ~TextButtonUi();

	virtual void Init() override;

	virtual void Selected();
	function<void(int)> ChangeMode;
	virtual void Deselected();
};
