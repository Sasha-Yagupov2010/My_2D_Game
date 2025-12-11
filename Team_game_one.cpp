#include <iostream>
using namespace std;


#include <SFML/Graphics.hpp>
using namespace sf;

#include "Settings.h"
#include "Player.h"
#include "Mytext.h"
#include "MyButton.h"

void menu(RenderWindow& window, Settings& mysettings, bool& gameStarted)
{
    //кнопочки
    MyButton play_button(200, 50, Color::White, (mysettings.width - 200) / 2, (mysettings.height - 50) / 2);
    play_button.setVisible(true);

    MyButton exit_button(200, 50, Color::White, (mysettings.width - 200) / 2, (mysettings.height - 50) / 3);
    exit_button.setVisible(true);

    //текстовые блоки
    MyText menu_text("myfonts/arialmt.ttf", "Menu");
    menu_text.setVisible(true);
    menu_text.setColor(Color::White);
    menu_text.setPosition(100.f, 100.f);

    MyText play_text("myfonts/arialmt.ttf", "Play");
    play_text.setVisible(true);
    play_text.setColor(Color::Black);
    play_text.center(play_button.get_shape().getGlobalBounds());


    MyText exit_text("myfonts/arialmt.ttf", "Exit");
    exit_text.setVisible(true);
    exit_text.setColor(Color::Black);
    exit_text.center(exit_button.get_shape().getGlobalBounds());


    window.clear();
    play_button.draw(window);
    exit_button.draw(window);

    menu_text.draw(window);
    play_text.draw(window);
    exit_text.draw(window);

    window.display();

    if (play_button.is_pressed(window)) { gameStarted = true; }
    if (exit_button.is_pressed(window)) { window.close(); }

}

int main()
{
    /* настройки проекта */
    Settings mysettings;
    mysettings.height = 600;
    mysettings.width = 400;
    mysettings.fps = 60;

    RenderWindow window( VideoMode(mysettings.height, mysettings.width), L"Game",  Style::Default);

    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(mysettings.fps);
    /* =============================== */
  

    bool gameStarted = false;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        //menu
        menu(window, mysettings, gameStarted);
    }
     return 0;
}
