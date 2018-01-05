#pragma once
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp> 
#include <GLM/gtc/type_ptr.hpp> 

#include "Cube.h"

class Stars
{
	public:
		Stars();
		~Stars();

		void Draw();

		glm::mat4 GetModelMatrix();

	protected:
		glm::mat4 _modelMatrix;
		Cube _stars;

};
