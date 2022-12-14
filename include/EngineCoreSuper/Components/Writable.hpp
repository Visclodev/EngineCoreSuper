/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Writable
*/

#ifndef WRITABLE_HPP_
#define WRITABLE_HPP_

#include "iostream"
#include "SFML/Window.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/System/String.hpp"

namespace eng
{
    /// @brief A class holding your texts
    class Writable {
        public:
            /// @brief Writable object constructor
            /// @param name name of the Writable object
            /// @param content text contained in the object
            /// @param fontPath path to the font file
            /// @param charSize size of the characters
            /// @param color color of the characters
            /// @param style style of the text
            /// @param x horizontal offset of the text
            /// @param y vertical offset of the text
            Writable(std::string name,
            sf::String content = "Text",
            const std::string fontPath = "../assets/Russo_One.ttf",
            unsigned int charSize = 30,
            sf::Color color = sf::Color::White,
            sf::Text::Style style = sf::Text::Regular,
            float x = 0, float y = 0) {
                _font->loadFromFile(fontPath);
                _content = &content;
                _color = &color;
                _txt.setString(*_content);
                _txt.setCharacterSize(charSize);
                _txt.setFont(*_font);
                _txt.setFillColor(*_color);
                _txt.setStyle(style);
                _name = name;
                _xOffset = x;
                _yOffset = y;
            }
            ~Writable() {}
            sf::String *_content = new sf::String;
            sf::Font *_font = new sf::Font;
            sf::Color *_color = new sf::Color;
            sf::Text _txt;
            std::string _name;
            float _xOffset;
            float _yOffset;
        protected:
        private:
    };
} // namespace eng

#endif /* !WRITABLE_HPP_ */