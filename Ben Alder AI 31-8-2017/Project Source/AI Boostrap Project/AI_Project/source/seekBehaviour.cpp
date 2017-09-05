#include "seekBehaviour.h"
#include "GameObject.h"

#include <glm\glm.hpp>
#include <Renderer2D.h>

seekBehaviour::seekBehaviour() : m_innerRadius(0.f) , m_outerRadius(0.f), m_strength(1000.f)
{

}

seekBehaviour::~seekBehaviour()
{

}

void seekBehaviour::update(GameObject *object, float deltaTime)
{
	float lastDistanceToTarget = glm::length(m_targetPosition - m_lastPosition);
	float DistanceToTarget = glm::length(m_targetPosition - object->getPosition());

	//just entered circle in this frame
	if (m_onOuterRadiusEnter && lastDistanceToTarget > m_outerRadius && DistanceToTarget <= m_outerRadius)
		m_onOuterRadiusEnter();
	//just finished seeking
	if (m_onInnerRadiusEnter && lastDistanceToTarget > m_innerRadius && DistanceToTarget <= m_innerRadius)
		m_onInnerRadiusEnter();
	//just finished fleeing
	if (m_onOuterRadiusExit && lastDistanceToTarget > m_outerRadius && DistanceToTarget >= m_outerRadius)
		m_onOuterRadiusExit();
	//just started fleeing
	if (m_onInnerRadiusExit && lastDistanceToTarget > m_innerRadius && DistanceToTarget >= m_innerRadius)
		m_onInnerRadiusExit();
	//was in inner circle at start of fleeing
	if (m_setHigherSpeed && DistanceToTarget < m_innerRadius)
		m_setHigherSpeed();

	if (m_setKeyboard && DistanceToTarget < m_innerRadius)
		m_setKeyboard();

	glm::vec2 directionToTartget = glm::normalize(m_targetPosition - object->getPosition()) * m_strength;
	object->applyForce(directionToTartget);

	m_lastPosition = object->getPosition();
}

void seekBehaviour::draw(GameObject * object, aie::Renderer2D *renderer)
{
	renderer->drawBox(m_targetPosition.x, m_targetPosition.y, 4, 4);

	renderer->setRenderColour(1.f, 1.f, 1.f, 0.5f);
	renderer->drawCircle(m_targetPosition.x, m_targetPosition.y, m_innerRadius);
	renderer->drawCircle(m_targetPosition.x, m_targetPosition.y, m_outerRadius);
	renderer->setRenderColour(1.f, 1.f, 1.f, 1.f);
}

const glm::vec2 & seekBehaviour::getTarget()
{
	return m_targetPosition;
}

void seekBehaviour::setTarget(const glm::vec2 & target)
{
	m_targetPosition = target;
}

void seekBehaviour::setForceStrength(float strength)
{
	m_strength = strength;
}

float seekBehaviour::getForceStrength()
{
	return m_strength;
}

void seekBehaviour::setInnerRadius(float radius)
{
	m_innerRadius = radius;
}

float seekBehaviour::getInnerRadius()
{
	return m_innerRadius;
}

void seekBehaviour::setOuterRadius(float radius)
{
	m_outerRadius = radius;
}

float seekBehaviour::getOuterRadius()
{
	return m_outerRadius;
}

void seekBehaviour::onInnerRadiusEnter(std::function<void()> func)
{
	m_onInnerRadiusEnter = func;
}

void seekBehaviour::onInnerRadiusExit(std::function<void()> func)
{
	m_onInnerRadiusExit = func;
}

void seekBehaviour::onOuterRadiusEnter(std::function<void()> func)
{
	m_onOuterRadiusEnter = func;
}

void seekBehaviour::onOuterRadiusExit(std::function<void()> func)
{
	m_onOuterRadiusExit = func;
}

void seekBehaviour::setKeyboard(std::function<void()> func)
{
	m_setKeyboard = func;
}

void seekBehaviour::setHigherSpeed(std::function<void()> func)
{
	m_setHigherSpeed = func;
}
