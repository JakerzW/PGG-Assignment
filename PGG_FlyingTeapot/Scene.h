#include "Player.h"
#include "Stars.h"
#include "Asteroid.h"
#include "Laser.h"

// The GLM library contains vector and matrix functions and classes for us to use
// They are designed to easily work with OpenGL!
#include <GLM/glm.hpp> // This is the main GLM header
#include <GLM/gtc/matrix_transform.hpp> // This one lets us use matrix transformations
#include <GLM/gtc/type_ptr.hpp> // This one gives us access to a utility function which makes sending data to OpenGL nice and easy
#include <GLM/gtc/quaternion.hpp>

#include <string>
#include <vector>

// The scene contains objects, the camera and light
// It is responsible for coordinating these things
class Scene
{
public:

	
	// Currently the scene is set up in the constructor
	// This means the object(s) are loaded, given materials and positions as well as the camera and light
	Scene();
	~Scene();

	// Use these to adjust the camera's orientation
	// Camera is currently set up to rotate about the world-space origin NOT the camera's origin
	void ChangeCameraAngleX( float value ) { _cameraAngleX += value; }
	void ChangeCameraAngleY( float value ) { _cameraAngleY += value; }

	// Calls update on all objects in the scene
	void Update(float deltaTs, std::vector<Laser*> allLasers, std::vector<Asteroid*> allAsteroids);

	// Draws the scene from the camera's point of view
	void Draw(std::vector<Laser*> allLasers, std::vector<Asteroid*> allAsteroids);

	bool GetGameStatus();

	int GetNumberDestroyed();

	Player* GetPlayer() {return _player;}


protected:

	// Currently one object, this could be a list of objects!
	GameObject *_model;
	Stars *_stars;
	Player *_player;
	Asteroid *_asteroid;
	Laser *_laser;

	bool _gameStatus;

	int _numberDestroyed = 0;
		
	// This matrix represents the camera's position and orientation
	glm::mat4 _viewMatrix;
	
	// This matrix is like the camera's lens
	glm::mat4 _projMatrix;

	// Current rotation information about the camera
	float _cameraAngleX, _cameraAngleY;

	// Position of the single point-light in the scene
	glm::vec3 _lightPosition;

	glm::quat _cameraOrientation;


};
