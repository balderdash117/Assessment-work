#include "followPathBehaviour.h"
#include "path.h"
#include "GameObject.h"

#include <Renderer2D.h>
#include <glm\glm.hpp>

followPathBehaviour::followPathBehaviour() : behaviour(), m_currentPathNodeIndex(0),
											 m_path(nullptr), m_strength(1000.f),
											 m_nodeRadius(10.f)
{

}

followPathBehaviour::~followPathBehaviour()
{

}

void followPathBehaviour::update(GameObject * obj, float deltaTime)
{
	auto &path = m_path->getPath();

	if (!path.empty())
	{
		glm::vec2 point = path[m_currentPathNodeIndex];
		if (glm::length(point - obj->getPosition()) < m_nodeRadius)
		{
			m_currentPathNodeIndex += 1;
		}

		m_currentPathNodeIndex = m_currentPathNodeIndex % path.size();
		point = path[m_currentPathNodeIndex];

		//seek towards the point
		glm::vec2 directionToTartget = glm::normalize(point - obj->getPosition()) * m_strength;
		obj->applyForce(directionToTartget);
	}
}

void followPathBehaviour::draw(GameObject * obj, aie::Renderer2D * renderer)
{
	auto &path = m_path->getPath();
	glm::vec2 lastPathPoint;
	int index = 0;

	for (auto iter = path.begin(); iter != path.end(); ++iter, ++index)
	{
		glm::vec2 point = (*iter);
		
		renderer->setRenderColour(1.f, 1.f, 1.f, 0.5f);
		renderer->drawCircle(point.x, point.y, m_nodeRadius);

		renderer->setRenderColour(1.f, 1.f, 1.f, 1.f);
		renderer->drawCircle(point.x, point.y, 4);

		if (index > 0)
		{
			renderer->drawLine(point.x, point.y, lastPathPoint.x, lastPathPoint.y);
		}

		lastPathPoint = point;
	}
}

void followPathBehaviour::setPath(path * Path)
{
	m_path = Path;
}

void followPathBehaviour::setforce(float force)
{
	m_strength = force;
}

void followPathBehaviour::setNodeRadius(float radius)
{
	m_nodeRadius = radius;
}

void followPathBehaviour::setPathNodeIndex(int index)
{
	m_currentPathNodeIndex = index;
}

int followPathBehaviour::getPathNodeIndex()
{
	return m_currentPathNodeIndex;
}

float followPathBehaviour::getNodeRadius()
{
	return m_nodeRadius;
}

float followPathBehaviour::getForce()
{
	return m_strength;
}

path * followPathBehaviour::getPath()
{
	return m_path;
}
