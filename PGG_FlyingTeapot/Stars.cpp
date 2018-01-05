#include "Stars.h"

Stars::Stars()
{
	_modelMatrix = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.5f, 0.0f)), glm::vec3(20.0f, 0.1f, 20.0f));
}

Stars::~Stars()
{

}

void Stars::Draw()
{
	_stars.Draw();
}
