#pragma once
#include "../GameObject/Object.h"
#include <list>

class TextObj;
class TextButton;

class SaveLoadUi : public Object
{
protected:
	RectangleShape frame;

	TextObj* showFilePath;
	string filePath;

	TextButton* confirm;

public:
	SaveLoadUi();
	~SaveLoadUi();

	virtual void Init() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void Save();
	void Load();
};
