#include "Enemy.h"
#include "../../Framework/Animator.h"
#include "../../Framework/RayCast.h"
#include "../../Scene/SceneMgr.h"
#include "../Collider.h"
#include "../Player.h"
#include "../../Ui/EnemyHpBarUi.h"

Enemy::Enemy(Types type)
	:type(type), currState(States::None), animator(nullptr), platform(nullptr), playerDetected(false), stiffDuration(0.7f), stiffTimer(0.f), stiffDistance(0.f),
	totalHp(0), currHp(0), hpBar(nullptr), attackDmg(0)
{
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
	SpriteObj::Init();
	direction = { 1.f, 0.f };
	gravityApply = true;
	gravity = 8.f;
	SetOrigin(Origins::BC);
	for (int i = 0; i < 3; ++i)
	{
		RayCast* ray = new RayCast();
		ray->SetDirection({ 0.f, 1.f });
		ray->SetRayLength(1.0f);
		ray->SetLayerMask((int)Scene::Layer::Collider);
		rays.push_back(ray);
	}
	animator = new Animator();
	animator->SetTarget(&sprite);
	hpBar = new EnemyHpBarUi();
}

void Enemy::Release()
{
}

void Enemy::Reset()
{
	playerDetected = false;
}

void Enemy::Update(float dt)
{
	if (currState == States::Hit)
	{
		stiffTimer += dt;
		if (stiffTimer >= stiffDuration)
			SetState(States::Idle);
	}
	gravityApply = true;
	platform = nullptr;
	if (animator != nullptr)
		animator->Update(dt);
	Utils::SetOrigin(hitbox, Origins::BC);
	FloatRect hitBound = hitbox.getGlobalBounds();
	rays[0]->SetStartPos({ hitBound.left, hitBound.top + hitBound.height });
	rays[1]->SetStartPos({ hitBound.left + hitBound.width * 0.5f, hitBound.top + hitBound.height });
	rays[2]->SetStartPos({ hitBound.left + hitBound.width, hitBound.top + hitBound.height });
	for (int i = 0; i < 3; ++i)
	{
		if (direction.y < 0.f)
			break;
		rays[i]->Update(dt);
		if (rays[i]->RayHit())
		{
			auto collider = rays[i]->GetClosestObj();
			auto colliderBound = collider->GetHitBounds();
			if (Utils::EqualFloat(rays[i]->RayHitDistance(), 0.f) && rays[i]->GetHittingPoint().y - colliderBound.top < hitBound.height * 0.2f)
			{
				gravityApply = false;
				direction.y = 0.f;
				platform = rays[i]->GetClosestObj();
				position.y = colliderBound.top;
				break;
			}
		}
	}
	Scene* playScene = SCENE_MGR->GetCurrentScene();
	auto& layOut = playScene->GetLayout();
	for (auto collider : *layOut[(int)Scene::Layer::Collider])
	{
		if (((Collider*)collider)->GetType() == Collider::Type::AllSide)
			OnCollisionBlock(collider->GetHitBounds());
	}

	SpriteObj::Update(dt);
	if (direction.y > 5.f)
		direction.y = 5.f;
}

void Enemy::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
	hpBar->Draw(window);
}

void Enemy::OnCollisionBlock(const FloatRect& blockBound)
{
	FloatRect hitBound = hitbox.getGlobalBounds();
	if (!hitBound.intersects(blockBound))
		return;
	Vector2f hitCenter(hitBound.left + hitBound.width * 0.5f, hitBound.top + hitBound.height * 0.5f);
	if (hitCenter.y - hitBound.height * 0.3f > blockBound.top + blockBound.height && direction.y < 0.f)
	{
		Translate({ 0.f, blockBound.top + blockBound.height - hitBound.top });
		direction.y = 0.f;
		return;
	}
	if (hitCenter.y + hitBound.height * 0.3f <= blockBound.top)
		return;

	if (hitCenter.x > blockBound.left + blockBound.width && direction.x < 0.f && hitBound.top + hitBound.height > blockBound.top)
	{
		Translate({ blockBound.left + blockBound.width - hitBound.left, 0.f });
		direction.x *= -1.f;
		return;
	}
	else if (hitCenter.x < blockBound.left && direction.x > 0.f && hitBound.top < blockBound.top + blockBound.height)
	{
		Translate({ blockBound.left - (hitBound.left + hitBound.width), 0.f });
		direction.x *= -1.f;
		return;
	}
}

void Enemy::OnHit(float dmg)
{
	SetState(States::Hit);
	stiffTimer = 0.f;
	Object* player = SCENE_MGR->GetCurrentScene()->FindGameObj("player");
	auto hitDirX = Utils::UnitizationFloat(((Player*)player)->GetLastDirX());
	if (hitDirX < 0.f)
		sprite.setScale(1, 1);
	else if (hitDirX > 0.f)
		sprite.setScale(-1, 1);
	Translate({ hitDirX * stiffDistance, 0.f });
	currHp -= dmg;
	if (currHp <= 0)
	{
		SetActive(false);
		return;
	}
	hpBar->Update();
}
