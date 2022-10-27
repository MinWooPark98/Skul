#pragma once
#include "Object.h"

class Player;

class Collider : public Object
{
public:
	enum class Type
	{
		None = -1,
		TopSide,
		AllSide,
	};

protected:
	Type type;

	Player* player;

public:
	Collider();
	virtual ~Collider();

	virtual void Init() override;
	virtual void Update(float dt) override;

	void SetPlayer(Player* player);
};
