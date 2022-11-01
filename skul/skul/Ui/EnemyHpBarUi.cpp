#include "EnemyHpBarUi.h"
#include "../GameObject/Enemy/Enemy.h"
#include "../Framework/Utils.h"

EnemyHpBarUi::EnemyHpBarUi()
	:enemy(nullptr)
{
}

EnemyHpBarUi::~EnemyHpBarUi()
{
}

void EnemyHpBarUi::SetEnemy(const Enemy* enemy)
{
	this->enemy = enemy;
}

void EnemyHpBarUi::Init()
{
	totalHpBar.setSize({ enemy->GetHitBounds().width * 1.1f, 5.f });
	currHpBar.setSize(totalHpBar.getSize());
	totalHpBar.setFillColor({ 128, 0, 0, 255 });
	currHpBar.setFillColor({ 255, 0, 0, 255 });
	
}

void EnemyHpBarUi::Reset()
{
	currHpBar.setSize(totalHpBar.getSize());
}

void EnemyHpBarUi::Update()
{
	Vector2f totalHpBarSize = totalHpBar.getSize();
	currHpBar.setSize({ totalHpBarSize.x * enemy->GetCurrHp() / enemy->GetTotalHp(), totalHpBarSize.y });
}

void EnemyHpBarUi::Draw(RenderWindow& window)
{
	window.draw(totalHpBar);
	window.draw(currHpBar);
}

void EnemyHpBarUi::SetPos(const Vector2f& pos)
{
	Utils::SetOrigin(totalHpBar, Origins::MC);
	auto& enemyPos = enemy->GetPos();
	totalHpBar.setPosition({ enemyPos.x, enemyPos.y + 5.f });
	auto totalHpBarBound = totalHpBar.getGlobalBounds();
	currHpBar.setPosition(totalHpBarBound.left, totalHpBarBound.top);
}
