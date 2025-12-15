#include "MyButton.h"


MyButton::MyButton(unsigned int size_x_, unsigned int size_y_, Color color_, float x, float y)
        : size_x(size_x_), size_y(size_y_), color(color_), xpos(x), ypos(y), visible_(true)
    {
        butt.setSize(Vector2f(size_x, size_y));
        butt.setFillColor(color);
        butt.setPosition(xpos, ypos);
    }
bool MyButton::in_focus(const RenderWindow& window) {
    Vector2i mousePos = Mouse::getPosition(window);
    Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    return butt.getGlobalBounds().contains(mousePosF);
}


void MyButton::setVisible(bool flag) { visible_ = flag; }

bool MyButton::is_pressed(const RenderWindow& window) {
        if (in_focus(window)) {
            if (Mouse::isButtonPressed(Mouse::Left)) {
                return true;
            }
        }
        return false;
    }



void MyButton::set_pos(float x, float y) {
        butt.setPosition(x, y);
        xpos = x;
        ypos = y;
    }



void MyButton::draw(RenderWindow& window) {
        if (visible_) {
            window.draw(butt);
        }
    }

