#include "System.hpp"
#include "Scene.hpp"

System::System(Scene* scene)
	: m_scene(scene)
{
}

void System::update()
{
    int id = 0;
	for (auto& ent : m_scene->m_entities)
	{
        if (!ent)
        {
            id++;
            continue;
        }
		if ((ent->mask & m_signature) == m_signature)
		{
			execute(id);
		}
        id++;
	}
}
