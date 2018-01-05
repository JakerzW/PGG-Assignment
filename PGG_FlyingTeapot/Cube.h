#pragma once
#include <SDL\SDL.h>
#include "glew.h"

class Cube
{
	public:
		Cube();
		~Cube();
		void Draw();

	protected:
		GLuint _VAO;
		unsigned int _numVertices;
};