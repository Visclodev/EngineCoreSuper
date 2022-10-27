/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Drawable
*/

#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_

#include "iostream"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

namespace eng
{
    /// @brief A component holding your sprite
    class Drawable {
        public:
            /// @brief Drawable object constructor
            /// (prefer the use of sf::Texture& instead of std::string
            /// by using a texture manager maybe)
            /// @param textureFilePath path to your Sprite
            /// @param pSheetDirection the direction of your spritesheet
            /// [0:none]
            /// [1:left to right]
            /// [2:right to left]
            /// [3:up to down]
            /// [4:down to up]
            /// @param rect the dimensions of one sprite in your spritesheet
            /// @param pFrameTime how much time from one frame to another,
            /// -1 to not animate
            Drawable(std::string textureFilePath,
            int pSheetDirection = 0,
            sf::IntRect rect = {0, 0, 0, 0},
            float pFrameTime = -1) {
                sheetDirection = pSheetDirection;
                texture = new sf::Texture;
                texture->loadFromFile(textureFilePath);
                sprite.setTexture(*texture);
                sizeX = texture->getSize().x;
                sizeY = texture->getSize().y;
                frameTime = pFrameTime;
                _holdTexture = true;
                if (sheetDirection != 0)
                    sprite.setTextureRect(rect);
            }
            /// @brief Drawable object constructor
            /// @param textureFilePath path to your Sprite
            /// @param pSheetDirection the direction of your spritesheet
            /// [0:none]
            /// [1:left to right]
            /// [2:right to left]
            /// [3:up to down]
            /// [4:down to up]
            /// @param rect the dimensions of one sprite in your spritesheet
            /// @param pFrameTime how much time from one frame to another,
            /// -1 to not animate
            Drawable(sf::Texture &pTexture,
            int pSheetDirection = 0,
            sf::IntRect rect = {0, 0, 0, 0},
            float pFrameTime = -1) {
                texture = &pTexture;
                sprite.setTexture(*texture);
                sheetDirection = pSheetDirection;
                sizeX = texture->getSize().x;
                sizeY = texture->getSize().y;
                frameTime = pFrameTime;
                if (sheetDirection != 0)
                    sprite.setTextureRect(rect);
            }
            ~Drawable() {
                if (_holdTexture)
                    delete texture;
            }

            int sheetDirection;
            float frameTime;
            float nextFrame = 0;
            sf::Texture *texture;
            sf::Sprite sprite;
            int sizeX;
            int sizeY;
        protected:
        private:
            bool _holdTexture = false;
    };
} // namespace eng



#endif /* !DRAWABLE_HPP_ */
