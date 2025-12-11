#include <iostream>
using namespace std;


#include <SFML/Graphics.hpp>
using namespace sf;

#include "Settings.h"
#include "Player.h"
#include "Mytext.h"
#include "MyButton.h"
#include "GameMap.h"

void menu(RenderWindow& window, Settings& mysettings, bool& gameStarted)
{
    //кнопочки
    MyButton play_button(200, 50, Color::White, (mysettings.width - 200)/2, (mysettings.height - 50) * 0.3);
    play_button.setVisible(true);

    MyButton exit_button(200, 50, Color::White, (mysettings.width - 200)/2, (mysettings.height - 50) * 0.425);
    exit_button.setVisible(true);

    //текстовые блоки
    MyText menu_text("myfonts/arial_bolditalicmt.ttf", "Menu",72);
    menu_text.setVisible(true);
    //menu_text.setSize(100);
    menu_text.setColor(Color::White);
    menu_text.setPosition((mysettings.width-200)/2, mysettings.height*0.1);

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

void singleGame(RenderWindow& window, Settings& mysettings, Player& player) {
    float size = player.size; //radius
    CircleShape circle(size / 2);
    player.set_position(0, mysettings.height/2);
    circle.setPosition(player.x_pos, player.y_pos);

    // Устанавливаем цвет заливки
    circle.setFillColor(Color::Red);
    circle.setOutlineColor(Color::White);
    circle.setOutlineThickness(size / 14);

    // Автоматический расчет размера тайлов относительно экрана
    const int mapWidthTiles = 24;   // количество тайлов по ширине
    const int mapHeightTiles = 16;  // количество тайлов по высоте

    
    int tileSize = min(mysettings.width / mapWidthTiles, mysettings.height / mapHeightTiles);

    GameMap gameMap(mapWidthTiles, mapHeightTiles, tileSize);

    if (!gameMap.loadFromFile("maps/fastrunner.txt", Color::White)) {
        cout << "error: map not loaded!"<<endl;
    }

    bool gameRun = true;
    uint8_t speed = player.speed;

    while (gameRun)
    {
        // Сохраняем старую позицию для отката при коллизии
        float oldX = player.x_pos;
        float oldY = player.y_pos;

        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            player.move(-speed, 0);
            circle.move(-speed, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            player.move(speed, 0);
            circle.move(speed, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            player.move(0, -speed);
            circle.move(0, -speed);
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            player.move(0, speed);
            circle.move(0, speed);
        }

        // Проверяем коллизии
        if (gameMap.checkCollision(player.x_pos, player.y_pos, size) ||
            player.x_pos < 0 || player.x_pos > mysettings.width - size ||
            player.y_pos < 0 || player.y_pos > mysettings.height - size) {

            // Откатываем позицию
            player.set_position(oldX, oldY);
            circle.setPosition(oldX, oldY);
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            player.set_position(0, 0);
            gameRun = false;
        }

        window.clear();


        gameMap.draw(window);
        window.draw(circle);

        window.display();
    }
}

int main()
{
    /* настройки проекта */
    Settings mysettings;
    mysettings.height = 800;
    mysettings.width = 1200;
    mysettings.fps = 60;

    Player player;

    RenderWindow window( VideoMode(mysettings.width, mysettings.height), L"Game",  Style::Default);

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
        if (gameStarted) {
            singleGame(window, mysettings,player); 
            gameStarted = false;
        }
        menu(window, mysettings, gameStarted);
    }
     return 0;
}
