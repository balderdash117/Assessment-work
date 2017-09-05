#pragma once
#include "Node.h"
#include "Renderer2D.h"
#include <Vector2.h>
#include <Matrix3.h>
#include <Application.h>
#include <vector>

class bullets :
	public Node
{
public:
	bullets();
	~bullets();

protected:
		Vector2 point;
		float rotate;
		float time;
		float speed;
		bool active;

};

