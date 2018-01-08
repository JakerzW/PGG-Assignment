#include "Asteroid.h"

Asteroid::Asteroid()
{

}

Asteroid::~Asteroid()
{

}

void Asteroid::ChangeRoll(float value)
{

}

void Asteroid::ChangeHorizontalPos(float value)
{

}

void Asteroid::ChangeVerticalPos(float value)
{

}

float Asteroid::GetRoll()
{
	return 0.0f;
}

glm::quat Asteroid::GetOrientation()
{
	return glm::quat();
}

void Asteroid::Update(float deltaTs)
{
	_modelMatrix = glm::translate(glm::mat4(1), _position);
	_invModelMatrix = glm::inverse(_modelMatrix);
}
