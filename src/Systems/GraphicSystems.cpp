/*
** EPITECH PROJECT, 2022
** EngineCoreSuper
** File description:
** GraphicSystems
*/

#include "GraphicSystems.hpp"

eng::GraphicSystems::GraphicSystems(int width, int height, std::string name):
_window(sf::VideoMode(width, height, 256), name), _clock(sf::Clock())
{
    if (!_window.isOpen()) {
        std::cerr << "error: window " << name << " hasn't opened" << std::endl;
        throw;
    }
    sf::Texture iconText;
    iconText.loadFromFile("../assets/logo.png");
    _window.setIcon(32, 32, iconText.copyToImage().getPixelsPtr());
}

eng::GraphicSystems::~GraphicSystems()
{
}

bool eng::GraphicSystems::isWindowOpen()
{
    return this->_window.isOpen();
}

void eng::GraphicSystems::display()
{
    _window.display();
    _delta = _clock.restart();
}

void eng::GraphicSystems::drawSystem(Registry &r)
{
    auto &positions = r.getComponents<Position>();
    auto &sprites = r.getComponents<Drawable>();

    for (int i = 0; i < sprites.size() && i < positions.size(); i++) {
        if (sprites[i].has_value() && positions[i].has_value()) {
            auto sprite = sprites[i].value();
            auto position = positions[i].value();
            
            sprite.sprite.setPosition(position.x, position.y);
            _window.draw(sprite.sprite);
        }
    }
}

void eng::GraphicSystems::writeSystem(Registry &r)
{
    auto &positions = r.getComponents<Position>();
    auto &texts = r.getComponents<Writable>();

    for (int i = 0; i < texts.size() && i < positions.size(); i++) {
        if (texts[i].has_value() && positions[i].has_value()) {
            auto text = texts[i].value();
            auto position = positions[i].value();
            
            text._txt.setPosition(position.x, position.y);
            _window.draw(text._txt);
        }
    }
}

sf::Time &eng::GraphicSystems::getDelta()
{
    return _delta;
}

sf::Clock &eng::GraphicSystems::getClock()
{
    return _clock;
}

sf::RenderWindow &eng::GraphicSystems::getRenderWindow()
{
    return _window;
}

void eng::GraphicSystems::setFrameRateLimit(unsigned int limit)
{
    _window.setFramerateLimit(limit);
}

void eng::GraphicSystems::clear(sf::Color c)
{
    _window.clear(c);
}