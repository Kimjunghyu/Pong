#include "pch.h"
#include "InputMgr.h"

std::map<Axis, AxisInfo> InputMgr::axisInfoMap;
std::list<sf::Keyboard::Key> InputMgr::downList;
std::list<sf::Keyboard::Key> InputMgr::upList;
std::list<sf::Keyboard::Key> InputMgr::ingList;

void InputMgr::Init()
{
// Horizontal
    AxisInfo infoH;
    infoH.axis = Axis::Horizontal;
    infoH.positives.push_back(sf::Keyboard::D);
    infoH.positives.push_back(sf::Keyboard::Right);
    infoH.negatives.push_back(sf::Keyboard::A);
    infoH.negatives.push_back(sf::Keyboard::Left);
    infoH.sensi = 5.f;
    infoH.value = 0.f;
    axisInfoMap.insert({ infoH.axis, infoH });

    //Vertical
    AxisInfo infoV;
    infoV.axis = Axis::Horizontal;
    infoV.positives.push_back(sf::Keyboard::S);
    infoV.positives.push_back(sf::Keyboard::Down);
    infoV.negatives.push_back(sf::Keyboard::W);
    infoV.negatives.push_back(sf::Keyboard::Up);
    infoV.sensi = 5.f;
    infoV.value = 0.f;
    axisInfoMap.insert({ infoV.axis, infoV });
}

void InputMgr::UpdateEvent(const sf::Event& ev)
{
    switch (ev.type)
    {
    case sf::Event::KeyPressed:
        if (!GetKey(ev.key.code))
        {
            ingList.push_back(ev.key.code);
            downList.push_back(ev.key.code);
        }
        break;
    case sf::Event::KeyReleased:
        ingList.remove(ev.key.code);
        upList.push_back(ev.key.code);
        break;
    }
}

void InputMgr::Update(float dt)
{

}

void InputMgr::Clear()
{
    downList.clear();
    upList.clear();
}

float InputMgr::GetAxisRaw(Axis axis)
{
    auto findInfo = axisInfoMap.find(axis);
    if (findInfo == axisInfoMap.end())
        return 0.f;
    const auto& info = findInfo->second;
  //  auto it = ingList.begin();//정방향 순회
    auto it = ingList.rbegin(); // 역방향 순회용 it (r)end = 처음 전에 있는 list 값 x 
    while (it != ingList.rend())
    {
        sf::Keyboard::Key key = *it;

        if (std::find(info.positives.begin(), info.positives.end(), key) != info.positives.end())
        {
            return 1.f;
        }
        if (std::find(info.negatives.begin(), info.negatives.end(), key) != info.negatives.end())
        {
            return -1.f;
        }
        ++it;
    }



    return 0.0f;
}

float InputMgr::GetAxis(Axis axis)
{
    return 0.0f;
}

bool InputMgr::GetKeyDown(sf::Keyboard::Key key)
{
    //std::list<sf::Keyboard::Key>::iterator it = downList.begin

    //for (auto it = downList.begin(); it != downList.end(); ++it)
    //{
    //    if (*it == key)
    //        return true;
    //}

    //for (auto k : downList)
    //{
    //    if (k == key)
    //        return true;
    //}

    return std::find(downList.begin(), downList.end(), key) != downList.end();
}

bool InputMgr::GetKeyUp(sf::Keyboard::Key key)
{
    return std::find(upList.begin(), upList.end(), key) != upList.end();
}

bool InputMgr::GetKey(sf::Keyboard::Key key)
{
    return std::find(ingList.begin(), ingList.end(), key) != ingList.end();
}
