#pragma once
#include "GameObject.h"

class Laser : public GameObject
{
	public:
		Laser();
		~Laser();

		virtual void Update(float deltaTs);

	protected:

};
