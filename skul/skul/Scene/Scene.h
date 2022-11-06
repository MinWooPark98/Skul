#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "../GameObject/Object.h"

using namespace sf;
using namespace std;

enum class Scenes
{
	Title,
	MapEditor,
	MonsterScene,
	NpcScene,
	BossScene,
};

class UiMgr;
class Scene
{
public:
	enum class Layer
	{
		BackGround,
		BackObject,
		Tile,
		Gate,
		Reward,
		NPC,
		Enemy,
		Boss,
		Player,
		Collider,
		Front,
		Count,
	};

protected:
	Scenes type;
	vector<list<Object*>*> layOut;
	list<Object*> objList;

	bool isPause;
	Vector2f objMousePos;

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
	virtual void Exit();

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
	const Vector2f& GetObjMousePos() const { return objMousePos; }

	vector<list<Object*>*>& GetLayout() { return layOut; }
};

