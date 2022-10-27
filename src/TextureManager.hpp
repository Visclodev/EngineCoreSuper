/*
** EPITECH PROJECT, 2022
** EngineCoreSuper
** File description:
** TextureManager
*/

#ifndef TEXTUREMANAGER_HPP_
#define TEXTUREMANAGER_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>

namespace eng
{
    class TextureManager {
        public:
            TextureManager();
            ~TextureManager();

            sf::Texture &getTextureFromFile(std::string);
        protected:
        private:
            std::map<std::string, sf::Texture *> _textures;
    };
} // namespace eng

#endif /* !TEXTUREMANAGER_HPP_ */