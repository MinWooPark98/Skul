#pragma once
#include "Object.h"

class TextObj;

class TextButtons : public Object
{
protected:
	vector<TextObj*> buttons;
	int vecIdx;
	int textSize;
	float buttonDistance;

public:
	TextButtons();
	virtual ~TextButtons();

	virtual void Release() override;
	virtual void Reset() override;

	void AddButton(const string& text);
	void SetCharacterSize(int size);
	void SetDistance(float distance) { buttonDistance = distance; }

	void SetVecIdx(int idx) { vecIdx = idx; }
	int GetVecIdx() const { return vecIdx; }

	virtual void Update(float dt) override;
	virtual	void Draw(RenderWindow& window) override;
};

