#pragma once
#include "../../SpriteObj.h"

class Animator;
class ElderEnt;
class Player;

class ElderEntHand : public SpriteObj
{
protected:
	Animator* handAnim;

	Vector2f idlePos;
	Vector2f stompPos;
	RectangleShape attackBox;
	int attackDmg;

	bool isReady;
	bool attackable;

	ElderEnt* mainBody;
	Player* player;

	bool playerHit;

	bool cameraShake;
	float shakedelay;
	float shakeTimer;
	int currShake;
	int totalshake;
	Vector2f shakedView;

public:
	ElderEntHand();
	virtual ~ElderEntHand();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	bool GetReady() const { return isReady; }
	bool GetAttackable() const { return attackable; }
	void SetMainBody(ElderEnt* body) { mainBody = body; }

	virtual void ReturnIdlePos();
	void UpdateIdle(float dt);

	virtual void ReturnStompPos();
	void UpdateNormalStomp(float dt);
	virtual void OnCompleteStomp();
	void CameraShake();
	void NormalStomp();
};

