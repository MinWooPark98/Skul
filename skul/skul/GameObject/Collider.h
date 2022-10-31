#pragma once
#include "Object.h"

class Player;

class Collider : public Object
{
public:
	enum class Types
	{
		None = -1,
		TopSide,
		AllSide,
	};

protected:
	Types type;

public:
	Collider();
	virtual ~Collider();

	virtual void Init() override;

	void SetType(Types type);
	Types GetType() { return type; }

	virtual void SetHitBox(const FloatRect rect);
};
