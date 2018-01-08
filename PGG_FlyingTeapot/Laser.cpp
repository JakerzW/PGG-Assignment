#include "Laser.h"

Laser::Laser()
{

}

Laser::~Laser()
{

}

void Laser::Update(float deltaTs)
{
	_modelMatrix = glm::translate(glm::mat4(1), _position);
	_invModelMatrix = glm::inverse(_modelMatrix);
}
