#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <Windows.h>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace sf;
using namespace chrono;


#include "libs/Settings.h"
#include "libs/Player.h"
#include "libs/Mytext.h"
#include "libs/MyButton.h"
#include "libs/GameMap.h"
#include "libs/Flag.h"
#include "libs/ShootGun.h"
#include "libs/PlayerBoost.h"

vector<string> getMapFiles(const string& directoryPath, const string& extension = ".map") {
    vector<string> maps;

    string searchPath = directoryPath + "\\*" + extension;

    WIN32_FIND_DATAA findData;
    HANDLE hFind = FindFirstFileA(searchPath.c_str(), &findData);

    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            // Проверяем, не директория ли это
            if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                string filename = findData.cFileName;
                maps.push_back(filename);
            }
        } while (FindNextFileA(hFind, &findData) != 0);

        FindClose(hFind);
    }

    // Сортируем по алфавиту
    sort(maps.begin(), maps.end());

    return maps;
}


string selectMapMenu(RenderWindow& window, Settings& mysettings){

    MyText menu_text("myfonts/arial_bolditalicmt.ttf", "Select map", 72);
    menu_text.setVisible(true);
    menu_text.setColor(Color::White);
    menu_text.setPosition((mysettings.width - 400) / 2, mysettings.height * 0.1);

    MyText maps_list("myfonts/arialmt.ttf", "");
    maps_list.setVisible(true);
    maps_list.setColor(Color::White);
    maps_list.setPosition((mysettings.width - 200) / 2, mysettings.height * 0.3);

    MyText selected_map("myfonts/arialmt.ttf", "",28);
    selected_map.setVisible(true);
    selected_map.setColor(Color::White);
    selected_map.setPosition((mysettings.width - 200) / 2, mysettings.height * 0.7);

    string list = "";
    vector <string> maps = getMapFiles("maps",".txt");
    for (auto i :maps) {
        list += i += "\n";
    }
    cout << list;
    maps_list.setString(list);
    
    
    bool runWhile = 1;

    string out="fastrunner.txt";//default
    int index = 0;
    Event event;
    while (runWhile) {


        while (window.pollEvent(event)){ if(event.type == Event::Closed) window.close(); }

        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            index--;
            while (Keyboard::isKeyPressed(Keyboard::Up));
        }

        if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            index++;
            while (Keyboard::isKeyPressed(Keyboard::Down));
        }

        if (index < 0) index = 0;
        if (index > maps.size()-1)index = maps.size()-1;
        out = maps[index];

        if (Keyboard::isKeyPressed(Keyboard::Enter)) 
            runWhile = 0;

        selected_map.setString(out);
        window.clear();
        maps_list.draw(window);
        menu_text.draw(window);
        selected_map.draw(window);
        window.display();
    }
    return out;
}

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

void run_shoots_logic(ShootGun& gun, RenderWindow& window, CircleShape& gun_circle, int shoot_speed) {
    if (gun.visible)
    {
        gun.step(shoot_speed);
        gun_circle.setPosition(gun.startX, gun.startY);
        window.draw(gun_circle);

        if (gun.startX == gun.targetX and gun.startY == gun.targetY) { gun.visible = false; }
    }
}

float calc_distance(float x1, float x2, float y1, float y2) {
    float dx = x1 - x2;
    float dy = y1 - y2;
    return sqrt(dx * dx + dy * dy);
}

int calc_text_size(string text, int size) { return text.length()* size/2; }
int calc_text_size(string text) { return 200; }

