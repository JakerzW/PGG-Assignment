#ifndef __PLAYER__
#define __PLAYER__

#include <GLM/gtc/quaternion.hpp>
#include "GameObject.h"

class Player : public GameObject
{
	public:
		Player();
		~Player();
	
		virtual void Update( float deltaTs );
	
		void ChangeRoll(float value);
		void ChangeHorizontalPos(float value);
		void ChangeVerticalPos(float value);
	
		float GetRoll();
		glm::quat GetOrientation();
	
	protected:
		glm::vec3 _velocity;
		glm::quat _orientation;
		glm::vec3 _originalFacingDir;
		glm::vec3 _originalLeftDir;

		float _roll;
		float _horizontalPos;
		float _verticalPos;
};

#endif
