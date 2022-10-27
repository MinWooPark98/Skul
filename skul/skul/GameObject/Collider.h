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

public:
	Collider();
	virtual ~Collider();

	virtual void Init() override;

	void SetType(Type type) { this->type = type; }
	Type GetType() { return type; }
};
