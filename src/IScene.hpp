/*
** EPITECH PROJECT, 2022
** EngineCoreSuper
** File description:
** IScene
*/

#ifndef ISCENE_HPP_
#define ISCENE_HPP_

class IScene {
    public:
        ~IScene() {}

        /// @brief add the sparseArrays to the registry, sets up the basic
        /// entities of your scene
        virtual void setupScene() = 0;

        /// @brief Launch all systems of the scene
        virtual void systemRun() = 0;
    protected:
    private:
};

#endif /* !ISCENE_HPP_ */
