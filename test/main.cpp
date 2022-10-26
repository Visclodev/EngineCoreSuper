/*
** EPITECH PROJECT, 2022
** EngineCoreSuper
** File description:
** main
*/

#include <EngineCoreSuper/EngineCoreSuper.hpp>

class Player{
    public:
        Player(std::string name_, int health_):
        name(name_), health(health_)
        {}
        ~Player()
        {}
        std::string name;
        int health;
    private:
};

void followMouse(eng::Entity entity, eng::Registry &r, eng::GraphicSystems &g)
{
    auto &pos = r.getComponents<eng::Position>()[entity.getId()].value();

    pos.x = sf::Mouse::getPosition(g.getRenderWindow()).x;
    pos.y = sf::Mouse::getPosition(g.getRenderWindow()).y;
}

void print_infos(eng::Registry &reg, eng::Entity &baba)
{
    std::cout << reg.getComponents<Player>()[baba.getId()].value().name << " has ";
    std::cout << reg.getComponents<Player>()[baba.getId()].value().health;
    std::cout << " health points!" << std::endl;

    std::cout << "He is at: {" << reg.getComponents<eng::Position>()[baba.getId()].value().x;
    std::cout << ", " << reg.getComponents<eng::Position>()[baba.getId()].value().y;
    std::cout << "}" << std::endl;
}

void addText(eng::Registry &r)
{
    eng::Entity text = r.spawnEntity();

    r.emplaceComponent(text, eng::Position(300, 1080 / 2, 0));
    r.emplaceComponent(text, eng::Writable("escape_text", "Press esc. key to exit"));
}

eng::Entity addParticleEmmiter(eng::Registry &r)
{
    eng::Entity particles = r.spawnEntity();

    r.emplaceComponent(particles, eng::Position(0, 0, 0));
    r.emplaceComponent(particles, eng::ParticleEmitter());
    auto &emitter = r.getComponents<eng::ParticleEmitter>()[particles.getId()].value();
    
    emitter.setParticleTexture(eng::PARTICLE_TYPE::Pixel);
    emitter.setBaseSpeed(100, 250);
    emitter.setBaseRotation(0, 360);
    emitter.setTorque(10);
    emitter.setEmittingRate(0.01);
    emitter.setAcceleration(-10);
    emitter.setMaxNumber(100000);
    emitter.setParticleColor(255, 255, 255, 150);
    emitter.setLifetime(5);
    emitter.isLocal = false;
    return particles;
}

void setupRegistry(eng::Registry &reg)
{
    reg.registerComponents(eng::SparseArray<Player>());
    reg.registerComponents(eng::SparseArray<eng::Position>());
    reg.registerComponents(eng::SparseArray<eng::Drawable>());
    reg.registerComponents(eng::SparseArray<eng::Velocity>());
    reg.registerComponents(eng::SparseArray<eng::Writable>());
    reg.registerComponents(eng::SparseArray<eng::ParticleEmitter>());
}

eng::Entity addBaba(eng::Registry &reg)
{
    eng::Entity baba = reg.spawnEntity();

    reg.emplaceComponent(baba, Player("baba", 56));
    reg.emplaceComponent(baba, eng::Position(32, 32, 0));
    reg.emplaceComponent(baba, eng::Velocity(0, 0));
    reg.emplaceComponent(baba, eng::Drawable("../assets/logo.png"));
    reg.getComponents<eng::Velocity>()[baba.getId()].value().angular = 90;
    reg.getComponents<eng::Drawable>()[baba.getId()].value().sprite.setOrigin(16, 16);
    return baba;
}

int main(void)
{
    eng::RegistryManager r;
    r.addRegistry("Registry one");
    auto reg = r.getTop();
    eng::GraphicSystems gfx(1920, 1080, "Coucou");
    eng::PhysicSystems physics(gfx.getDelta());

    gfx.setFrameRateLimit(60);
    setupRegistry(reg);
    addText(reg);
    eng::Entity baba = addBaba(reg);
    eng::Entity particle =  addParticleEmmiter(reg);
    print_infos(reg, baba);

    while (gfx.isWindowOpen()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            gfx.getRenderWindow().close();
        followMouse(particle, reg, gfx);
        physics.applyVelocities(reg);
        gfx.clear();
        gfx.drawSystem(reg);
        gfx.writeSystem(reg);
        gfx.particleSystem(reg);
        gfx.display();
    }
    return (0);
}
