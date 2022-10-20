#pragma once
#include "Object.h"

enum class Origins;
class TextObj : public Object
{
protected:
	Text text;

public:
	TextObj();
	virtual ~TextObj();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(Vector2f position);

	virtual Text& GetSFMLText() { return text; }
	virtual void SetFont(Font& font);
	virtual void SetText(string text);
	virtual void SetOrigin(Origins origin);
	virtual const string GetText() const;
};

