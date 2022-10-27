/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Sound
*/

#ifndef SOUND_HPP_
#define SOUND_HPP_

#include <SFML/Audio.hpp>

namespace eng
{
    /// @brief A class holding sound components
    class Sound {
        public:
            /// @brief Sound object constructor
            /// @param filepath path to the audio file
            /// @param pToPlay true : the sound will be played, false otherwise
            Sound(std::string filepath, bool pToPlay = false) {
                toPlay = pToPlay;
                buffer->loadFromFile(filepath);
                sound.setBuffer(*buffer);
            }
            ~Sound() {}

            sf::SoundBuffer *buffer = new sf::SoundBuffer;
            sf::Sound sound;
            bool toPlay;
        protected:
        private:
    };
} // namespace eng

#endif /* !SOUND_HPP_ */
