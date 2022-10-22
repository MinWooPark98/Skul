#pragma once
#include "../GameObject/TextObj.h"
#include <functional>

class TextButtonUi : public TextObj
{
public:
	enum class Modes
	{
		BackWall,
		BackObj,
		Player,
		Enemies,
		NPC,
		Reward,
		Tile,
		TileCollider,
	};

protected:
	bool isMouseOn;
	bool isSelected;

	Modes mode;

public:
	TextButtonUi(Modes mode);
	virtual ~TextButtonUi();

	virtual void Init() override;
	virtual void Update(float dt) override;

	void MouseOn();
	void MouseOff();

	bool GetSelected() const;

	void Selected();
	function<void()> ShowSelected;
	function<void(Modes)> ChangeMode;
	void Deselected();
	function<void()> StopShowing;
};
