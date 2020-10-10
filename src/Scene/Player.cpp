#include "Scene.hpp"
#include "Renderer.hpp"
#include "Physics/PhysicsWorld.hpp"
#include "Layers/HudLayer.hpp"
#include "Core/Timer.hpp"

static constexpr float HeatRegen = 100.f;
static constexpr float MoveHeatCost = 8.f;
static constexpr float ShootHeatCost = 4.f;

float heat = 0.f;
sf::Clock heatTimer;
sf::Clock shootTimer;

bool overheat = false;

void initPlayer(Spacecraft* c)
{
    c->body = c->sceneCtx->physWorld->addRigidBody({0,0}, true);
    c->body->applyLinearImpulse({1,0});
}

void exertHeat(float hdiff)
{
    heat = std::min(heat + hdiff, 100.f);

    if (heat >= 100.f)
        overheat = true;

    heatTimer.restart();
}

void control(Spacecraft* c)
{
    if (overheat) return;

    c->body->rotateTowards(Renderer::get().getGlobalMousePosition(), 200 * timer::delta);

    float speed = (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) ? 8.f : 2.f;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        c->body->applyLinearImpulse(c->body->getDirection() * timer::delta * speed);
        exertHeat(speed * 2 * timer::delta);
    }

    Renderer::get().setZoom(math::length(c->body->getLinearVelocity()));
}

void shoot(Spacecraft* c)
{
    // if (overheat) return;

    // if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && shootTimer.getElapsedTime().asMilliseconds() > 250)
    // {
    //     vec2 pos = c->body->getPosition();
    //     vec2 dir = math::normalize(Renderer::get().getGlobalMousePosition() - pos);

    //     int bullet = scene->createEntity({pos.x, pos.y});
    //     scene->addRigidBody(bullet, RigidBody::PlayerBullet, pos, dir);

    //     EventQueue::get().registerCallback(Event::DamageEntity, bullet,
    //     [=](const Event& event, int ent)
    //     {
    //         scene->destroyEntity(bullet);
    //     });

    //     exertHeat(ShootHeatCost);
    //     shootTimer.restart();
    // }
}

void updatePlayer(Spacecraft* c)
{
    control(c);

    if (heatTimer.getElapsedTime() > sf::seconds(0.5))
    {
        heat = std::max(heat - timer::delta * HeatRegen, 0.f);

        if (heat == 0.f)
            overheat = false;
    }

    HudLayer::setPlayerCoords(c->pos.x, c->pos.y);
    HudLayer::setHeat(heat);
    HudLayer::setHealthPercentage(float(c->health) / float(c->maxHealth));

    c->pos = c->body->getPosition();
}

void drawPlayer(Spacecraft* c)
{
    Renderer::get().setView(c->pos);
}
