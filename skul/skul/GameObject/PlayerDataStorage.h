#pragma once

class PlayerDataStorage
{
	// ����, ���ݷ� ��� skul�� ���� ����Ǿ�� �ϴµ� ���� �ϼ����� ���ؼ� �ӽ÷� player�� �ִ� ü��, ���ݷ�, �̵��ӵ� � ����
private:
	int totalHp;
	int currHp;
	int attackDmg;
	float speed;
	int jumpableCnt;

public:
	PlayerDataStorage();
	~PlayerDataStorage();

	void Save();
	void Load();
};

