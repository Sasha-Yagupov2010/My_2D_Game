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

    int set_position(int x, int y) {
        x_pos = x;
        y_pos = y;
    }

    void update() {
        if (!visible) { visible = true; }
        // код обновления
    }
}; 

#endif // Player_H