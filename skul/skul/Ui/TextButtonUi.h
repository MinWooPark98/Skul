#pragma once
#include "../GameObject/TextMouseButton.h"
#include <functional>

class TextButtonUi : public TextMouseButton
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
