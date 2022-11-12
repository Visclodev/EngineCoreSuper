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
    //sf::Texture iconText;
    //iconText.loadFromFile("../assets/logo.png");
    //_window.setIcon(32, 32, iconText.copyToImage().getPixelsPtr());
    unsigned int fps = 60;
    _window.setFramerateLimit(fps);
    _frameRateLimit = fps;
    _delta = sf::Time::Zero;
    _deltaSeconds = 0;
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
    _deltaSeconds = _delta.asSeconds();
}

void eng::GraphicSystems::drawSystem(Registry &r)
{
    auto &positions = r.getComponents<Position>();
    auto &sprites = r.getComponents<Drawable>();

    for (int i = 0; i < sprites.size() && i < positions.size(); i++) {
        if (sprites[i].has_value() && positions[i].has_value()) {
            auto &sprite = sprites[i].value();
            auto &position = positions[i].value();
            
            sprite.sprite.setPosition(position.x, position.y);
            sprite.sprite.setRotation(position.rotation);
            _window.draw(sprite.sprite);
        }
    }
}


void eng::GraphicSystems::particleSystem(eng::Registry &r)
{
    auto &poss = r.getComponents<Position>();
    auto &partEmitters = r.getComponents<ParticleEmitter>();

    for (int i = 0; i < poss.size() && i < partEmitters.size(); i++) {
        if (poss[i].has_value() && partEmitters[i].has_value()) {
            auto &pos = poss[i].value();
            auto &prt = partEmitters[i].value();
            auto delta = _delta.asSeconds();

            prt.emitParticle(delta, pos.x, pos.y);
            prt.killOldparticles(delta);
            prt.limitNumber();
            prt.updateParticles(delta);
            prt.applyTorque(delta);
            prt.applyAcceleration(delta);
            if (prt.isLocal)
                _displayParticleVector(prt.getParticles(), pos.x, pos.y);
            else
                _displayParticleVector(prt.getParticles());
        }
    }
}

// global (position of each particle is independant)
void eng::GraphicSystems::_displayParticleVector(
std::vector<eng::SuperParticle> particles)
{
    auto it = particles.begin();

    for (; it != particles.end(); it++)
        _window.draw(it->sprite);
}

// local (position of each particle is dependant of the emitters point)
void eng::GraphicSystems::_displayParticleVector(
std::vector<eng::SuperParticle> particles, float x, float y)
{
    auto it = particles.begin();

    for (; it != particles.end(); it++) {
        float new_x = (x + it->sprite.getPosition().x);
        float new_y = (y + it->sprite.getPosition().y);
        it->sprite.setPosition(new_x, new_y);
        _window.draw(it->sprite);
    }
}

void eng::GraphicSystems::writeSystem(Registry &r)
{
    auto &positions = r.getComponents<Position>();
    auto &texts = r.getComponents<Writable>();

    for (int i = 0; i < texts.size() && i < positions.size(); i++) {
        if (texts[i].has_value() && positions[i].has_value()) {
            auto &text = texts[i].value();
            auto &position = positions[i].value();

            text._txt.setPosition(position.x + text._xOffset, position.y + text._yOffset);
            text._txt.setRotation(position.rotation);
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
    _frameRateLimit = limit;
}

unsigned int eng::GraphicSystems::getFrameRateLimit()
{
    return _frameRateLimit;
}

void eng::GraphicSystems::clear(sf::Color c)
{
    _window.clear(c);
}

void eng::GraphicSystems::animateSystem(Registry &r)
{
    auto &sprites = r.getComponents<eng::Drawable>();

    for (int i = 0; i < sprites.size(); i++) {
        auto &spr = sprites[i];
        
        if (spr.has_value() && spr.value().frameTime != -1) {
            sf::IntRect rect = spr.value().sprite.getTextureRect();
            if (spr.value().sheetDirection != 0) {
                spr.value().nextFrame -= _delta.asSeconds();
            }
            // Animate to the right
            if (spr.value().sheetDirection == 1 && spr.value().nextFrame <= 0) {
                rect.left += rect.width;
                if (rect.left >= spr.value().sizeX)
                    rect.left = 0;
                spr.value().nextFrame = spr.value().frameTime;
            }
            // Animate to the left
            if (spr.value().sheetDirection == 2 && spr.value().nextFrame <= 0) {
                rect.left -= rect.width;
                if (rect.left < 0)
                    rect.left = spr.value().sizeX;
                spr.value().nextFrame = spr.value().frameTime;
            }
            // Animate downward
            if (spr.value().sheetDirection == 3 && spr.value().nextFrame <= 0) {
                rect.top += rect.height;
                if (rect.top >= spr.value().sizeY)
                    rect.top = 0;
                spr.value().nextFrame = spr.value().frameTime;
            }
            // Animate upward
            if (spr.value().sheetDirection == 4 && spr.value().nextFrame <= 0) {
                rect.top -= rect.height;
                if (rect.top < 0)
                    rect.top = spr.value().sizeY;
                spr.value().nextFrame = spr.value().frameTime;
            }
            spr.value().sprite.setTextureRect(rect);
        }
    }
}

void eng::GraphicSystems::eventCatchWindow()
{
    while (this->_window.pollEvent(this->_event)) {
        if (this->_event.type == sf::Event::Closed)
            this->_window.close();
        if (this->_event.type == sf::Event::GainedFocus)
            this->_isWindowFocused = true;
        if (this->_event.type == sf::Event::LostFocus)
            this->_isWindowFocused = false;
    }
}

bool &eng::GraphicSystems::isWindowFocused()
{
    return _isWindowFocused;
}

void eng::GraphicSystems::closeWindow()
{
    this->_window.close();
}

float &eng::GraphicSystems::getDeltaSeconds()
{
    return _deltaSeconds;
}