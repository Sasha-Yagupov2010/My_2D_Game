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
   

    void set_position(int, int);
    void move(int, int);
};

#endif // !Flag_H