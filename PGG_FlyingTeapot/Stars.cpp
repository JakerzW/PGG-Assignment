#include "Stars.h"

Stars::Stars()
{
	
}

Stars::~Stars()
{

}

void Stars::Update(float deltaTs)
{
	_modelMatrix = glm::translate(glm::mat4(1), _position);
	_invModelMatrix = glm::inverse(_modelMatrix);
}
