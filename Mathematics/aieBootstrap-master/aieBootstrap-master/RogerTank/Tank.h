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
	virtual void SetTurretRotate(float p_radians);
	virtual void SetBaseRotate(float p_radians);
	virtual void SetBaseTranslate(Vector2 p_move);
	virtual float GetBaseRotate();
	virtual void SetShieldRotate(float p_radians);

protected:
	SpriteNode *m_base;
	SpriteNode *m_turret;
	SpriteNode *m_shield;

	aie::Texture *m_tankBaseTexture = nullptr;
	aie::Texture *m_turretTexture	= nullptr;
	aie::Texture *m_shieldTexture =	  nullptr;
private:
};