#include "path.h"

path::path()
{

}

path::~path()
{

}

void path::pushPathSegement(const glm::vec2 & point)
{
	m_pathPoints.push_back(point);
}

void path::popPathSegement()
{
	if (!m_pathPoints.empty())
	{
		m_pathPoints.pop_back();
	}
}

void path::clear()
{
	m_pathPoints.clear();
}

std::vector<glm::vec2>& path::getPath()
{
	return m_pathPoints;
}
