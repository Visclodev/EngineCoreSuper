/*
** EPITECH PROJECT, 2022
** EngineCoreSuper
** File description:
** TextureManager
*/

#include "TextureManager.hpp"

eng::TextureManager::TextureManager()
{
}

eng::TextureManager::~TextureManager()
{
    for (auto it = _textures.begin(); it != _textures.end(); it++) {
        delete it->second;
    }
}

sf::Texture &eng::TextureManager::getTextureFromFile(std::string filepath)
{
    if (_textures.find(filepath) == _textures.end()) {
        _textures[filepath] = new sf::Texture();
        _textures[filepath]->loadFromFile(filepath);
    }
    return *_textures[filepath];
}