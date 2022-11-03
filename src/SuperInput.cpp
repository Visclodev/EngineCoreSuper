/*
** EPITECH PROJECT, 2022
** EngineCoreSuper
** File description:
** SuperInput
*/

#include "SuperInput.hpp"

eng::SuperInput::SuperInput(sf::Window &w): _w(w)
{
}

eng::SuperInput::~SuperInput()
{
}

void eng::SuperInput::updateEvents()
{
    // Update every key events
    for (auto it = _keyEvents.begin(); it != _keyEvents.end(); it++) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(it->first))) {
            for (auto i = it->second.begin(); i != it->second.end(); i++) {
                _inputMap[*i][2] = _inputMap[*i][0];
                _inputMap[*i][0] = 1.0f;
            }
        } else {
            for (auto i = it->second.begin(); i != it->second.end(); i++) {
                _inputMap[*i][2] = _inputMap[*i][0];
                _inputMap[*i][0] = 0.0f;
            }
        }
    }

    // Update every mouse button event
    for (auto it = _mouseEvents.begin(); it != _mouseEvents.end(); it++) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button(it->first))) {
            for (auto i = it->second.begin(); i != it->second.end(); i++) {
                _inputMap[*i][2] = _inputMap[*i][0];
                _inputMap[*i][0] = 1.0f;
            }
        } else {
            for (auto i = it->second.begin(); i != it->second.end(); i++) {
                _inputMap[*i][2] = _inputMap[*i][0];
                _inputMap[*i][0] = 0.0f;
            }
        }
    }

    // Update every joystick button event
    for (auto it = _buttonEvents.begin(); it != _buttonEvents.end(); it++) {
        if (sf::Joystick::isButtonPressed(it->first.first, (int)it->first.second)) {
            for (auto i = it->second.begin(); i != it->second.end(); i++) {
                _inputMap[*i][2] = _inputMap[*i][0];
                _inputMap[*i][0] = 1.0f;
            }
        } else {
            for (auto i = it->second.begin(); i != it->second.end(); i++) {
                _inputMap[*i][2] = _inputMap[*i][0];
                _inputMap[*i][0] = 0.0f;
            }
        }
    }
    // Update every joystick analog event

}

void eng::SuperInput::addAction(std::string action, float deadzone)
{
    _inputMap[action] = {0.0f, deadzone, 0.0f};
}

// Add events

void eng::SuperInput::addEvent(std::string action, eng::SuperInput::Key keyEvent)
{
    _keyEvents[keyEvent].emplace_back(action);
}

void eng::SuperInput::addEvent(std::string action,
eng::SuperInput::JoyAnalog joyEvent, int joyIdx)
{
    _analogEvents[{joyIdx, joyEvent}].emplace_back(action);
}

void eng::SuperInput::addEvent(std::string action,
eng::SuperInput::JoyButton joyEvent, int joyIdx)
{
    _buttonEvents[{joyIdx, joyEvent}].emplace_back(action);
}

void eng::SuperInput::addEvent(std::string action, eng::SuperInput::MouseButton mouseEvent)
{
    _mouseEvents[mouseEvent].emplace_back(action);
}

void eng::SuperInput::clearEvent(std::string action)
{
    // Clear key events related to action
    for (auto it = _keyEvents.begin(); it != _keyEvents.end(); it++)
        for (auto i = it->second.begin(); i != it->second.end(); i++)
            if (*i == action)
                it->second.erase(i);
    // Clear mouse events related to action
    for (auto it = _mouseEvents.begin(); it != _mouseEvents.end(); it++)
        for (auto i = it->second.begin(); i != it->second.end(); i++)
            if (*i == action)
                it->second.erase(i);
    // Clear joyAnalog events related to action
    for (auto it = _analogEvents.begin(); it != _analogEvents.end(); it++)
        for (auto i = it->second.begin(); i != it->second.end(); i++)
            if (*i == action)
                it->second.erase(i);
    // Clear joyButton events related to action
    for (auto it = _buttonEvents.begin(); it != _buttonEvents.end(); it++)
        for (auto i = it->second.begin(); i != it->second.end(); i++)
            if (*i == action)
                it->second.erase(i);
}

// Action Getters

float eng::SuperInput::getActionStrength(std::string action)
{
    return _inputMap[action][0] - _inputMap[action][1];
}

bool eng::SuperInput::isActionPressed(std::string action)
{
    return (_inputMap[action][0] == 1.0f);
}

bool eng::SuperInput::isActionJustPressed(std::string action)
{
    return (_inputMap[action][0] == 1.0f && _inputMap[action][2] < 1.0f);
}

bool eng::SuperInput::isActionJustReleased(std::string action)
{
    return (_inputMap[action][0] < 1.0f && _inputMap[action][2] == 1.0f);
}