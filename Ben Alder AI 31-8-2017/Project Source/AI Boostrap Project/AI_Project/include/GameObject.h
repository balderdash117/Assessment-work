#pragma once

#include <Application.h>
#include <glm/vec2.hpp>
#include <Texture.h>

class behaviour;
class AI_ProjectApp;

namespace aie
{
	class Renderer2D;
};

class GameObject
{
public:
	GameObject(AI_ProjectApp *pApp);
	virtual ~GameObject();

	virtual void		 update(float deltaTime);
	virtual void		 draw(aie::Renderer2D *renderer);

	const glm::vec2		&getPosition();
	const glm::vec2		&getVelocity();
	
	void				 setPosition(const glm::vec2 & pos);
	void				 setVelocity(const glm::vec2 & vel);
						 
	void				 applyForce(const glm::vec2 & force);

	float				 getFriction();
	void				 setFriction(float frict);
						 
	void				 simulatePhysics(float deltaTime);
						 
	void				 setBehaviour(behaviour * Behaviour);
	behaviour			*getBehaviour();

	void				 setObjectType(int value);
	int					 getObjectType();


protected:

	aie::Texture		*m_personTexture;
	aie::Texture		*m_knightTexture;
	
	glm::vec2			 position;
	glm::vec2			 velocity;
	glm::vec2			 acceleration;
	
	AI_ProjectApp		*m_app;

	float				 friction;

	behaviour			*Behaviour;

	int					 m_objectType;

private:
};