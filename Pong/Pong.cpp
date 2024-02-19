#include <SFML/Graphics.hpp>
#include "pch.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "Pong");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);


    InputMgr::Init();

    while (window.isOpen())
    {
        InputMgr::Clear();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            InputMgr::UpdateEvent(event);
        }

        std::cout << InputMgr::GetAxisRaw(Axis::Horizontal) << std::endl;

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}