#ifndef Player_H
#define Player_H

#include <cstdint>
#include <SFML/Graphics.hpp>

class Player {
public:
    int x_pos = 0;
    int y_pos = 0;

    bool flag = false;
    bool visible = true;
    float size = 15.0;//diam
    uint8_t speed = 2;
    uint8_t score = 0;

    void set_position(int, int);
    void move(int, int);
    void update();

}; 

#endif // Player_H