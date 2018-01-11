#include "Stars.h"

Stars::Stars()
{
	starsMaterial = new Material();
	starsMaterial->LoadShaders("VertShader.txt", "StarsFragShader.txt");
	starsMaterial->SetDiffuseColour(glm::vec3(1.0f, 1.0f, 1.0f));
	starsMaterial->SetSpecularColour(glm::vec3(1.0f, 1.0f, 1.0f));
	starsMaterial->SetTexture("Stars.bmp");
	starsMaterial->SetLightPosition(_lightPosition);
	SetMaterial(starsMaterial);
	starsMesh = new Mesh();
	starsMesh->LoadOBJ("Stars.obj");
	SetMesh(starsMesh);
	SetPosition(100.0f, 0.0f, 0.0f);
	_velocity = 0.3f;
}

Stars::~Stars()
{
	// Delete all the materials and meshes used by the stars
	delete starsMaterial;
	delete starsMesh;
}

void Stars::Update(float deltaTs)
{
	// Reset the position to give the effect of infinite stars
	if (GetPosition().x < -100.0f)
	{
		SetPosition(100.0f, 0.0f, 0.0f);
	}

	_position += glm::vec3(-1.0f, 0.0f, 0.0f) * _velocity;

	_modelMatrix = glm::translate(glm::mat4(1), _position);
	_invModelMatrix = glm::inverse(_modelMatrix);
}
