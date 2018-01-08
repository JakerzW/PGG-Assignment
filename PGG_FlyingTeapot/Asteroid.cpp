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
	return _roll;
}

glm::quat Asteroid::GetOrientation()
{
	return _orientation;
}

void Asteroid::Update(float deltaTs)
{
	_modelMatrix = glm::translate(glm::mat4(1), _position);
	_invModelMatrix = glm::inverse(_modelMatrix);
}
