#include <SFML/Graphics.hpp>

int main()
{

    sf::RenderWindow window(sf::VideoMode(600, 400), L"Иллюзия", sf::Style::Default);

    window.setVerticalSyncEnabled(true);
    sf::Vector2f a1{ 100,100 };
    sf::Vector2f a2{ 500,200 };
    sf::Vector2f a3{ 500,200 };
    sf::Vector2f a4{ 100,300 };
    bool lu = true;
    sf::ConvexShape convex;
    convex.setPointCount(4);
    convex.setFillColor(sf::Color::Magenta);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (lu) { a1.y += 1; a4.y -= 1; a2.y -= 1; a3.y += 1; if (a1.y > 200) lu = false; }
        else { a1.y -= 1; a4.y += 1; a2.y += 1; a3.y -= 1; if (a1.y < 100) lu = true; }
        convex.setPoint(0, a1);
        convex.setPoint(1, a2);
        convex.setPoint(2, a3);
        convex.setPoint(3, a4);
        window.clear(sf::Color::Blue);
        window.draw(convex);
        window.display();
    }
    return 0;
}