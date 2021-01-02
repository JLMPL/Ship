#pragma once
#include "Scene/SceneObject.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Renderer.hpp"
#include "Libs/RichText/RichText.hpp"

enum ObjectiveType
{
    KILL_BANDITS,
    ROB_MERCHANT,
    PROTECT_CLIENT,
    OBJECTIVE_COUNT
};

class Objective : public SceneObject
{
public:
    Objective(Scene* scene);
    ~Objective() = default;

    void ready() override final;
    void update(float dt) override final;
    void draw() override final;

private:
    void generateNewObjective();
    void checkCompletion();

private:
    sf::Font m_font;

    sfe::RichText m_rtext;

    bool m_complete = false;
    ObjectiveType m_current = OBJECTIVE_COUNT;
    std::vector<SceneObject*> m_enemies;

    sf::Clock m_timer;
};