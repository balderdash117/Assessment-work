#pragma once

#include "behaviour.h"
#include <glm\vec2.hpp>
#include <functional>

class Renderer2D;

class seekBehaviour : public behaviour
{
public:
	seekBehaviour();
	virtual ~seekBehaviour();

	virtual void			update(GameObject *object, float deltaTime);
	virtual void			draw(GameObject *object, aie::Renderer2D *renderer);


	void					setTarget(const glm::vec2 &target);
	void					setForceStrength(float strength);
	void					setInnerRadius(float radius);
	void					setOuterRadius(float radius);

	const glm::vec2		   &getTarget();
	float					getForceStrength();
	float					getInnerRadius();
	float					getOuterRadius();

	void					onInnerRadiusEnter (std::function < void() > func);
	void					onInnerRadiusExit  (std::function < void() > func);
	void					onOuterRadiusEnter (std::function < void() > func);
	void					onOuterRadiusExit  (std::function < void() > func);
	void					setKeyboard		(std::function < void() > func);
	void					setHigherSpeed		(std::function < void() > func);

protected:

	glm::vec2				m_targetPosition;
	float					m_strength;
							
	float					m_innerRadius;
	float					m_outerRadius;

	
	std::function < void() >m_onInnerRadiusEnter;
	std::function < void() >m_onInnerRadiusExit;
	std::function < void() >m_onOuterRadiusEnter;
	std::function < void() >m_onOuterRadiusExit;
	std::function < void() >m_setKeyboard;
	std::function < void() >m_setHigherSpeed;

private:

	glm::vec2				m_lastPosition;
};

