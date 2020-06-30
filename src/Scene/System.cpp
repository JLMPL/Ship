#include "System.hpp"
#include "Scene.hpp"

System::System(Scene* scene)
	: m_scene(scene)
{
}

void System::update()
{
	for (auto& [id, ent] : m_scene->m_entities)
	{
		if ((ent->mask & m_signature) == m_signature)
		{
			execute(id);
		}
	}
}
