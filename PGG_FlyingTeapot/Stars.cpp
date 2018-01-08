#include "Stars.h"

Stars::Stars()
{
	Material *starsMaterial = new Material();
	starsMaterial->LoadShaders("VertShader.txt", "FragShader.txt");
	starsMaterial->SetDiffuseColour(glm::vec3(1.0f, 1.0f, 1.0f));
	starsMaterial->SetTexture("Stars.bmp");
	starsMaterial->SetLightPosition(_lightPosition);
	SetMaterial(starsMaterial);
	Mesh *starsMesh = new Mesh();
	starsMesh->LoadOBJ("Stars.obj");
	SetMesh(starsMesh);
}

Stars::~Stars()
{

}

void Stars::Update(float deltaTs)
{
	_modelMatrix = glm::translate(glm::mat4(1), _position);
	_invModelMatrix = glm::inverse(_modelMatrix);
}
