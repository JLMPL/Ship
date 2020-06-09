#include "EventQueue.hpp"

void EventQueue::registerCallback(Event::Type event, int ent, const std::function<void(const Event&)>&& callback)
{
    m_callbacks[event].push_back({ent, callback});
}

void EventQueue::pushEvent(const Event& event)
{
    m_events.push_back(event);
}

void EventQueue::redistributeEvents()
{
    for (auto& event : m_events)
    {
        for (auto& callback : m_callbacks[event.type])
        {
            if (event.receiver == callback.ent)
                callback.func(event);
        }
    }
    m_events.clear();
}
