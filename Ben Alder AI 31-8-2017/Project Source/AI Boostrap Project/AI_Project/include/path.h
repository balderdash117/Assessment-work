#pragma once

#include <glm\vec2.hpp>
#include <vector>

class path
{
public:
	path();
	~path();

	void						pushPathSegement(const glm::vec2 &point);
	void						popPathSegement();
	void						clear();

	std::vector<glm::vec2>	   &getPath();

protected:

	std::vector<glm::vec2>		m_pathPoints;

private:
};

