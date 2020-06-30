#pragma once
#include "Objective.hpp"

class ODestroyTheConvoy : public Objective
{
public:
    ODestroyTheConvoy(Scene* scene);
    ~ODestroyTheConvoy() = default;

    void check() override final;

private:
    int m_dronesToKill = 0;
    int m_dronesKilled = 0;
};