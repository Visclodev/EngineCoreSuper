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

static float basic_lerp(float a, float b, float t)
{
    return a + t * (b - a);
}

static std::array<float, 2> getVectorAngle(float angle)
{
    std::array<float, 2> res;
    float x = 1;
    float y = 0;
    int circlePlace = 0;

    while (angle > 90) {
        angle -= 90;
        circlePlace += 1;
    }
    x = basic_lerp(0, 1, angle / 90.0f);
    y = basic_lerp(1, 0, angle / 90.0f);
    if (circlePlace % 2 != 0)
        std::swap(x, y);
    if (circlePlace == 1)
        y = -y;
    else if (circlePlace == 2) {
        x = -x;
        y = -y;
    } else if (circlePlace == 3)
        x = -x;
    res[0] = x;
    res[1] = y;
    return res;
}

void eng::ParticleEmitter::updateParticles(float delta)
{
    applyAcceleration(delta);
    applyTorque(delta);
    auto it = _particles.begin();

    for (; it != _particles.end(); it++) {
        auto vectorAngle = getVectorAngle(it->currentRotation);
        float x = (delta * it->currentSpeed) * vectorAngle[0];
        float y = (delta * it->currentSpeed) * vectorAngle[1];
        it->sprite.setRotation(it->currentRotation);
        it->sprite.move(x, y);
    }
}

void eng::ParticleEmitter::setParticleTexture(int type)
{
    if (eng::PARTICLE_TYPE::Pixel == type)
        _texture->create(1, 1);
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

void eng::ParticleEmitter::setBaseSpeed(float speed)
{
    _baseSpeed = speed;
}

void eng::ParticleEmitter::setAcceleration(float acceleration)
{
    _acceleration = acceleration;
}

void eng::ParticleEmitter::setBaseRotation(float rotation)
{
    _baseRotation = rotation;
}

void eng::ParticleEmitter::setTorque(float torque)
{
    _torque = torque;
}

void eng::ParticleEmitter::setEmittingRate(float rate)
{
    _emissionRate = rate;
}

void eng::ParticleEmitter::setMaxNumber(float max)
{
    _maxNumber = max;
}

std::vector<eng::SuperParticle> &eng::ParticleEmitter::getParticles()
{
    return this->_particles;
}