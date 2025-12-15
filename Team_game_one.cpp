#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <string>
#include <Windows.h>

using namespace std;
using namespace sf;

#include "libs/Settings.h"
#include "libs/Player.h"
#include "libs/Mytext.h"
#include "libs/MyButton.h"
#include "libs/GameMap.h"
#include "libs/Flag.h"
#include "libs/ShootGun.h"


void menu(RenderWindow& window, Settings& mysettings, int& gameStarted)
{
    //кнопочки
    MyButton play_button(200, 50, Color::White, (mysettings.width - 200)/2, (mysettings.height - 50) * 0.3);
    play_button.setVisible(true);

    MyButton split_play(200, 50, Color::White, (mysettings.width - 200)/2, (mysettings.height - 50) * 0.425);
    split_play.setVisible(true);

    MyButton exit_button(200, 50, Color::White, (mysettings.width - 200) / 2, (mysettings.height - 50) * 0.550);
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

    MyText splitplay_text("myfonts/arialmt.ttf", "Split");
    splitplay_text.setVisible(true);
    splitplay_text.setColor(Color::Black);
    splitplay_text.center(split_play.get_shape().getGlobalBounds());


    MyText exit_text("myfonts/arialmt.ttf", "Exit");
    exit_text.setVisible(true);
    exit_text.setColor(Color::Black);
    exit_text.center(exit_button.get_shape().getGlobalBounds());


    window.clear();
    play_button.draw(window);
    split_play.draw(window);
    exit_button.draw(window);

    menu_text.draw(window);
    play_text.draw(window);
    exit_text.draw(window);
    splitplay_text.draw(window);

    window.display();

    if (play_button.is_pressed(window)) { gameStarted = 1; }
    if (split_play.is_pressed(window)) { gameStarted = 2; }
    if (exit_button.is_pressed(window)) { window.close(); }

}
void splitGame(RenderWindow& window, Settings& mysettings) {
    //для каждой игры свой игрок и 
    const uint8_t mindist_to_flag = 12;

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
    player.size = percent_of_resizing * player.size / 100;
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
    flag_circle.setOutlineThickness(flag.size / 7);
    /*=========================================================*/

    /*============================ второстепенный игрок =============================*/
    // игрок
    enemy.size = percent_of_resizing * enemy.size / 100;
    enemy.speed = percent_of_resizing * enemy.speed / 100;
    //float size = player.size; 

    CircleShape enemy_circle(enemy.size / 2);
    enemy.set_position(teamTwoBaseX - enemy.size, teamTwoBaseY);

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

    //текстовые блоки
    MyText score1_text("myfonts/arial_bolditalicmt.ttf", "Score:", 28);
    score1_text.setVisible(true);
    score1_text.setColor(Color::Red);
    score1_text.setPosition((mysettings.width - 200) * 0.1, 0);

    MyText score1_value("myfonts/arialmt.ttf", "0", 24);
    score1_value.setVisible(true);
    score1_value.setColor(Color::Red);
    score1_value.setPosition((mysettings.width - 200) * 0.1 + 100, 0);

    MyText score2_text("myfonts/arial_bolditalicmt.ttf", "Score:", 28);
    score2_text.setVisible(true);
    score2_text.setColor(Color::Blue);
    score2_text.setPosition((mysettings.width - 200)*0.9, 0);

    MyText score2_value("myfonts/arialmt.ttf", "0", 24);
    score2_value.setVisible(true);
    score2_value.setColor(Color::Blue);
    score2_value.setPosition((mysettings.width - 200) * 0.9+100, 0);

    /*===== пули =====*/
    const uint8_t shoot_speed = 4;

    ShootGun gun1(15, 15);
    gun1.setPos(player.x_pos, player.y_pos);
    gun1.visible = false;
    gun1.resetTarget();

    CircleShape gun1_circle(percent_of_resizing * 5 / 100);
    gun1_circle.setFillColor(Color::White);



    ShootGun gun2(15, 15);
    gun2.setPos(enemy.x_pos, enemy.y_pos);
    gun2.visible = false;
    gun2.resetTarget();

    CircleShape gun2_circle(percent_of_resizing * 5 / 100);
    gun2_circle.setFillColor(Color::White);
    /*===== пули =====*/


    // Автоматический расчет размера тайлов относительно экрана
    const int mapWidthTiles = 24;   // количество тайлов по ширине
    const int mapHeightTiles = 16;  // количество тайлов по высоте
    int tileSize = min(mysettings.width / mapWidthTiles, mysettings.height / mapHeightTiles);

    GameMap gameMap(mapWidthTiles, mapHeightTiles, tileSize);

    if (!gameMap.loadFromFile("maps/fastrunner.txt", Color::White)) {
        cout << "error: map not loaded!" << endl;
    }

    bool gameRun = true;
    uint8_t speed = player.speed;


    while (gameRun)
    {
        // Сохраняем старую позицию для отката при коллизии
        float oldX = player.x_pos;
        float oldY = player.y_pos;

        float oldX2 = enemy.x_pos;
        float oldY2 = enemy.y_pos;

        /* =================== движение ===================*/
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            player.move(-speed, 0);
            player_circle.move(-speed, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            player.move(speed, 0);
            player_circle.move(speed, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::W)) {
            player.move(0, -speed);
            player_circle.move(0, -speed);
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            player.move(0, speed);
            player_circle.move(0, speed);
        }
        /* =================== движение ===================*/

        /* =================== движение ===================*/
        if (Keyboard::isKeyPressed(Keyboard::J)) {
            enemy.move(-speed, 0);
            enemy_circle.move(-speed, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::L)) {
            enemy.move(speed, 0);
            enemy_circle.move(speed, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::I)) {
            enemy.move(0, -speed);
            enemy_circle.move(0, -speed);
        }
        if (Keyboard::isKeyPressed(Keyboard::K)) {
            enemy.move(0, speed);
            enemy_circle.move(0, speed);
        }
        /* =================== движение ===================*/

        /* ============ захват ============*/
        int distance;
        if (Keyboard::isKeyPressed(Keyboard::E)) {
            distance = sqrt(pow((enemyflag.x_pos - player.x_pos), 2) + pow((enemyflag.y_pos - player.y_pos), 2));
            //cout << distance << endl;
            player.flag = (distance < mindist_to_flag);
        }

        if (Keyboard::isKeyPressed(Keyboard::O)) {
            distance = sqrt(pow((flag.x_pos - enemy.x_pos), 2) + pow((flag.y_pos - enemy.y_pos), 2));
            //cout << distance << endl;
            enemy.flag = (distance < mindist_to_flag);
        }
        /* ============ захват ============*/

        /* ============ стрельба ============*/
        if (Keyboard::isKeyPressed(Keyboard::Q)) {
            if(gun1.count and !gun1.visible)
            {
                gun1.setPos(player.x_pos, player.y_pos);
                gun1.visible = true;
                gun1.setTarget(enemy.x_pos, enemy.y_pos);
                gun1.count -= 1;
            }
        
        }

        
        if (Keyboard::isKeyPressed(Keyboard::U)) {
            if (gun2.count and !gun2.visible)
            {
                gun2.setPos(enemy.x_pos, enemy.y_pos);
                gun2.visible = true;
                gun2.setTarget(player.x_pos, player.y_pos);
                gun2.count -= 1;
            }

        }
        
        /* ============ стрельба ============*/



        /* ============ Проверяем коллизии ============*/
        if (gameMap.checkCollision(player.x_pos, player.y_pos, player.size) ||
            player.x_pos < 0 || player.x_pos > mysettings.width - player.size ||
            player.y_pos < 0 || player.y_pos > mysettings.height - player.size) {

            // Откатываем позицию
            player.set_position(oldX, oldY);
            player_circle.setPosition(oldX, oldY);
        }

        if (gameMap.checkCollision(enemy.x_pos, enemy.y_pos, enemy.size) ||
            enemy.x_pos < 0 || enemy.x_pos > mysettings.width - enemy.size ||
            enemy.y_pos < 0 || enemy.y_pos > mysettings.height - enemy.size) {

            // Откатываем позицию
            enemy.set_position(oldX2, oldY2);
            enemy_circle.setPosition(oldX2, oldY2);
        }
        /* ============ Проверяем коллизии ============*/


        //exit to menu
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            player.set_position(0, 0);
            gameRun = false;
        }

        //move flag
        if (player.flag) {
            enemyflag.set_position(player.x_pos, player.y_pos);
            enemyflag_circle.setPosition(player.x_pos, player.y_pos);
        }

        if (enemy.flag) {
            flag.set_position(enemy.x_pos, enemy.y_pos);
            flag_circle.setPosition(enemy.x_pos, enemy.y_pos);
        }

        distance = sqrt(pow((enemyflag.x_pos - teamOneBaseX), 2) + pow((enemyflag.y_pos - teamOneBaseY), 2));
        if (distance < mindist_to_flag) {
            enemyflag.set_position(teamTwoBaseX - enemyflag.size, teamTwoBaseY);
            enemyflag_circle.setPosition(teamTwoBaseX - enemyflag.size, teamTwoBaseY);

            player.score += 1;
            player.flag = false;
        }

        distance = sqrt(pow((flag.x_pos - teamTwoBaseX), 2) + pow((flag.y_pos - teamTwoBaseY), 2));
        //cout << distance<<endl;
        if (distance < mindist_to_flag+flag.size) {
            flag.set_position(teamOneBaseX, teamOneBaseY);
            flag_circle.setPosition(teamOneBaseX, teamOneBaseY);

            enemy.score += 1;
            enemy.flag = false;
        }


        window.clear();


        gameMap.draw(window);
        window.draw(player_circle);
        window.draw(flag_circle);

        window.draw(enemy_circle);
        window.draw(enemyflag_circle);
        

        score1_text.draw(window);
        score1_value.setString(to_string(player.score));
        score1_value.draw(window);

        score2_text.draw(window);
        score2_value.setString(to_string(enemy.score));
        score2_value.draw(window);
        //cout << gun1.startX << gun1.startY << gun1.targetX << gun1.targetY << endl<<gun1.count<<endl;

        //пули, обработка
        if (gun1.visible) 
        {
            gun1.step(shoot_speed);
            gun1_circle.setPosition(gun1.startX, gun1.startY);
            window.draw(gun1_circle); 

            if (gun1.startX == gun1.targetX and gun1.startY == gun1.targetY) { gun1.visible = false; }
        }

        if (gun2.visible)
        {
            gun2.step(shoot_speed);
            gun2_circle.setPosition(gun2.startX, gun2.startY);
            window.draw(gun2_circle);

            if (gun2.startX == gun2.targetX and gun2.startY == gun2.targetY) { gun2.visible = false; }
        }

        window.display();
    }
}

