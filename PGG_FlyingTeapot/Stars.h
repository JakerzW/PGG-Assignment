#pragma once

#include "GameObject.h"

class Stars : public GameObject
{
	public:
		Stars();
		~Stars();

		virtual void Update(float deltaTs);

	protected:
		float _velocity;

		Material *starsMaterial;
		Mesh *starsMesh;
};
