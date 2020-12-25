// #pragma once
// #include "Layer.hpp"
// #include <vector>

// class LayerStack
// {
// public:
//     struct Command
//     {
//         enum class Type
//         {
//             Push,
//             Pop,
//             Clear
//         };

//         Type type;
//         Layer::Type state;
//     };

//     LayerStack() = default;
//     ~LayerStack() = default;

//     void update(float dt);
//     void draw();

//     void push(Layer::Type state);
//     void pop();
//     void clear();

//     bool isEmpty();

//     template <typename T>
//     T& getLayer(int index = 0)
//     {
//         if (index >= m_states.size())
//         {
//             printf("Error: accessing layer over the top\n");
//             int* p = nullptr;
//             *p = 0;
//         }
//         return static_cast<T&>(*m_states[index]);
//     }

//     template <typename T>
//     T& getTop()
//     {
//         return static_cast<T&>(*m_states.back());
//     }

// private:
//     void applyPendingCommands();

// private:
//     std::vector<Layer::Ptr> m_states;
//     std::vector<Command> m_commands[2];
//     bool commandPage = false;
// };