#pragma once
#include "Object.h"
#include "../Framework/ObjectPool.h"

class SpriteObj;

class DisplayObj : public Object
{
protected:
	ObjectPool<SpriteObj> displays;

public:
	DisplayObj();
	virtual ~DisplayObj();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Reset() override;

	virtual void Update(float dt) override;
};
