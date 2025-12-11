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

void singleGame(RenderWindow& window, Settings& mysettings, Player& player) {
    float size = player.size; //radius
    CircleShape circle(size / 2);
    circle.setPosition(player.x_pos, player.y_pos);

    // Устанавливаем цвет заливки
    circle.setFillColor(Color::Red);
    circle.setOutlineColor(Color::White);
    circle.setOutlineThickness(size / 14);

    // Автоматический расчет размера тайлов относительно экрана
    const int mapWidthTiles = 12;  // количество тайлов по ширине
    const int mapHeightTiles = 8;  // количество тайлов по высоте

    // Размер тайла = минимум из (ширина_экрана/тайлы_по_ширине, высота_экрана/тайлы_по_высоте)
    int tileSize = std::min(mysettings.width / mapWidthTiles, mysettings.height / mapHeightTiles);

    // Создаем карту с автоматическим размером тайлов
    GameMap gameMap(mapWidthTiles, mapHeightTiles, tileSize);

    // Загружаем уровень
    std::vector<std::vector<int>> level = {
        {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    gameMap.loadFromArray(level, Color::White);

    bool gameRun = true;
    uint8_t speed = 5;

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

        // Рисуем карту ПЕРВОЙ (фон)
        gameMap.draw(window);

        // Рисуем игрока ПОВЕРХ карты
        window.draw(circle);

        window.display();
    }
}

int main()
{
    /* настройки проекта */
    Settings mysettings;
    mysettings.height = 400;
    mysettings.width = 600;
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
