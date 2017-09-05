#pragma once
#include "behaviour.h"

class KeyboardBehaviour : public behaviour
{
public:
					KeyboardBehaviour(int upkey = 0,int rightkey = 0,int downkey = 0,int leftkey = 0);
	virtual		   ~KeyboardBehaviour();

	virtual void	update(GameObject * object, float deltaTime);

	int				getUpKey();
	int				getRightKey();
	int				getDownKey();
	int				getLeftKey();

	void			setUpKey(int key);
	void			setRightKey(int key);
	void			setDownKey(int key);
	void			setLeftKey(int key);
protected:

	int				m_upkey;
	int				m_rightkey;
	int				m_downkey;
	int				m_leftkey;

	float			m_force;

private:
};