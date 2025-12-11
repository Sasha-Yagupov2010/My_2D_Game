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

    void set_position(int x, int y) {
        x_pos = x;
        y_pos = y;
    }

    void move(int x, int y) {
        x_pos += x;
        y_pos += y;
    }

    void update() {
        if (!visible) { visible = true; }
        // код обновления
    }
}; 

#endif // Player_H