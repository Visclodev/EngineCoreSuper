/*
** EPITECH PROJECT, 2022
** EngineCoreSuper
** File description:
** SceneManager
*/

#include "SceneManager.hpp"

eng::SceneManager::SceneManager(eng::RegistryManager &manager):
_registryManager(manager)
{
}

eng::SceneManager::~SceneManager()
{
    while (!_stack.empty())
        pop();
}

bool eng::SceneManager::empty()
{
    return _stack.empty();
}

void eng::SceneManager::push(IScene *scene)
{
    _registryManager.addRegistry("newReg");
    _stack.push(scene);
    _stack.top()->setupScene();
}

void eng::SceneManager::pop()
{
    _registryManager.popRegistry();
    delete _stack.top();
    _stack.pop();
}

IScene &eng::SceneManager::top()
{
    return *_stack.top();
}

eng::Registry &eng::SceneManager::getAttachedTopRegistry()
{
    return _registryManager.getTop();
}
