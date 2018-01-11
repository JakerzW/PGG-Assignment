#include "Asteroid.h"
#include <time.h>

Asteroid::Asteroid()
{
	asteroidMaterial = new Material();
	asteroidMaterial->LoadShaders("VertShader.txt", "FragShader.txt");
	asteroidMaterial->SetDiffuseColour(glm::vec3(1.0f, 1.0f, 1.0f));
	// Use the random number generator to give the asteroid a one in three chance of being an indestructable/dark asteroid
	if ((rand() % 3 + 1) == 1)
	{
		// If it is a dark asteroid, change the texture and set the destructable value to false
		asteroidMaterial->SetTexture("Asteroid2.bmp");
		_destructable = false;
	}
	else
	{
		asteroidMaterial->SetTexture("Asteroid.bmp");
		_destructable = true;
	}	
	asteroidMaterial->SetLightPosition(_lightPosition);
	SetMaterial(asteroidMaterial);
	asteroidMesh = new Mesh();
	asteroidMesh->LoadOBJ("Asteroid.obj");
	SetMesh(asteroidMesh);

	// Set the position to be random across the z axis (the x axis on screen)	
	float _zPos = (rand() / (float)RAND_MAX * 14) - 7;
	SetPosition(30.0f, 50.0f, _zPos);
	_size = 1.0f;
}

Asteroid::~Asteroid()
{
	// Delete the material and mesh
	delete asteroidMaterial;
	delete asteroidMesh;
}

float Asteroid::GetRoll()
{
	return _roll;
}

glm::quat Asteroid::GetOrientation()
{
	return _orientation;
}

bool Asteroid::GetDestructable()
{
	return _destructable;
}

void Asteroid::Update(float deltaTs)
{
	// Update the position of the asteroid by moving it in the direction of movement and moving it by the velocity amount
	_position += glm::vec3(-1.0f, 0.0f, 0.0f) * _velocity;

	_modelMatrix = glm::translate(glm::mat4(1), _position);
	_invModelMatrix = glm::inverse(_modelMatrix);
}
