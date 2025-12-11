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
    MyText(const std::string& fontPath, const String& text = "", unsigned int size = 24)
        : text_(text), size_(size), visible_(false) {
        if (!font_.loadFromFile(fontPath)) {
            // Обработка ошибки
            throw std::runtime_error("Failed to load font");
        }
        sfText_.setFont(font_);
        sfText_.setString(text_);
        sfText_.setCharacterSize(size_);
        sfText_.setFillColor(sf::Color::White);

    }

    // Установка текста
    void setString(const String& text) {
        text_ = text;
        sfText_.setString(text_);
    }

    void setColor(Color color) {
        sfText_.setFillColor(color);
    }

    // Установка позиции
    void setPosition(float x, float y) {
        sfText_.setPosition(x, y);
    }

    // Центрирование по рамке
    void center(const FloatRect& bounds) {
        FloatRect textRect = sfText_.getLocalBounds();
        sfText_.setOrigin(textRect.left + textRect.width / 2.f,
            textRect.top + textRect.height / 2.f);
        sfText_.setPosition(bounds.left + bounds.width / 2.f,
            bounds.top + bounds.height / 2.f);
    }

    // Отрисовка
    void draw(sf::RenderWindow& window) {
        if (visible_) {
            window.draw(sfText_);
        }
    }

    // Установка видимости
    void setVisible(bool visible) {
        visible_ = visible;
    }
};

#endif // !Mytext_H