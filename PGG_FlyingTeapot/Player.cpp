#include "Player.h"

Player::Player()
{
	// Load the shaders for the player's material
	shipMaterial->LoadShaders("VertShader.txt", "FragShader.txt");
	// Set the basic colour for the material (Use 1,1,1 to just use the texture colour)
	shipMaterial->SetDiffuseColour(glm::vec3(1.0, 1.0, 1.0));
	// Set the texture for the material
	shipMaterial->SetTexture("SpaceShip.bmp");
	// Set the lights position for the material
	shipMaterial->SetLightPosition(_lightPosition);
	// Assign the material to the game object
	SetMaterial(shipMaterial);	
	// Load the obj file for the model
	shipMesh->LoadOBJ("SpaceShip.obj");
	// Set the mesh loaded from the obj file to the game object
	SetMesh(shipMesh);
	// Set the position of the game object in the scene
	SetPosition(0.0f, 50.0f, 0.0f);

	// Set the initial roll
	_roll = 0.0f;	
	
	// Initialise with direction object is facing
	_originalFacingDir = glm::vec3(1, 0, 0);
	_originalLeftDir = glm::vec3(0, 0, -1);

	// Give it an initial velocity, otherwise it falls out the sky
	_velocity = glm::vec3(15.0f,0,0);

	// Set the size of the player for collision purposes
	_size = 0.8f;
}

Player::~Player()
{
	delete shipMaterial;
	delete shipMesh;
}

void Player::ChangeRoll(float value)
{
	_roll = value;
}

void Player::ChangeHorizontalPos(float value)
{
	_horizontalPos = value;
}

void Player::ChangeVerticalPos(float value)
{
	_verticalPos = value;
}

float Player::GetRoll()
{
	return _roll;
}

glm::quat Player::GetOrientation()
{
	return _orientation;
}

void Player::Update( float deltaTs )
{
	// _roll and _pitch are like 'commands'
	// Need to work out the current requested change in roll and pitch, based on these
	// The magic numbers at the end are the maximum rates of turn

	// Set the current roll and the horizontal and vertical positions
	float currentRoll = _roll * deltaTs * 1.2f;
	float currentHorizontalPos = _horizontalPos * deltaTs;
	float currentVerticalPos = _verticalPos * deltaTs;

	// Set the roll of the model around the facing direction
	_orientation = glm::angleAxis(currentRoll, _originalFacingDir) *_orientation;

	// Update position of model in the forward direction using the thrust value
	_position += _originalFacingDir * currentVerticalPos;
	_position += _originalLeftDir * currentHorizontalPos;

	// Move the model to it's new position
	_modelMatrix = glm::translate(glm::mat4(1), _position) * glm::mat4_cast(_orientation);
	_invModelMatrix = glm::inverse(_modelMatrix);
}