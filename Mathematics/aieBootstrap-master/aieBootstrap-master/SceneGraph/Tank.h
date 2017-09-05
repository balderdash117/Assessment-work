#pragma once

#include "Node.h"

class SpriteNode;
namespace aie
{
	class Texture;
}

class Tank : public Node
{
public:

	Tank();
	virtual ~Tank();

	virtual void Update(float deltaTime);
	virtual void Render(aie::Renderer2D *renderer);

protected:

	SpriteNode *m_base;
	SpriteNode *m_turret;

	aie::Texture *m_tankBaseTexture = nullptr;
	aie::Texture *m_turretTexture = nullptr;


private:
};