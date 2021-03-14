#include "Audio.hpp"

_Audio Audio;

_Audio::_Audio()
{
    m_buffers[EFFECT_BLASTER].loadFromFile("data/sounds/laserLarge_003.ogg");
    m_buffers[EFFECT_LASER].loadFromFile("data/sounds/engineCircular_000.ogg");
    m_buffers[EFFECT_ROCKET].loadFromFile("data/sounds/rocket.ogg");
    m_buffers[EFFECT_EXPLOSION].loadFromFile("data/sounds/laserLarge_003.ogg");
    m_buffers[EFFECT_MENU_SWITCH].loadFromFile("data/sounds/menu_switch.ogg");
    m_buffers[EFFECT_MENU_SELECT].loadFromFile("data/sounds/menu_select.ogg");
    m_buffers[EFFECT_ENGINE].loadFromFile("data/sounds/engine.ogg");
    m_buffers[EFFECT_ENEMY_BLASTER].loadFromFile("data/sounds/enemy_blaster.ogg");

    for (int i = 0; i < EFFECT_COUNT; i++)
    {
        m_sounds[i].setBuffer(m_buffers[i]);
    }

    m_sounds[EFFECT_LASER].setLoop(true);
    m_sounds[EFFECT_ENGINE].setLoop(true);
}

void _Audio::playSound(int effect)
{
    if (m_sounds[effect].getLoop() && m_sounds[effect].getStatus() == sf::Sound::Playing)
        return;


#ifndef DISABLE_AUDIO
    m_sounds[effect].play();
#endif
}

void _Audio::stopSound(int effect)
{
    m_sounds[effect].pause();
}

void _Audio::setVolume(int effect, float value)
{
    m_sounds[effect].setVolume(value * 100.f);
}