#include <SFML/Graphics.hpp>
#include "pch.h"
#include "Bat.h"
#include "Ball.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Pong");

    InputMgr::Init();
    Bat bat;
    Ball ball(bat, { {0.f,0.f},{1920.f,1080.f} });

    bool isBallActive = false;

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Time deltatime = clock.restart();
        float dt = deltatime.asSeconds();
        InputMgr::Clear();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            InputMgr::UpdateEvent(event);
        }
        InputMgr::Update(dt);

        if (!isBallActive && InputMgr::GetKeyDown(sf::Keyboard::Space))
        {
            ball.Fire({1.f,-1.f}, 500.f);
            isBallActive = true;
        }

        bat.Update(dt);

        if (!isBallActive)
        {
            ball.shape.setPosition(bat.shape.getPosition());
        }
        ball.Update(dt);
        if (ball.isDead)
        {
            isBallActive = true; 
            ball.Fire({ 0.f,0.f }, 0.f);
            //게임 재시작 대기
        }
        else if (ball.isBoundBat)
        {
            //점수추가
        }

        window.clear();
        bat.Draw(window);
        ball.Draw(window);
        window.display();
    }

    return 0;
}