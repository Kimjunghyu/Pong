#pragma once

enum class Axis
{
	Horizontal,
	Vertical,
};

struct AxisInfo
{
	Axis axis;

	std::list<sf::Keyboard::Key>positives;
	std::list<sf::Keyboard::Key>negatives;

	float sensi;
	float value;
};

class InputMgr
{
private:
	static std::map<Axis, AxisInfo> axisInfoMap;

	static std::list<sf::Keyboard::Key> downList;
	static std::list<sf::Keyboard::Key> upList;
	static std::list<sf::Keyboard::Key> ingList;

public:
	static void Init();

	static void UpdateEvent(const sf::Event& ev);
	static void Update(float dt);

	static void Clear();

	static float GetAxisRaw(Axis axis); //-1.0, 0, 1.0
	static float GetAxis(Axis axis); //-1.0~1.0
	static bool GetKeyDown(sf::Keyboard::Key key);
	static bool GetKeyUp(sf::Keyboard::Key key);
	static bool GetKey(sf::Keyboard::Key key);

};

