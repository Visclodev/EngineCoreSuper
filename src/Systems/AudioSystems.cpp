/*
** EPITECH PROJECT, 2022
** EngineCoreSuper
** File description:
** AudioSystems
*/

#include "AudioSystems.hpp"

eng::AudioSystems::AudioSystems()
{
}

eng::AudioSystems::~AudioSystems()
{
}

void eng::AudioSystems::playSound(Registry &r)
{
    auto &sounds = r.getComponents<Sound>();

    for (int i = 0; i < sounds.size(); i++)
        if (sounds[i].has_value() && sounds[i].value().toPlay) {
            sounds[i].value().toPlay = false;
            sounds[i].value().sound.play();
        }
}

void eng::AudioSystems::playMusic(Registry &r)
{
    auto &musics = r.getComponents<Music>();

    for (int i = 0; i < musics.size(); i++)
        if (musics[i].has_value() && musics[i].value().toPlay) {
            musics[i].value().toPlay = false;
            musics[i].value().music->play();
        }
}

void eng::AudioSystems::pauseAllMusic(Registry &r)
{
    auto &musics = r.getComponents<Music>();

    for (int i = 0; i < musics.size(); i++)
        if (musics[i].has_value())
            musics[i].value().music->pause();
}

void eng::AudioSystems::setAllMusicToPlay(Registry &r)
{
    auto &musics = r.getComponents<Music>();

    for (int i = 0; i < musics.size(); i++)
        if (musics[i].has_value())
            musics[i].value().toPlay = true;
}