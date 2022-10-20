#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include <map>

// static함수를 이용해서 키보드 및 마우스 입력을 검사할 수 있는 클래스

using namespace sf;
using namespace std;

enum class Axis
{
	Horizontal,
	Vertical,
};

struct AxisInfo
{
	Axis axis;
	list<Keyboard::Key> positives;
	list<Keyboard::Key> negatives;
};

class InputMgr
{
private:
	static map<Axis, AxisInfo> axisInfoMap;

	static vector<bool> downList;
	static vector<bool> ingList;
	static vector<bool> upList;
	static list<Keyboard::Key> keyList;
public:
	static void Init();
	static void ClearInput();
	static void UpdateInput(const Event& ev);

	static bool GetKeyDown(Keyboard::Key key);
	static bool GetKey(Keyboard::Key key);
	static bool GetKeyUp(Keyboard::Key key);

	static float GetAxisRaw(Axis axis);
};
