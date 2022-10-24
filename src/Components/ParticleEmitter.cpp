/*
** EPITECH PROJECT, 2022
** EngineCoreSuper
** File description:
** ParticleEmitter
*/

#include "ParticleEmitter.hpp"

eng::ParticleEmitter::ParticleEmitter()
{
    setParticleTexture(eng::PARTICLE_TYPE::Pixel);
}

eng::ParticleEmitter::~ParticleEmitter()
{
}

void eng::ParticleEmitter::limitNumber()
{
    while (_particles.size() > _maxNumber)
        _particles.erase(_particles.begin());
}

void eng::ParticleEmitter::killOldparticles(float delta)
{
    for (auto it = _particles.begin(); it != _particles.end(); it++) {
        it->lifeTime += delta;
        if (it->lifeTime > _lifeTime)
            _particles.erase(it);
    }
}

void eng::ParticleEmitter::applyAcceleration(float delta)
{
    for (auto it = _particles.begin(); it != _particles.end(); it++)
        it->currentSpeed += (delta * _acceleration);
}

void eng::ParticleEmitter::applyTorque(float delta)
{
    for (auto it = _particles.begin(); it != _particles.end(); it++)
        it->sprite.setRotation(delta * _torque);
}

void eng::ParticleEmitter::emitParticle(float delta, float x, float y)
{
    _nextEmission -= delta;

    if (_nextEmission <= 0) {
        _particles.push_back(
            eng::SuperParticle(*_texture, _color, _baseSpeed, _baseRotation,
            x, y)
        );
        _nextEmission = _emissionRate;
    }
}

void eng::ParticleEmitter::updateParticles(float delta)
{
    applyAcceleration(delta);
    applyTorque(delta);
    auto it = _particles.begin();

    for (; it != _particles.end(); it++) {
        it->sprite.setRotation(it->currentRotation);
        it->sprite.setPosition(it->sprite.getPosition().x + it->currentSpeed, it->sprite.getPosition().y);
    }
}

void eng::ParticleEmitter::setParticleTexture(int type)
{
    if (eng::PARTICLE_TYPE::Pixel)
        _texture->create(0, 0);
}

void eng::ParticleEmitter::setParticleTexture(int type, std::string filepath)
{
    if (eng::PARTICLE_TYPE::Sprite)
        _texture->loadFromFile(filepath);
}

void eng::ParticleEmitter::setParticleColor(sf::Color color)
{
    this->_color = color;
}

void eng::ParticleEmitter::setParticleColor(int r, int g, int b, int a)
{
    this->_color = sf::Color(r, g, b, a);
}

std::vector<eng::SuperParticle> &eng::ParticleEmitter::getParticles()
{
    return this->_particles;
}