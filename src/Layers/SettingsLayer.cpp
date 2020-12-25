// #include "SettingsLayer.hpp"
// #include "LayerStack.hpp"
// #include "Renderer.hpp"

// SettingsLayer::SettingsLayer(LayerStack& layerStack)
//     : Layer(layerStack)
// {
//     m_font.loadFromFile("data/NotoSans-Regular.ttf");

//     m_title.setFont(m_font);
//     m_title.setCharacterSize(64);
//     m_title.setString("Starry Stealers");
//     m_title.setPosition({32, 64});

//     m_settings.setFont(m_font);
//     m_settings.setCharacterSize(32);
//     m_settings.setString("Settings");
//     m_settings.setPosition({32, 150});
//     m_settings.setFillColor({128,128,128,255});

//     m_menu.addItem("Audio", [this]()
//     {
//     });

//     m_menu.addItem("Controls", [this]()
//     {
//     });

//     m_menu.addItem("Back", [this]()
//     {
//         m_layerStack.pop();
//         m_layerStack.push(Layer::Type::MainMenu);
//     });
// }

// void SettingsLayer::update(float dt)
// {
//     m_menu.update(dt);
// }

// void SettingsLayer::draw()
// {
//     Renderer::get().draw(m_title);
//     Renderer::get().draw(m_settings);

//     m_menu.draw();
// }

