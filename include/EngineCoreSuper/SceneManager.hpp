/*
** EPITECH PROJECT, 2022
** EngineCoreSuper
** File description:
** SceneManager
*/

#ifndef SCENEMANAGER_HPP_
#define SCENEMANAGER_HPP_

#include <stack>
#include <optional>
#include "RegistryManager.hpp"
#include "IScene.hpp"

namespace eng
{
    class SceneManager {
        public:
            SceneManager(eng::RegistryManager &manager);
            ~SceneManager();

            /// @brief verify if the SceneStack is empty
            /// @return true if empty, false if not empty
            bool empty();

            /// @brief get a ref to the top scene
            /// @return a ref to the top scene
            IScene &top();

            /// @brief get the top registry of the attached registry manager
            /// @return a pointer to the top registry
            Registry &getAttachedTopRegistry();

            /// @brief add a new scene to the SceneManager
            /// @param scene the scene ref (scene must derive from IScene)
            void push(IScene *scene);

            /// @brief pop the top scene of the SceneManager, optionally
            /// managing attached RegistryManager
            void pop();
        protected:
        private:
            eng::RegistryManager &_registryManager;
            std::stack<IScene *> _stack;
    };
} // namespace eng

#endif /* !SCENEMANAGER_HPP_ */