void winPlayerScreen(string winner, RenderWindow& window, Settings& mysettings)
{
    MyText winneris("myfonts/arial_bolditalicmt.ttf", "Winner is:", 72);
    winneris.setVisible(true);
    winneris.setColor(Color::White);
    winneris.setPosition(
        (mysettings.width/2) - calc_text_size("Winner is:") ,
        mysettings.height*0.2);

    MyText win("myfonts/arialmt.ttf", winner, 28);
    win.setVisible(true);
    win.setColor(Color::White);
    win.setPosition(
        (mysettings.width) * 0.5 - calc_text_size(winner, 28),
        mysettings.height * 0.5);

    MyText comment("myfonts/arialmt.ttf", "press space to continue", 28);
    comment.setVisible(true);
    comment.setColor(Color::White);
    comment.setPosition(
        (mysettings.width*0.4) - calc_text_size("press space to continue", 28),
        mysettings.height * 0.9);

    window.clear();
    winneris.draw(window);
    win.draw(window);
    comment.draw(window);
    window.display();

    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) break;
        if (event.type == Event::Closed) window.close();
    }

}//    winPlayerScreen("fist", window, mysettings);

void splitGame(RenderWindow& window, Settings& mysettings) {
    //для каждой игры свой игрок и 
    uint8_t mindist_to_flag = mysettings.minDistToFlag;

    Player player;
    Flag flag;

    Player enemy;
    Flag enemyflag;

    PlayerBoost firstBoost;
    PlayerBoost enemyBoost;

    uint16_t percent_of_resizing = (mysettings.height / 400 * 100);


    float teamOneBaseX = 0;
    float teamOneBaseY = mysettings.height / 2;

    float teamTwoBaseX = mysettings.width;
    float teamTwoBaseY = mysettings.height / 2;

    int  max_score_for_win = mysettings.scoreForWin;

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
    score2_text.setPosition((mysettings.width - 200)*0.85, 0);

    MyText score2_value("myfonts/arialmt.ttf", "0", 24);
    score2_value.setVisible(true);
    score2_value.setColor(Color::Blue);
    score2_value.setPosition((mysettings.width - 200) * 0.85+100, 0);

    MyText player_Boost_table("myfonts/arialmt.ttf", "", 24);
    player_Boost_table.setVisible(true);
    player_Boost_table.setColor(Color::Red);
    player_Boost_table.setPosition((mysettings.width - 200) * 0.1 + 150, 0);

    MyText enemy_Boost_table("myfonts/arialmt.ttf", "", 24);
    enemy_Boost_table.setVisible(true);
    enemy_Boost_table.setColor(Color::Blue);
    enemy_Boost_table.setPosition((mysettings.width - 200) * 0.85 + 150, 0);
    

    /*===== пули =====*/
    const uint8_t shoot_speed = 4;
    const uint8_t shoot_ball_size = percent_of_resizing * 5 / 100;

    //первая
    ShootGun gun1(15, 15);
    gun1.setPos(player.x_pos, player.y_pos);
    gun1.visible = false;
    gun1.resetTarget();

    CircleShape gun1_circle(shoot_ball_size);
    gun1_circle.setFillColor(Color::White);


    //вторая
    ShootGun gun2(15, 15);
    gun2.setPos(enemy.x_pos, enemy.y_pos);
    gun2.visible = false;
    gun2.resetTarget();

    CircleShape gun2_circle(shoot_ball_size);
    gun2_circle.setFillColor(Color::White);
    /*===== пули =====*/

    string mapname = selectMapMenu(window, mysettings);
    string map_path = "maps/" + mapname;
                                                                        // Автоматический расчет размера тайлов относительно экрана
    const int mapWidthTiles = 24;                                       // количество тайлов по ширине
    const int mapHeightTiles = 16;                                      // количество тайлов по высоте
    int tileSize = min(mysettings.width / mapWidthTiles, mysettings.height / mapHeightTiles);

    GameMap gameMap(mapWidthTiles, mapHeightTiles, tileSize);           //поле

    if (!gameMap.loadFromFile(map_path, Color::White)) {
        cout << "error: map not loaded!" << endl;
    }

    bool gameRun = true;
    uint8_t speed = player.speed;   //для сброса

    /*=== таймеры ===*/
    const uint8_t resetMIN_const = 3;
    auto resetMIN = chrono::seconds(resetMIN_const);
    auto now = steady_clock::now();
    steady_clock::time_point resetFirst;
    steady_clock::time_point resetEnemy;

    resetFirst = now - resetMIN;;
    resetEnemy = now - resetMIN;;

    while (gameRun)
    {
        now = steady_clock::now();

        // Сохраняем старую позицию для отката при коллизии
        float oldX = player.x_pos;
        float oldY = player.y_pos;

        float oldX2 = enemy.x_pos;
        float oldY2 = enemy.y_pos;

        /* =================== движение 1 ===================*/
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            player.move(-player.speed, 0);
            player_circle.move(-player.speed, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            player.move(player.speed, 0);
            player_circle.move(player.speed, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::W)) {
            player.move(0, -player.speed);
            player_circle.move(0, -player.speed);
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            player.move(0, player.speed);
            player_circle.move(0, player.speed);
        }
        /* =================== движение 1 ===================*/


        /* =================== движение 2 ===================*/
        if (Keyboard::isKeyPressed(Keyboard::J)) {
            enemy.move(-enemy.speed, 0);
            enemy_circle.move(-enemy.speed, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::L)) {
            enemy.move(enemy.speed, 0);
            enemy_circle.move(enemy.speed, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::I)) {
            enemy.move(0, -enemy.speed);
            enemy_circle.move(0, -enemy.speed);
        }
        if (Keyboard::isKeyPressed(Keyboard::K)) {
            enemy.move(0, enemy.speed);
            enemy_circle.move(0, enemy.speed);
        }
        /* =================== движение 2 ===================*/


        /* ============ захват ============*/
        int distance;
        if (Keyboard::isKeyPressed(Keyboard::E)) {
            distance = calc_distance(enemyflag.x_pos, player.x_pos, enemyflag.y_pos, player.y_pos);
            player.flag = (distance < mindist_to_flag);
        }

        if (Keyboard::isKeyPressed(Keyboard::O)) {
            distance = calc_distance(flag.x_pos, enemy.x_pos, flag.y_pos, enemy.y_pos);
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


            /*============ пуля попала ============*/
        if (gun1.checkDestroy(enemy.x_pos, enemy.y_pos, enemy.size))
        {
            if ((now - resetEnemy > resetMIN) and !enemyBoost.god) {            //убить не всегда можно
                resetEnemy = now;
                enemy.set_position(teamTwoBaseX - enemy.size, teamTwoBaseY);        // Сброс врага 
                enemy.flag = false;
                enemy_circle.setPosition(teamTwoBaseX - enemy.size, teamTwoBaseY);
                flag.set_position(teamOneBaseX, teamOneBaseY);                      // Сброс флага врага (если он его нес)
                flag_circle.setPosition(teamOneBaseX, teamOneBaseY);                // Пополнение патронов игроку (награда за попадание)
                gun2.count = gun2.max_count;
            }
                                                                                    // Игрок пополнил патроны
        }
        

        
        if (gun2.checkDestroy(player.x_pos, player.y_pos, player.size))
        {
            if ((now - resetFirst > resetMIN) and !firstBoost.god) {
                resetFirst = now;
                player.set_position(teamOneBaseX, teamOneBaseY);                    // Сброс игрока
                player.flag = false;
                player_circle.setPosition(teamOneBaseX, teamOneBaseY);
                enemyflag.set_position(teamTwoBaseX - enemyflag.size, teamTwoBaseY);// Сброс флага игрока (если он его нес)
                enemyflag_circle.setPosition(teamTwoBaseX - enemyflag.size, teamTwoBaseY);
                gun1.count = gun1.max_count;
            }
                                       // Враг пополнил патроны
        }
        /*============ пуля попала ============*/


        /* ============ Проверяем коллизии ============*/
        if (gameMap.checkCollision(player.x_pos, player.y_pos, player.size) ||
            player.x_pos < 0 || player.x_pos > mysettings.width - player.size ||
            player.y_pos < 0 || player.y_pos > mysettings.height - player.size){
            
                player.set_position(oldX, oldY);                                // Откатываем позицию
                player_circle.setPosition(oldX, oldY);
            }

        if (gameMap.checkCollision(enemy.x_pos, enemy.y_pos, enemy.size) ||
            enemy.x_pos < 0 || enemy.x_pos > mysettings.width - enemy.size ||
            enemy.y_pos < 0 || enemy.y_pos > mysettings.height - enemy.size){

                enemy.set_position(oldX2, oldY2);                               // Откатываем позицию
                enemy_circle.setPosition(oldX2, oldY2);
            }


        if (gameMap.checkCollision(gun1.startX, gun1.startY, shoot_ball_size)) {
            gun1.visible = false;
        }

        if (gameMap.checkCollision(gun2.startX, gun2.startY, shoot_ball_size)) {
            gun2.visible = false;
        }
        /* ============ Проверяем коллизии ============*/

        /*============= супер способности =============*/
        enemyBoost.activateRandomEffect();
        firstBoost.activateRandomEffect();

        firstBoost.updateEffects();
        enemyBoost.updateEffects();

        if (enemyBoost.superSpeed) {
            enemy.speed = 2 * speed;
        }
        else enemy.speed = speed;

        if (firstBoost.superSpeed) {
            player.speed = 2 * speed;
        }
        else player.speed = speed;

        //cout << firstBoost.god << firstBoost.shield << firstBoost.superSpeed << endl;
        //cout << enemyBoost.god << enemyBoost.shield << enemyBoost.superSpeed << endl;
        
        
        /*============= супер способности =============*/

        //выходим в меню
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            player.set_position(0, 0);
            enemy.set_position(0, 0);
            gameRun = false;
        }

        //флаг тащим
        if (player.flag and !enemyBoost.shield) {
            enemyflag.set_position(player.x_pos, player.y_pos);
            enemyflag_circle.setPosition(player.x_pos, player.y_pos);
        }

        if (enemy.flag and !firstBoost.shield) {
            flag.set_position(enemy.x_pos, enemy.y_pos);
            flag_circle.setPosition(enemy.x_pos, enemy.y_pos);
        }

        
        distance = calc_distance(enemyflag.x_pos, teamOneBaseX, enemyflag.y_pos, teamOneBaseY);
        if (distance < mindist_to_flag) {
            enemyflag.set_position(teamTwoBaseX - enemyflag.size, teamTwoBaseY);
            enemyflag_circle.setPosition(teamTwoBaseX - enemyflag.size, teamTwoBaseY);

            player.score += 1;
            player.flag = false;
        }

        
        distance = calc_distance(flag.x_pos, teamTwoBaseX, flag.y_pos, teamTwoBaseY);
        if (distance < mindist_to_flag+flag.size) {
            flag.set_position(teamOneBaseX, teamOneBaseY);
            flag_circle.setPosition(teamOneBaseX, teamOneBaseY);

            enemy.score += 1;
            enemy.flag = false;
        }

        player_Boost_table.setString(firstBoost.UI_active_mode());
        enemy_Boost_table.setString(enemyBoost.UI_active_mode());


        /* победа и очки */
        if (player.score >= max_score_for_win) { winPlayerScreen("PLAYER 1", window, mysettings); gameRun = false; }
        if (enemy.score >= max_score_for_win) { winPlayerScreen("PLAYER 2", window, mysettings); gameRun = false; }

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

        player_Boost_table.draw(window);
        enemy_Boost_table.draw(window);
        

        //пули, обработка
        run_shoots_logic(gun1, window, gun1_circle, shoot_speed);
        run_shoots_logic(gun2, window, gun2_circle, shoot_speed);

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
            int distance = calc_distance(enemyflag.x_pos, player.x_pos, enemyflag.y_pos, player.y_pos);

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

        int distance = calc_distance(enemyflag.x_pos, teamOneBaseX, enemyflag.y_pos, teamOneBaseY);
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
        switch (gameStarted)
        {
        case(1):
            singleGame(window, mysettings);
            gameStarted = 0;
            break;

        case(2):
            splitGame(window, mysettings);
            gameStarted = 0;
            break;

        default:
            break;
        }

        menu(window, mysettings, gameStarted);
    }
     return 0;
}
