/*
** EPITECH PROJECT, 2022
** EngineCoreSuper
** File description:
** ParticleEmitter
*/

#ifndef PARTICLEEMITTER_HPP_
#define PARTICLEEMITTER_HPP_

#include <vector>
#include <SFML/Graphics.hpp>
#include <array>

namespace eng
{
    enum PARTICLE_TYPE {
        Sprite,
        Pixel,
        Metaball
    };

    class SuperParticle {
        public:
            SuperParticle(sf::Texture &t, sf::Color c, float speed,
            float rotation, float x, float y):
            currentSpeed(speed), currentRotation(rotation)
            {
                sprite.setTexture(t);
                sprite.setColor(c);
                sprite.setPosition(x, y);
                sprite.setRotation(rotation);
                sprite.setOrigin(t.getSize().x / 2, t.getSize().y / 2);
            }
            ~SuperParticle() {}
            float lifeTime = 0;
            float currentSpeed;
            float currentRotation;
            sf::Sprite sprite;
            std::array<float, 2> direction;
        private:
    };

    class ParticleEmitter {
        public:
            ParticleEmitter();
            ~ParticleEmitter();

            void limitNumber();
            void killOldparticles(float delta);
            void applyAcceleration(float delta);
            void applyTorque(float delta);
            void updateParticles(float delta);
            void emitParticle(float delta, float x, float y);
            void setParticleTexture(int type);
            void setParticleTexture(int type, std::string filepath);
            void setLifetime(float lifetime);
            bool isLocal = true;
            void setEmittingRate(float rate);
            void setMaxNumber(float maxNumber);
            std::vector<eng::SuperParticle> &getParticles();

            // Fixeds

            void setBaseSpeed(float speed);
            void setAcceleration(float acceleration);
            void setBaseRotation(float rotation);
            void setTorque(float torque);
            void setParticleColor(sf::Color color);
            void setParticleColor(int r, int g, int b, int a);

            // Randoms

            void setBaseSpeed(float speed, float maxSpeed);
            void setAcceleration(float acceleration, float maxAcceleration);
            void setBaseRotation(float rotation, float maxRotation);
            void setTorque(float torque, float maxTorque);
            void setParticleColor(sf::Color color, sf::Color maxColor);
        private:
            std::vector<eng::SuperParticle> _particles;
            sf::Texture *_texture = new sf::Texture();
            int _particleType;
            float _maxNumber = 20;

            // Position & Rotation & Color
            // -Speed
            bool _randomSpeed = false;
            float _baseSpeed = 5;
            float _baseSpeedMax = 0;
            // -Acceleration
            bool _randomAcceleration = false;
            float _acceleration = 0;
            float _accelerationMax = 0;
            // -Rotation
            bool _randomRotation = false;
            float _baseRotation = 0;
            float _baseRotationMax = 0;
            // -Torque
            bool _randomTorque = false;
            float _torque = 0;
            float _torqueMax = 0;
            // -Color
            bool _randomColor = false;
            sf::Color _color = sf::Color::White;
            sf::Color _colorMax = sf::Color::White;

            // Timers
            float _lifeTime = 5;
            float _nextEmission = 0;
            float _emissionRate = 1;

            // Usefull methods
            float _basicLerp(float a, float b, float t);
            std::array<float, 2> _getVectorAngle(float angle);
    };
} // namespace eng

#endif /* !PARTICLEEMITTER_HPP_ */
