#pragma once
#include "Scene.h"

class PlayScene : public Scene
{
public:
	enum class Layer
	{
		BackGround,
		BackObject,
		Tile,
		Reward,
		NPC,
		Enemy,
		Player,
		Collider,
		Front,
		Count,
	};

protected:
	vector<list<Object*>*> layOut;

public:
	PlayScene();
	virtual ~PlayScene();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	virtual void Enter() override;
	virtual void Exit() override;

	vector<list<Object*>*>& GetLayout() { return layOut; }
};

