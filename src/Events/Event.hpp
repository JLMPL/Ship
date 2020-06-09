#pragma once

struct Event
{
    enum Type
    {
        DestroyEntity = 0,

        Count
    };

    Type type = Type::Count;
    int sender = -1;
    int receiver = -1;
};