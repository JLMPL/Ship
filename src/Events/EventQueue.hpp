#pragma once
#include "Event.hpp"
#include <functional>
#include <deque>
#include <array>
#include <vector>

class EventQueue
{
public:
    using CallbackSignature = std::function<void(const Event&, int entity)>;

    struct EventCallback
    {
        int ent = -1;
        CallbackSignature func;
    };

    void registerCallback(Event::Type event, int ent, const CallbackSignature& callback);
    void unregisterForEntity(int ent);

    void pushEvent(const Event& event);
    void redistributeEvents();

    static EventQueue& get()
    {
        static EventQueue eq;
        return eq;
    }

private:
    EventQueue() = default;
    ~EventQueue() = default;

private:
    std::deque<Event> m_events;

    std::array<std::vector<EventCallback>, Event::Count> m_callbacks;
    std::vector<int> m_toRemove;
};
