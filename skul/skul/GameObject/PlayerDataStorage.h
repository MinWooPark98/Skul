#pragma once

class PlayerDataStorage
{
	// 스탯, 공격력 등등 skul에 따라 저장되어야 하는데 아직 완성하지 못해서 임시로 player에 있는 체력, 공격력, 이동속도 등만 저장
private:
	int totalHp;
	int currHp;
	int attackDmg;
	float normalSpeed;
	float dashSpeed;
	int jumpableCnt;

public:
	PlayerDataStorage();
	~PlayerDataStorage();

	void Save();
	void Load();
};

