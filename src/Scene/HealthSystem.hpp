#pragma once
#include "System.hpp"

class HealthSystem : public System
{
public:
    HealthSystem(Scene* scene);

    void registerEntity(int id);
    void execute(int id) override final;
};