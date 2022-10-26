/*
** EPITECH PROJECT, 2022
** EngineCoreSuper
** File description:
** ParticleEmitter
*/

#include "ParticleEmitter.hpp"
#include <iostream>

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
        it->currentRotation += (delta * _torque);
}

void eng::ParticleEmitter::emitParticle(float delta, float x, float y)
{
    _nextEmission -= delta;

    if (_nextEmission <= 0) {
        float baseRotation = _baseRotation;
        if (_fixedRotation == false)
            baseRotation += rand() % int(_baseRotationMax - _baseRotation);
        _particles.push_back(
            eng::SuperParticle(*_texture, _color, _baseSpeed, baseRotation,
            x, y)
        );
        _nextEmission = _emissionRate;
    }
}

float eng::ParticleEmitter::_basicLerp(float a, float b, float t)
{
    return a + t * (b - a);
}

std::array<float, 2> eng::ParticleEmitter::_getVectorAngle(float angle)
{
    std::array<float, 2> res;
    float x = 1;
    float y = 0;
    int circlePlace = 0;

    while (angle > 90) {
        angle -= 90;
        circlePlace += 1;
    }
    x = _basicLerp(0, 1, angle / 90.0f);
    y = _basicLerp(1, 0, angle / 90.0f);
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
        auto vectorAngle = _getVectorAngle(it->currentRotation);
        float x = (delta * it->currentSpeed) * vectorAngle[0];
        float y = (delta * it->currentSpeed) * vectorAngle[1];
        it->sprite.setRotation(it->currentRotation);
        it->sprite.move(x, y);
    }
}

void eng::ParticleEmitter::setParticleTexture(int type)
{
    if (eng::PARTICLE_TYPE::Pixel == type) {
        sf::Uint8 *pixelArray = new sf::Uint8(1 * 1 * 4);
        for (int i = 0; i < 4; i++)
            pixelArray[i] = 255;
        _texture->create(1, 1);
        _texture->update(pixelArray);
        delete pixelArray;
    }
}

void eng::ParticleEmitter::setParticleTexture(int type, std::string filepath)
{
    if (eng::PARTICLE_TYPE::Sprite)
        _texture->loadFromFile(filepath);
}

void eng::ParticleEmitter::setParticleColor(sf::Color color)
{
    _fixedColor = true;
    this->_color = color;
}

void eng::ParticleEmitter::setParticleColor(int r, int g, int b, int a)
{
    _fixedColor = true;
    this->_color = sf::Color(r, g, b, a);
}

void eng::ParticleEmitter::setParticleColor(sf::Color color, sf::Color maxColor)
{
    _fixedColor = false;
    _color = color;
    _colorMax = maxColor;
}

void eng::ParticleEmitter::setBaseSpeed(float speed)
{
    _fixedSpeed = true;
    _baseSpeed = speed;
}

void eng::ParticleEmitter::setAcceleration(float acceleration)
{
    _fixedAcceleration = true;
    _acceleration = acceleration;
}

void eng::ParticleEmitter::setBaseRotation(float rotation)
{
    _fixedRotation = true;
    _baseRotation = rotation;
}

void eng::ParticleEmitter::setTorque(float torque)
{
    _fixedTorque = true;
    _torque = torque;
}

void eng::ParticleEmitter::setBaseSpeed(float speed, float maxSpeed)
{
    _fixedSpeed = false;
    _baseSpeed = speed;
    _baseSpeedMax = maxSpeed;
}

void eng::ParticleEmitter::setAcceleration(float acceleration, float maxAcceleration)
{
    _fixedAcceleration = false;
    _acceleration = acceleration;
    _accelerationMax = maxAcceleration;
}

void eng::ParticleEmitter::setBaseRotation(float rotation, float maxRotation)
{
    _fixedRotation = false;
    _baseRotation = rotation;
    _baseRotationMax = maxRotation;
}

void eng::ParticleEmitter::setTorque(float torque, float maxTorque)
{
    _fixedTorque = false;
    _torque = torque;
    _torqueMax = maxTorque;
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