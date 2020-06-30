#include "EventQueue.hpp"

void EventQueue::registerCallback(Event::Type event, int ent, const CallbackSignature& callback)
{
    m_callbacks[event].push_back({ent, callback});
}

void EventQueue::unregisterForEntity(int ent)
{
    for (auto& calls : m_callbacks)
    {
        for (auto i = calls.begin(); i != calls.end();)
        {
            if ((*i).ent == ent)
                i = calls.erase(i);
            else
                i++;
        }
    }
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
                callback.func(event, callback.ent);
        }
    }
    m_events.clear();
}
