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

	Text& GetSFMLText() { return text; }
	void SetFont(Font& font);
	void SetText(string text);
	void SetOrigin(Origins origin);
	const string GetText() const;
};

