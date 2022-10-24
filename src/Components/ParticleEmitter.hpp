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
            void setParticleColor(sf::Color color);
            void setParticleColor(int r, int g, int b, int a);
            bool isLocal = true;
            std::vector<eng::SuperParticle> &getParticles();
        private:
            std::vector<eng::SuperParticle> _particles;
            sf::Texture *_texture = new sf::Texture();
            sf::Color _color = sf::Color::White;
            int _particleType;
            float _maxNumber = 20;

            // Position & Rotation
            float _baseSpeed = 5;
            float _acceleration = 0;
            float _baseRotation = 0;
            float _torque = 0;

            // Timers
            float _lifeTime = 5;
            float _nextEmission = 0;
            float _emissionRate = 1;
    };
} // namespace eng

#endif /* !PARTICLEEMITTER_HPP_ */
