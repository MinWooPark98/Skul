#pragma once
#include "Scene.h"

class PlayScene : public Scene
{
protected:
	string mapFilePath;

public:
	PlayScene(Scenes scene);
	virtual ~PlayScene();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	virtual void Enter() override;
	virtual void Exit() override;

	void SetMapFilePath(const string& path) { mapFilePath = path; }
};

