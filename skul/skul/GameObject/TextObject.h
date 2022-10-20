#pragma once
#include "Object.h"
#include <string>

using namespace std;

class TextObject : public Object
{
protected:
	Text text;

public:
	TextObject();
	virtual ~TextObject();

	virtual void Init();
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	void SetString(const string& string);
	void SetFont(const Font& font);
};

