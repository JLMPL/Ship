#include "Enemy.hpp"
#include "Scene/Scene.hpp"
#include "Bullet.hpp"
#include "Player.hpp"
#include "Debris.hpp"

Enemy::Enemy(Scene* scene)
 : Spacecraft(scene)
{
}

void Enemy::draw()
{
    Spacecraft::draw();
    m_healthbar.draw();
}

void Enemy::onContact(SceneObject* other)
{
    if (!other) return;

    if (other->getName() == "player_bullet")
    {
        damage(other->as<Bullet>()->getDamage());
    }
}

void Enemy::damage(int value)
{
    m_health = std::max(0, m_health - value);

    if (m_health == 0)
    {
        if (!m_isDead)
        {
            m_player->as<Player>()->addMoney(m_moneyValue);

            for (int i = 0; i < 10; i++)
                m_scene->spawnObject<Debris>(m_pos, m_color);

            m_isDead = false;
        }
        destroy();
    }

    m_healthbar.setValue(m_health);
}

