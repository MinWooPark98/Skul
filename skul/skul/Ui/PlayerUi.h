#pragma once
#include "../GameObject/SpriteObj.h"

class Player;

class PlayerUi : public SpriteObj
{
protected:
	SpriteObj symbol;
	SpriteObj skillBFrame;
	SpriteObj skillAIcon;
	SpriteObj skillBIcon;

	RectangleShape currHpBar; 

	const Player* player;

public:
	PlayerUi();
	virtual ~PlayerUi();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	virtual void SetPos(const Vector2f& pos) override;

	void SetPlayer(const Player* player);
	void ResetUi();
};

