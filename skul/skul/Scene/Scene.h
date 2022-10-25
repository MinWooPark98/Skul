#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "../GameObject/Object.h"

using namespace sf;
using namespace std;

enum class Scenes
{
	MapEditor,
};

class UiMgr;
class Scene
{
protected:
	Scenes type;
	list<Object*> objList;
	//list<Object*> uiObjList;
	View worldView;
	View uiView;
	UiMgr* uiMgr;

public:
	Scene(Scenes type);
	virtual ~Scene();

	virtual void Init() = 0; //생성
	virtual void Release();	 //해제

	virtual void Reset() {}

	virtual void Enter();
	virtual void Exit() = 0;

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	Texture* GetTexture(const string path) const;

	View& GetWorldView() { return worldView; }
	View& GetUiView() { return uiView; }

	Vector2f ScreenToWorld(Vector2i screenPos);
	Vector2f ScreenToUiPosition(Vector2i screenPos);

	void AddGameObject(Object* obj);
	void AddGameObjectFirst(Object* obj);
	void DelGameObject(Object* obj);
	Object* FindGameObj(string name);
	UiMgr* GetUiMgr() { return uiMgr; }
};

