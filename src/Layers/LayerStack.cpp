// #include "LayerStack.hpp"
// #include "MenuLayer.hpp"
// #include "SettingsLayer.hpp"
// #include "BackgroundLayer.hpp"
// #include "GameLayer.hpp"
// #include "HudLayer.hpp"

// void LayerStack::applyPendingCommands()
// {
//     auto oldCommandPage = commandPage;
//     commandPage = !commandPage;

//     for (auto& com : m_commands[oldCommandPage])
//     {
//         switch (com.type)
//         {
//             case Command::Type::Push:
//             {
//                 switch (com.state)
//                 {
//                     case Layer::Type::MainMenu:
//                         m_states.emplace_back(new MenuLayer(*this));
//                         break;
//                     case Layer::Type::Settings:
//                         m_states.emplace_back(new SettingsLayer(*this));
//                         break;
//                     case Layer::Type::Background:
//                         m_states.emplace_back(new BackgroundLayer(*this));
//                         break;
//                     case Layer::Type::Game:
//                         m_states.emplace_back(new GameLayer(*this));
//                         break;
//                     case Layer::Type::Hud:
//                         m_states.emplace_back(new HudLayer(*this));
//                         break;
//                     default: break;
//                 }
//             }
//             break;
//             case Command::Type::Pop:
//                 m_states.pop_back();
//                 break;
//             case Command::Type::Clear:
//                 m_states.clear();
//                 break;
//             default: break;
//         }
//     }
//     m_commands[oldCommandPage].clear();
// }

// void LayerStack::update(float dt)
// {
//     applyPendingCommands();

//     for (auto& state : m_states)
//         state->update(dt);
// }

// void LayerStack::draw()
// {
//     for (auto& state : m_states)
//         state->draw();
// }

// void LayerStack::push(Layer::Type state)
// {
//     m_commands[commandPage].push_back({Command::Type::Push, state});
// }

// void LayerStack::pop()
// {
//     m_commands[commandPage].push_back({Command::Type::Pop, Layer::Type::None});
// }

// void LayerStack::clear()
// {
//     m_commands[commandPage].push_back({Command::Type::Clear, Layer::Type::None});
// }

// bool LayerStack::isEmpty()
// {
//     return m_states.empty();
// }
