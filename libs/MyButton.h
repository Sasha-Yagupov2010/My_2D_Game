#ifndef MyButton_H
#define MyButton_H

#include <cstdint>
#include <SFML/Graphics.hpp>
using namespace sf;


class MyButton {
private:
    String text_;
    unsigned int size_x;
    unsigned int size_y;
    bool visible_;
    RectangleShape butt;
    Color color;
    float xpos;
    float ypos;

public:
    MyButton(unsigned int size_x_, unsigned int size_y_, Color color_, float x, float y);

    void setVisible(bool);
    bool is_pressed(const RenderWindow&);
    bool in_focus(const RenderWindow&);
    void set_pos(float, float);

    RectangleShape get_shape() const {
        return butt;
    }

    void draw(RenderWindow& window);

}; 
#endif // !MyButton_H
