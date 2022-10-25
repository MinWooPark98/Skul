#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "../GameObject/Object.h"

using namespace sf;
using namespace std;

enum class Scenes
{
	MapEditor,
	Play,
};

class UiMgr;
class Scene
{
protected:
	Scenes type;
	list<Object*> objList;

	bool isPause;

	View worldView;
	View uiView;
	UiMgr* uiMgr;

public:
	Scene(Scenes type);
	virtual ~Scene();

	virtual void Init() = 0; //����
	virtual void Release();	 //����

	virtual void Reset() {}

	virtual void Enter();
	virtual void Exit() = 0;

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	Texture* GetTexture(const string path) const;

	void SetPause(bool pause) { isPause = pause; }
	bool GetPause() const { return isPause; }

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

