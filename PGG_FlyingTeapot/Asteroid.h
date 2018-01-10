#pragma once

#include "GameObject.h"
#include <GLM/gtc/quaternion.hpp>

class Asteroid : public GameObject
{
	public:
		Asteroid();
		~Asteroid();

		virtual void Update(float deltaTs);

		/*void ChangeRoll(float value);
		void ChangeHorizontalPos(float value);
		void ChangeVerticalPos(float value);*/
		void IncreaseVelocity(float newVelocity);

		float GetRoll();
		glm::quat GetOrientation();
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
};