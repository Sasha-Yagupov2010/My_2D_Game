#include <iostream>
using namespace std;


#include <SFML/Graphics.hpp>
using namespace sf;

#include "Settings.h"
#include "Player.h"
#include "Mytext.h"

/*
class Button {
    Button::Button(x,y,syze)
private:
    uint16_t x = 0;
    uint16_t y = 0;

    int size_x = 0;
    int size_y = 0;

    bool visible = false;

public:
    void show() { visible = true; }

    void set_pos(uint16_t x1, uint16_t y1)
    {
        x = x1;
        y = y1;
    }

    void set_resolution(int size_x1, int size_y1)
    {
        size_x = size_x1;
        size_y = size_y1;
    }

    bool isPressed() {
        return true;

        return false;
    }

};
*/


int main()
{
    Settings mysettings;
    mysettings.height = 600;
    mysettings.width = 400;
    mysettings.fps = 60;

    RenderWindow window( VideoMode(mysettings.height, mysettings.width), L"Game",  Style::Default);

    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(mysettings.fps);

    RectangleShape button(Vector2f(200, 50));
    button.setFillColor(Color::Blue);
    button.setPosition((mysettings.width - 200) / 2, (mysettings.height - 50) / 2); // по центру


    //текст тестирование
    MyText myText("myfonts/arialmt.ttf", "Play");
    myText.setVisible(true);
    myText.setPosition(100.f, 50.f);
    

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
                if (button.getGlobalBounds().contains(mousePos.x, mousePos.y))
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
            window.draw(button);
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
