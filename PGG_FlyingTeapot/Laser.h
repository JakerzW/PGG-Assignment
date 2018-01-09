#pragma once
#include "GameObject.h"
#include "Player.h"

class Laser : public GameObject
{
	public:
		Laser(Player *player);
		~Laser();

		virtual void Update(float deltaTs);

	protected:
		float _velocity;
		Material *laserMaterial;
		Mesh *laserMesh;
};
