#include "GameObject.h"
#include "behaviour.h"
#include "AI_ProjectApp.h"

#include <Renderer2D.h>

GameObject::GameObject() : friction(0.0f),  Behaviour(nullptr),
						   m_personTexture(nullptr), m_knightTexture(nullptr)
{
	m_personTexture = new aie::Texture("./textures/townsperson.png");
	m_knightTexture = new aie::Texture("./textures/knight.png");
}

GameObject::~GameObject()
{
	setBehaviour(nullptr);

	delete m_personTexture;
}

void GameObject::update(float deltaTime)
{
	if (Behaviour != nullptr)
		Behaviour->update(this, deltaTime);

	simulatePhysics(deltaTime);
}

void GameObject::draw(aie::Renderer2D *renderer)
{
	glm::vec2 targetHeading = (position + (velocity * 0.25f));

	if (m_objectType == 0)
	{
		if (m_personTexture != nullptr) renderer->drawSprite(m_personTexture, position.x, position.y, 25, 35);
	}
	else if (m_objectType == 1)
	{
		if (m_knightTexture != nullptr) renderer->drawSprite(m_knightTexture, position.x, position.y, 25, 35);
	}
	else
	{
		renderer->setRenderColour(1.f, 1.f, 1.f, 0.75f);
		renderer->drawCircle(position.x, position.y, 8);
	}

	renderer->setRenderColour(0xFF7F007F);
	renderer->drawLine(position.x, position.y, targetHeading.x , targetHeading.y , 2.0f);
	renderer->setRenderColour(0xFFFFFFFF);

	if (Behaviour != nullptr)
		Behaviour->draw(this, renderer);
}

const glm::vec2 & GameObject::getPosition()
{
	return position;
}

const glm::vec2 & GameObject::getVelocity()
{
	return velocity;
}

void GameObject::setPosition(const glm::vec2 &pos)
{
	position = pos;
}

void GameObject::setVelocity(const glm::vec2 &vel)
{
	velocity += vel;
}

void GameObject::applyForce(const glm::vec2 & force)
{
	acceleration += force;
}

float GameObject::getFriction()
{
	return friction;
}

void GameObject::setFriction(float frict)
{
	friction += frict;
}

void GameObject::simulatePhysics(float deltaTime)
{
	applyForce(friction * -velocity);

	velocity += acceleration * deltaTime;
	position += velocity * deltaTime;
	acceleration = glm::vec2(0, 0);
}

void GameObject::setBehaviour(behaviour * Behave)
{
	if (Behaviour && Behaviour->isOwnedByGameObject() == true)
		delete Behaviour;

	Behaviour = Behave;
}

behaviour * GameObject::getBehaviour()
{
	return Behaviour;
}

void GameObject::setObjectType(int value)
{
	m_objectType = value;
}

int GameObject::getObjectType()
{
	return m_objectType;
}

