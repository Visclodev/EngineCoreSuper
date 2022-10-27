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
    _window.setFramerateLimit(60);
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
        it->sprite.setPosition(x, y);
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
            
            text._txt.setPosition(position.x, position.y);
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
}

void eng::GraphicSystems::clear(sf::Color c)
{
    _window.clear(c);
}
