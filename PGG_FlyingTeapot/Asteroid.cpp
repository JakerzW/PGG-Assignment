#include "Asteroid.h"
#include <time.h>

Asteroid::Asteroid()
{
	asteroidMaterial = new Material();
	asteroidMaterial->LoadShaders("VertShader.txt", "FragShader.txt");
	asteroidMaterial->SetDiffuseColour(glm::vec3(1.0f, 1.0f, 1.0f));
	asteroidMaterial->SetTexture("Asteroid.bmp");
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
	// Delete all materials and meshes used by the asteroid (setting to null to avoid double deletion errors)
	asteroidMaterial = NULL;
	delete asteroidMaterial;
	SetMaterial(NULL);
	delete _material;
	asteroidMesh = NULL;
	delete asteroidMesh;
	SetMesh(NULL);
	delete _mesh;

	SetPosition(NULL, NULL, NULL);
}
//
//void Asteroid::ChangeRoll(float value)
//{
//
//}
//
//void Asteroid::ChangeHorizontalPos(float value)
//{
//
//}
//
//void Asteroid::ChangeVerticalPos(float value)
//{
//
//}

void Asteroid::IncreaseVelocity(float newVelocity)
{
	_velocity += newVelocity;
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
	_position += glm::vec3(-1.0f, 0.0f, 0.0f) * _velocity;

	_modelMatrix = glm::translate(glm::mat4(1), _position);
	_invModelMatrix = glm::inverse(_modelMatrix);
}
