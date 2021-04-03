#pragma once
#include <SFML/Audio.hpp>

// #define DISABLE_AUDIO

class _Audio
{
public:
    enum
    {
        EFFECT_BLASTER = 0,
        EFFECT_LASER,
        EFFECT_ROCKET,
        EFFECT_EXPLOSION,
        EFFECT_BIG_EXPLOSION,
        EFFECT_MENU_SWITCH,
        EFFECT_MENU_SELECT,
        EFFECT_ENGINE,
        EFFECT_ENEMY_BLASTER,

        EFFECT_COUNT
    };

    _Audio();
    ~_Audio() = default;

    void updateVolumes();

    void playSound(int effect);
    void stopSound(int effect);
    void setVolume(int effect, float value);

private:
    sf::SoundBuffer m_buffers[EFFECT_COUNT];
    sf::Sound m_sounds[EFFECT_COUNT];
};

extern _Audio Audio;