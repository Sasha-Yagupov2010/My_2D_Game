#include <iostream>
using namespace std;


#include <SFML/Graphics.hpp>
using namespace sf;

#include "Settings.h"
#include "Player.h"
#include "Mytext.h"
#include "MyButton.h"

int main()
{
    Settings mysettings;
    mysettings.height = 600;
    mysettings.width = 400;
    mysettings.fps = 60;

    RenderWindow window( VideoMode(mysettings.height, mysettings.width), L"Game",  Style::Default);

    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(mysettings.fps);

  
    //текст тестирование
    MyText myText("myfonts/arialmt.ttf", "Play");
    myText.setVisible(true);
    myText.setPosition(100.f, 50.f);

    //кнопочка
    MyButton button(200, 50, Color::Blue, (mysettings.width - 200) / 2, (mysettings.height - 50) / 2);
    button.setVisible(true);
    
    

    bool gameStarted = false;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
         }
        
        if (event.type == Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == Mouse::Left)
            {
                Vector2i mousePos = Mouse::getPosition(window);
                if (button.get_shape().getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    // Нажата кнопка "Играть"
                    gameStarted = true;
                }
            }
        }
        
        window.clear();

        if (!gameStarted)
        {
            // Рисуем кнопку "Играть"

            button.draw(window);
            myText.draw(window);
        }
        else
        {
            // Тут уже идет сама игра
            // Можно рисовать игровые объекты
        }
        window.display();
    }
    return 0;
}
