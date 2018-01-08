#include "Player.h"

Player::Player()
{
	_roll = 0.0f;	
	
	// Initialise with direction object is facing
	_originalFacingDir = glm::vec3(1, 0, 0);
	_originalLeftDir = glm::vec3(0, 0, -1);

	// Give it an initial velocity, otherwise it falls out the sky
	_velocity = glm::vec3(15.0f,0,0);

}

Player::~Player()
{

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