void singleGame(RenderWindow& window, Settings& mysettings) {
    //для каждой игры свой игрок и 
    const uint8_t mindist_to_flag = 12;

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

    //текстовые блоки
    MyText score1_text("myfonts/arial_bolditalicmt.ttf", "Score:", 28);
    score1_text.setVisible(true);
    score1_text.setColor(Color::Red);
    score1_text.setPosition((mysettings.width - 200)*0.1, 0);

    MyText score1_value("myfonts/arialmt.ttf","0",24);
    score1_value.setVisible(true);
    score1_value.setColor(Color::Red);
    score1_value.setPosition((mysettings.width - 200)*0.1 + 100, 0);



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
        window.draw(enemy_circle);

        window.draw(enemyflag_circle);
        window.draw(flag_circle);

        score1_text.draw(window);
        score1_value.setString(to_string(player.score));
        score1_value.draw(window);


        window.display();
    }
}

int main()
{
    /* настройки проекта */

    SetConsoleCP(1251);       // Установить кодовую страницу ввода
    SetConsoleOutputCP(1251); // Установить кодовую страницу вывода

    Settings mysettings;
    mysettings.height = 800;
    mysettings.width = 1200;
    mysettings.fps = 60;



    RenderWindow window( VideoMode(mysettings.width, mysettings.height), L"Game",  Style::Default);

    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(mysettings.fps);
    /* =============================== */
  

    int gameStarted = 0;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        //menu
        if (gameStarted==1) {
            singleGame(window, mysettings); 
            gameStarted = false;
        }
        if (gameStarted == 2) {
            splitGame(window, mysettings);
            gameStarted = false;
        }
        menu(window, mysettings, gameStarted);
    }
     return 0;
}
