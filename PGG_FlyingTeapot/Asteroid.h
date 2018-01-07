#pragma once
#include "GameObject.h"

class Asteroid : public GameObject
{
	public:
		Asteroid();
		~Asteroid();

		virtual void Update(float deltaTs);

	protected:

};