#pragma once

#include <Matrix3.h>
#include <Vector2.h>

namespace aie
{
	class Renderer2D;
}

class Node
{
public:

	Node();
	virtual ~Node();

	virtual void Update(float dt);
	virtual void Render(aie::Renderer2D *renderer);

	void SetParent(Node *parent);

	Matrix3& GetTransform();
	Matrix3 CalculateGlobalTransform() const;

	void Translate(const Vector2 &pos);
	void Rotate(float radians);

	Vector2 GetLocalPosition();
	float GetLocalRotation();

	// WARNING:
	// Expensive -- does a lot of things
	Vector2 GetGlobalPosition();
	float GetGlobalRotation();

protected:

	Node *m_parent = nullptr;
	Matrix3 m_local; // defaults to identity

private:
};