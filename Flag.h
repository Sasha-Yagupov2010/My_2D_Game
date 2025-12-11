#ifndef Flag_H
#define Flag_H

#include <cstdint>
#include <SFML/Graphics.hpp>

class Flag {
public:
    int x_pos = 0;
    int y_pos = 0;

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
};

#endif // !Flag_H