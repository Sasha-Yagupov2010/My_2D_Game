#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
using namespace std;
using namespace sf;

#include "Settings.h"
#include "Player.h"
#include "Mytext.h"
#include "MyButton.h"
#include "GameMap.h"
#include "Flag.h"


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

void singleGame(RenderWindow& window, Settings& mysettings) {
    //для каждой игры свой игрок и 
    const uint8_t mindist_to_flag = 5;

    Player player;
    Flag flag;

    Player enemy;
    Flag enemyflag;

    uint16_t percent_of_resizing = (mysettings.height / 400 * 100);


    float teamOneBaseX = 0;
    float teamOneBaseY = mysettings.height / 2;

    float teamTwoBaseX = mysettings.width;
    float teamTwoBaseY = mysettings.height / 2;

    /*============================ основной игрок =============================*/
    // игрок
    player.size = percent_of_resizing *player.size/100;
    player.speed = percent_of_resizing * player.speed / 100;
    //float size = player.size; 

    CircleShape player_circle(player.size / 2);
    player.set_position(teamOneBaseX, teamOneBaseY);

    player_circle.setPosition(player.x_pos, player.y_pos);
    player_circle.setFillColor(Color::Red);
    player_circle.setOutlineColor(Color::White);
    player_circle.setOutlineThickness(player.size / 14);


    // флажок
    flag.size = percent_of_resizing * flag.size / 100;

    CircleShape flag_circle(flag.size / 2);
    flag.set_position(teamOneBaseX, teamOneBaseY);

    flag_circle.setPosition(flag.x_pos, flag.y_pos);
    flag_circle.setFillColor(Color::Green);
    flag_circle.setOutlineColor(Color::Red);
    flag_circle.setOutlineThickness(flag.size/7);
    /*=========================================================*/

    /*============================ второстепенный игрок =============================*/
    // игрок
    enemy.size = percent_of_resizing * enemy.size / 100;
    enemy.speed = percent_of_resizing * enemy.speed / 100;
    //float size = player.size; 

    CircleShape enemy_circle(enemy.size / 2);
    enemy.set_position(teamTwoBaseX -enemy.size, teamTwoBaseY);

    enemy_circle.setPosition(enemy.x_pos, enemy.y_pos);
    enemy_circle.setFillColor(Color::Blue);
    enemy_circle.setOutlineColor(Color::White);
    enemy_circle.setOutlineThickness(enemy.size / 14);


    // флажок
    enemyflag.size = percent_of_resizing * enemyflag.size / 100;

    CircleShape enemyflag_circle(enemyflag.size / 2);
    enemyflag.set_position(teamTwoBaseX - enemy.size, teamTwoBaseY);

    enemyflag_circle.setPosition(enemyflag.x_pos, enemyflag.y_pos);
    enemyflag_circle.setFillColor(Color::Green);
    enemyflag_circle.setOutlineColor(Color::Blue);
    enemyflag_circle.setOutlineThickness(enemyflag.size / 7);
    /*=========================================================*/



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
            player_circle.move(-speed, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            player.move(speed, 0);
            player_circle.move(speed, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            player.move(0, -speed);
            player_circle.move(0, -speed);
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            player.move(0, speed);
            player_circle.move(0, speed);
        }

        if (Keyboard::isKeyPressed(Keyboard::E)) {
            int distance = sqrt(pow((enemyflag.x_pos - player.x_pos), 2) + pow((enemyflag.y_pos - player.y_pos), 2));
            if (distance < mindist_to_flag) player.flag = true; 
            else player.flag = false;
        }


        // Проверяем коллизии
        if (gameMap.checkCollision(player.x_pos, player.y_pos, player.size) ||
            player.x_pos < 0 || player.x_pos > mysettings.width - player.size ||
            player.y_pos < 0 || player.y_pos > mysettings.height - player.size) {

            // Откатываем позицию
            player.set_position(oldX, oldY);
            player_circle.setPosition(oldX, oldY);
        }
        //exit to menu
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            player.set_position(0, 0);
            gameRun = false;
        }

        //move flag
        if (player.flag) {
            enemyflag.set_position(player.x_pos, player.y_pos);
            enemyflag_circle.setPosition(enemyflag.x_pos, enemyflag.y_pos);
        }

        int distance = sqrt(pow((enemyflag.x_pos - teamOneBaseX), 2) + pow((enemyflag.y_pos - teamOneBaseY), 2));
        if (distance < mindist_to_flag) {
            enemyflag.set_position(teamTwoBaseX - enemy.size, teamTwoBaseY);
            enemyflag_circle.setPosition(teamTwoBaseX - enemy.size, teamTwoBaseY);

            player.score += 1;
            player.flag = false;
        }


        window.clear();


        gameMap.draw(window);
        window.draw(player_circle);
        window.draw(flag_circle);

        window.draw(enemyflag_circle);
        window.draw(enemy_circle);

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
            singleGame(window, mysettings); 
            gameStarted = false;
        }
        menu(window, mysettings, gameStarted);
    }
     return 0;
}
