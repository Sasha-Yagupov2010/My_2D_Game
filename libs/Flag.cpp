#include "Flag.h"

void Flag::set_position(int x, int y) {
    x_pos = x;
    y_pos = y;
}

void Flag::move(int x, int y) {
    x_pos += x;
    y_pos += y;
}

