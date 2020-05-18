#pragma once
#include "Layer.hpp"
#include <vector>

class LayerStack
{
public:
    struct Command
    {
        enum class Type
        {
            Push,
            Pop,
            Clear
        };

        Type type;
        Layer::Type state;
    };

    LayerStack() = default;
    ~LayerStack() = default;

    void update(float dt);
    void draw();

    void push(Layer::Type state);
    void pop();
    void clear();

    bool isEmpty();

private:
    void applyPendingCommands();

private:
    std::vector<Layer::Ptr> m_states;
    std::vector<Command> m_commands;
};