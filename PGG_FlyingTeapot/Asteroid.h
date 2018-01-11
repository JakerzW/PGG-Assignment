#pragma once

#include "GameObject.h"
#include <GLM/gtc/quaternion.hpp>

class Asteroid : public GameObject
{
	public:
		Asteroid();
		~Asteroid();

		virtual void Update(float deltaTs);

		float GetRoll();
		glm::quat GetOrientation();
		bool GetDestructable();

	protected:
		float _velocity = 0.05f;
		glm::quat _orientation;
		glm::vec3 _originalFacingDir;
		glm::vec3 _originalLeftDir;

		float _roll;
		float _horizontalPos;
		float _verticalPos;

		Material *asteroidMaterial;
		Mesh *asteroidMesh;

		bool _destructable;
};