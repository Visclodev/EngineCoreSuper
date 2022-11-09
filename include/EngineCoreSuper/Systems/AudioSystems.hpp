/*
** EPITECH PROJECT, 2022
** EngineCoreSuper
** File description:
** AudioSystems
*/

#ifndef AUDIOSYSTEMS_HPP_
#define AUDIOSYSTEMS_HPP_

#include "../Registry.hpp"
#include "../Components/SuperComponents.hpp"

namespace eng
{
    class AudioSystems {
        public:
            AudioSystems();
            ~AudioSystems();

            /// @brief Play every sound set to play
            /// @param r The registry with sounds to play
            void playSound(Registry &r);

            /// @brief Play every music set to play
            /// @param r The registry with musics to play
            void playMusic(Registry &r);

            /// @brief Stops every music currently playing in a regitry
            /// @param r The registry containing the musics
            void pauseAllMusic(Registry &r);

            /// @brief Ready all music to play
            /// @param r The registry on which to apply thoses settings
            void setAllMusicToPlay(Registry &r);
        protected:
        private:
    };
} // namespace eng

#endif /* !AUDIOSYSTEMS_HPP_ */
