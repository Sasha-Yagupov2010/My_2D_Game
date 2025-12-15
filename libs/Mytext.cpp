#include "Mytext.h"


    // Конструктор
MyText::MyText(const std::string& fontPath, const String& text, unsigned int size)
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
    void MyText::setString(const String& text) {
        text_ = text;
        sfText_.setString(text_);
    }
    void MyText::setSize(unsigned int size) {
        sfText_.setCharacterSize(size_);
    }
    void MyText::setColor(Color color) {
        sfText_.setFillColor(color);
    }

    // Установка позиции
    void MyText::setPosition(float x, float y) {
        sfText_.setPosition(x, y);
    }

    // Центрирование по рамке
    void MyText::center(const FloatRect& bounds) {
        FloatRect textRect = sfText_.getLocalBounds();
        sfText_.setOrigin(textRect.left + textRect.width / 2.f,
            textRect.top + textRect.height / 2.f);
        sfText_.setPosition(bounds.left + bounds.width / 2.f,
            bounds.top + bounds.height / 2.f);
    }

    // Отрисовка
    void MyText::draw(sf::RenderWindow& window) {
        if (visible_) {
            window.draw(sfText_);
        }
    }

    // Установка видимости
    void MyText::setVisible(bool visible) {
        visible_ = visible;
    }
