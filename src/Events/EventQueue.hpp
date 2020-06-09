#pragma once
#include "Event.hpp"
#include <functional>
#include <deque>
#include <array>
#include <vector>

class EventQueue
{
public:
    struct EventCallback
    {
        int ent = -1;
        std::function<void(const Event&)> func;
    };

    void registerCallback(Event::Type event, int ent, const std::function<void(const Event&)>&& callback);
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
};
