#pragma once
#include "behaviour.h"

class path;

class followPathBehaviour :	public behaviour
{
public:
	followPathBehaviour();
	virtual ~followPathBehaviour();

	virtual void	update(GameObject *obj, float deltaTime);
	virtual void	draw(GameObject *obj, aie::Renderer2D *renderer);

	void			setPath(path *Path);
	void			setforce(float force);
	void			setNodeRadius(float radius);
	void			setPathNodeIndex(int index);
	
	int				getPathNodeIndex();
	float			getNodeRadius();
	float			getForce();
	path		   *getPath();

protected:

	int				m_currentPathNodeIndex;

	float			m_strength;
	float			m_nodeRadius;

	bool			m_showingPath;

	path		   *m_path;

private:
};

