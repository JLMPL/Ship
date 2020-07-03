#include "EventQueue.hpp"

void EventQueue::registerCallback(Event::Type event, int ent, const CallbackSignature& callback)
{
    m_callbacks[event].push_back({ent, callback});
}

void EventQueue::unregisterForEntity(int ent)
{
    m_toRemove.push_back(ent);
}

void EventQueue::pushEvent(const Event& event)
{
    m_events.push_back(event);
}

void EventQueue::redistributeEvents()
{
    for (auto& ent : m_toRemove)
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
    m_toRemove.clear();

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
