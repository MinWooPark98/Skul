#pragma once
#include "../3rd/Singleton.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class Framework : public Singleton<Framework>
{
protected:
	RenderWindow window;
	Vector2i windowSize;

	// TimeMgr
	Clock clock;
	Time deltaTime;
	float timeScale;

public:
	Framework();
	virtual ~Framework();

	float GetDT() const;
	float GetRealDT() const;
	const Vector2i& GetWindowSize() const;

	bool Init(int width, int height);
	bool Do();

	 RenderWindow& GetWindow();
};

#define FRAMEWORK (Framework::GetInstance())