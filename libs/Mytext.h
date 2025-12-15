#ifndef Mytext_H
#define Mytext_H

#include <cstdint>
#include <SFML/Graphics.hpp>
using namespace sf;

class MyText {
private:
    String text_;
    unsigned int size_;
    Font font_;
    Text sfText_;
    bool visible_;

public:
    // Конструктор
    MyText(const std::string& fontPath, const String& text = "", unsigned int size = 24);


    // Установка текста
    void setString(const String& text);
    void setSize(unsigned int size = 24);
    void setColor(Color color);

    // Установка позиции
    void setPosition(float x, float y);

    // Центрирование по рамке
    void center(const FloatRect& bounds);

    // Отрисовка
    void draw(sf::RenderWindow& window);

    // Установка видимости
    void setVisible(bool visible);
};

#endif // !Mytext_H