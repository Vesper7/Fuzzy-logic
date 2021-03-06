#pragma once
#include "SFML\Graphics.hpp"
#include "FuzzyVariable.h"
#include "Range.h"

class Axis {
public:
    Axis() {}
    Axis(sf::Vector2f size, sf::Vector2f position, Range range) {
        _size = size;
        _position = position;
        _range = range;
        setHorizontalAxis();
        setGraduation();
        setVerticalAxis();
    }
    void setRange(Range range) {
        _range = range;
    }
    float getX(float pointX) {
        return pointX*_pixelSpace + vertical.getPosition().x;
    }
    float getY(float pointY) {
        return horizontal.getPosition().y - pointY*_size.y;
    }
    void draw(sf::RenderWindow& window) {
        window.draw(vertical);
        window.draw(horizontal);
        for (auto& x : _graduations)
            window.draw(x);
    }
    float getPixelSpace() {
        return _pixelSpace;
    }
    float getZeroX() {
        return vertical.getPosition().x;
    }
private:

    sf::RectangleShape horizontal, vertical;
    std::vector<sf::RectangleShape> _graduations;
    sf::Vector2f _size;
    sf::Vector2f _position;
    Range _range;
    float _pixelSpace;

    void setGraduation()
    {
        float ratio = _size.x / _range.getElementsNum();
        if (ratio >= 5) {
            _pixelSpace = ratio;
        }
        for (auto i = _position.x; i <= _size.x; i += _pixelSpace) {
            _graduations.push_back(sf::RectangleShape({ 1, 10 }));
            _graduations.back().setPosition(i, _position.y - 5);
            _graduations.back().setFillColor(sf::Color(185, 185, 185, 255));
        }
    }
    void setHorizontalAxis() {
        horizontal = sf::RectangleShape({ _size.x, 1 });
        horizontal.setPosition(_position);
        horizontal.setFillColor(sf::Color::Black);
    }
    void setVerticalAxis()
    {
        vertical = sf::RectangleShape({ 1, _size.y });
        vertical.setFillColor(sf::Color::Black);
        if (_range.getUpper() >= 0)
            for (int i = _range.getLower(), j = 0; i < _range.getUpper(); i ++, ++j) 
                if (i == 0) {
                    vertical.setPosition(_graduations[j].getPosition().x, 100);
                    break;
                }
    }
};