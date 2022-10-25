#pragma once
#include "../GameObject/Object.h"
#include <list>

class TextObj;
class TextButton;

class SaveLoadUi : public Object
{
public:
	enum class Mode
	{
		None = -1,
		Save,
		Load,
		Count,
	};
protected:
	Mode mode;

	RectangleShape frame;
	TextObj* showMode;
	TextObj* showFilePath;
	string filePath;
	TextObj* showFailure;
	bool isFailed;
	float showFailureTimer;

	TextButton* yesButton;
	TextButton* noButton;

public:
	SaveLoadUi();
	~SaveLoadUi();

	virtual void Init() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetShowFilePath(const string& filePath);

	void SaveMode();
	void LoadMode();
};
