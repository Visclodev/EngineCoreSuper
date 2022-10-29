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
    emitter.setParticleColorRandom(true);
    emitter.setBaseSpeed(30, 100);
    emitter.setBaseRotation(0, 360);
    emitter.setAcceleration(100);
    emitter.setTorque(-50, 100);
    emitter.setEmittingRate(0.001);
    emitter.setMaxNumber(10000);
    emitter.setLifetime(1);
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
    reg.registerComponents(eng::SparseArray<eng::CircleCollider>());
    reg.registerComponents(eng::SparseArray<eng::RectCollider>());
    reg.registerComponents(eng::SparseArray<eng::RigidBody>());
}

eng::Entity addBaba(eng::Registry &reg, eng::TextureManager &tm)
{
    eng::Entity baba = reg.spawnEntity();

    reg.emplaceComponent(baba, Player("baba", 56));
    reg.emplaceComponent(baba, eng::Position(32, 32, 0));
    reg.emplaceComponent(baba, eng::Velocity(1000, 0));
    reg.emplaceComponent(baba, eng::Drawable(tm.getTextureFromFile("../assets/logo.png")));
    reg.emplaceComponent(baba, eng::RigidBody(eng::RigidBody::ColliderType::CIRCLE, true, 0.5));
    reg.emplaceComponent(baba, eng::CircleCollider(32));
    reg.getComponents<eng::Velocity>()[baba.getId()].value().angular = 90;
    reg.getComponents<eng::Drawable>()[baba.getId()].value().sprite.setOrigin(16, 16);
    return baba;
}

eng::Entity addBoubou(eng::Registry &reg, eng::TextureManager &tm)
{
    eng::Entity baba = reg.spawnEntity();

    reg.emplaceComponent(baba, Player("baba", 56));
    reg.emplaceComponent(baba, eng::Position(750, 50, 0));
    reg.emplaceComponent(baba, eng::Velocity(0, 0));
    reg.emplaceComponent(baba, eng::Drawable(tm.getTextureFromFile("../assets/logo.png")));
    reg.emplaceComponent(baba, eng::RigidBody(eng::RigidBody::ColliderType::RECTANGLE, false));
    reg.emplaceComponent(baba, eng::RectCollider(32, 32));
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
    gfx.setFrameRateLimit(360);
    eng::TextureManager tm;

    gfx.setFrameRateLimit(60);
    setupRegistry(reg);
    addText(reg);
    eng::Entity baba(0);
    eng::Entity boubou(0);
    baba = addBaba(reg, tm);
    boubou = addBoubou(reg, tm);
    eng::Entity particle =  addParticleEmmiter(reg);
    print_infos(reg, baba);

    while (gfx.isWindowOpen()) {
        gfx.eventCatchWindow();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            gfx.getRenderWindow().close();
        followMouse(particle, reg, gfx);
        physics.moveAndCollide(reg);
        physics.applyGravity(reg);
        //physics.applyRigidBodyCollisions(reg);
        gfx.clear();
        gfx.animateSystem(reg);
        gfx.drawSystem(reg);
        gfx.writeSystem(reg);
        gfx.particleSystem(reg);
        gfx.display();
    }
    return (0);
}
