#pragma once
#include "../GameObject/Object.h"
#include <list>

class Scene;
class UiMgr : public Object
{
protected:
	list<Object*> uiObjList;
	Scene* parentScene;

public:
	UiMgr(Scene* scene);
	virtual ~UiMgr();

	virtual void Init();
	virtual void Release();

	virtual void Reset();

	virtual void SetPos(const Vector2f& pos);

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	Object* FindUiObj(string name);
};

