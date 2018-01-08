#include "Asteroid.h"

Asteroid::Asteroid()
{
	Material *asteroidMaterial = new Material();
	asteroidMaterial->LoadShaders("VertShader.txt", "FragShader.txt");
	asteroidMaterial->SetDiffuseColour(glm::vec3(1.0f, 1.0f, 1.0f));
	asteroidMaterial->SetTexture("Asteroid.bmp");
	asteroidMaterial->SetLightPosition(_lightPosition);
	SetMaterial(asteroidMaterial);
	Mesh *asteroidMesh = new Mesh();
	asteroidMesh->LoadOBJ("Asteroid.obj");
	SetMesh(asteroidMesh);
	SetPosition(30.0f, 50.0f, 0.0f);
	_velocity = 0.05f;
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
	_position += glm::vec3(-1.0f, 0.0f, 0.0f) * _velocity;

	_modelMatrix = glm::translate(glm::mat4(1), _position);
	_invModelMatrix = glm::inverse(_modelMatrix);
}
