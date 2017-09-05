#include "Tank.h"
#include <Texture.h>
#include "SpriteNode.h"
#include "Input.h"

Tank::Tank()
{
	m_tankBaseTexture = new aie::Texture("./sceneGraph/textures/tankBlue1.png");
	m_turretTexture = new aie::Texture("./sceneGraph/textures/barrelGreen.png");
	m_shieldTexture = new aie::Texture("./sceneGraph/textures/overshield.png");
	
	m_turret = new SpriteNode(m_turretTexture);
	m_turret->Translate(Vector2(0, 0));
	m_turret->SetOrigin(Vector2(0.25f, 0.5f));

	m_shield = new SpriteNode(m_shieldTexture);
	m_shield->Translate(Vector2(0, 0));

	m_base = new SpriteNode(m_tankBaseTexture);
	m_base->Rotate(3.14159f / 4.0f); // 90 degrees

	m_turret->SetParent(m_base);
	m_shield->SetParent(m_base);
	m_base->SetParent(this);
	m_shield->SetSize(Vector2{320.f, 320.f});

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
	aie::Input* input = aie::Input::getInstance();
}

void Tank::Render(aie::Renderer2D *renderer)
{
	m_base->Render(renderer);
	m_turret->Render(renderer);
	m_shield->Render(renderer);
}

void Tank::SetTurretRotate(float p_radians)
{
	float bRads = m_base->GetLocalRotation();
	//float rotationary = m_turret->setLocalMatrix(p_radians - bRads);
	m_turret->setLocalMatrix(p_radians - bRads);
}

void Tank::SetShieldRotate(float p_radians)
{
	p_radians = p_radians + 1.5 * 0.0174533;
	m_shield->Rotate(p_radians);
}

void Tank::SetBaseRotate(float p_radians)
{
	m_base->setLocalMatrix(p_radians);
}

void Tank::SetBaseTranslate(Vector2 p_move)
{
	m_base->Translate(p_move);
}

float Tank::GetBaseRotate()
{
	return m_base->GetLocalRotation();
}
