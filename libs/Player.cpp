#include "Player.h"

void Player::set_position(int x, int y) {
    x_pos = x;
    y_pos = y;
}

void Player::move(int x, int y) {
    x_pos += x;
    y_pos += y;
}

