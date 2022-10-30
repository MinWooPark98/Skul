#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Enemy;

class EnemyHpBarUi
{
private:
	RectangleShape totalHpBar;
	RectangleShape currHpBar;

	const Enemy* enemy;

public:
	EnemyHpBarUi();
	~EnemyHpBarUi();

	void SetEnemy(const Enemy* enemy);

	void Init();
	void Update();
	void Draw(RenderWindow& window);
	void SetPos(const Vector2f& pos);
};
