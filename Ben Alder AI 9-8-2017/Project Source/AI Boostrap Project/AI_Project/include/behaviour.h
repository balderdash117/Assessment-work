#pragma once

class GameObject;

namespace aie
{
	class Renderer2D;
}

class behaviour
{
public:

	behaviour() : m_isOwned(true) {}
	virtual ~behaviour() {}

	virtual void	update(GameObject *obj, float deltaTime) {}
	virtual void	draw(GameObject *obj, aie::Renderer2D *renderer) {}

	bool			isOwnedByGameObject() { return m_isOwned; }
	void			isOwnedByGameObject(bool isOwned) { m_isOwned = isOwned; }

protected:

	bool			m_isOwned;

private:
};

