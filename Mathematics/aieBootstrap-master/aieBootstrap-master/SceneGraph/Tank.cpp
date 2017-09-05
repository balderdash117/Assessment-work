#include "Tank.h"
#include <Texture.h>
#include "SpriteNode.h"
Tank::Tank()
{
	m_tankBaseTexture = new aie::Texture("./textures/tankBlue.png");
	m_turretTexture = new aie::Texture("./textures/barrelGreen.png");
	
	m_turret = new SpriteNode(m_turretTexture);
	m_turret->Translate(Vector2(0, 0));
	m_turret->SetOrigin(Vector2(0.0f, 0.5f));

	m_base = new SpriteNode(m_tankBaseTexture);
	m_base->Rotate(3.14159f / 4.0f); // 90 degrees

	m_turret->SetParent(m_base);
	m_base->SetParent(this);
}
Tank::~Tank()
{
	delete m_base;
	delete m_turret;

	delete m_turretTexture;
	delete m_tankBaseTexture;
}

void Tank::Update(float deltaTime)
{

}

void Tank::Render(aie::Renderer2D *renderer)
{
	m_base->Render(renderer);
	m_turret->Render(renderer);
}
