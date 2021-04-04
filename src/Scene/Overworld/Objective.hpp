#pragma once
#include "Scene/SceneObject.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Renderer.hpp"
#include "Libs/RichText/RichText.hpp"
#include "Scene/UI/Label.hpp"

enum ObjectiveType
{
    KILL_BANDITS = 0,
    ROB_MERCHANT,
    SURVIVE_TIME,
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

	const vec2& getPosition() const;

private:
    void generateNewObjective();
    void checkCompletion();

private:
    sf::Font m_font;

    Label m_obj;

    bool m_complete = false;
    ObjectiveType m_current = OBJECTIVE_COUNT;
    std::vector<SceneObject*> m_enemies;

    SceneObject* m_player = nullptr;
    SceneObject* m_merchant = nullptr;

    sf::Time m_timer;

    int m_droneNumber = 2;
    int m_gunnerNumber = -2;
    int m_mothershipNumber = -6;

    sf::Time m_surviveTimer;

	vec2 m_pos;
};