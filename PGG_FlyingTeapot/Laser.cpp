#include "Laser.h"

Laser::Laser(Player *player)
{
	laserMaterial = new Material();
	laserMaterial->LoadShaders("VertShader.txt", "StarsFragShader.txt");
	laserMaterial->SetDiffuseColour(glm::vec3(1.0f, 1.0f, 1.0f));
	laserMaterial->SetTexture("Laser.bmp");
	laserMaterial->SetLightPosition(_lightPosition);
	SetMaterial(laserMaterial);
	laserMesh = new Mesh();
	laserMesh->LoadOBJ("Laser.obj");
	SetMesh(laserMesh);
	SetPosition(player->GetPosition().x + 1, player->GetPosition().y, player->GetPosition().z);
	_velocity = 0.25f;
}

Laser::~Laser()
{
	// Delete all materials and meshes used by the laser (setting to null to avoid double deletion errors)
	delete laserMaterial;
	delete laserMesh;
}

void Laser::Update(float deltaTs)
{
	_position += glm::vec3(1.0f, 0.0f, 0.0f) * _velocity;

	_modelMatrix = glm::translate(glm::mat4(1), _position);
	_invModelMatrix = glm::inverse(_modelMatrix);
}
