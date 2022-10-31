#pragma once
#include "Scene.h"

class TextButtons;

class TitleScene : public Scene
{
protected:
	TextButtons* buttons;

public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Init() override;
	virtual void Update(float dt) override;

	virtual void Enter() override;
	virtual void Exit() override;
};

