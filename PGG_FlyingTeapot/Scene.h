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
class Scene
{
	public:	
		Scene();
		~Scene();

		// Use these to adjust the camera's orientation
		void ChangeCameraAngleX( float value ) { _cameraAngleX += value; }
		void ChangeCameraAngleY( float value ) { _cameraAngleY += value; }

		// Calls update on all objects in the scene
		void Update(float deltaTs, std::vector<Laser*> &allLasers, std::vector<Asteroid*> &allAsteroids);

		// Draws the scene from the camera's point of view
		void Draw(std::vector<Laser*> &allLasers, std::vector<Asteroid*> &allAsteroids);

		// Returns the gameStatus (used by main)
		bool GetGameStatus();

		// Returns the number of asteroids destroyed
		int GetNumberDestroyed();

		// Returns the player
		Player* GetPlayer() {return _player;}


	protected:
		// The background and player
		Stars *_stars;
		Player *_player;

		// Scene's version of the gameStatus boolean to pass back for collisions
		bool _gameStatus;

		// The number of asteroids destroyed
		int _numberDestroyed = 0;
		
		// This matrix represents the camera's position and orientation
		glm::mat4 _viewMatrix;
	
		// This matrix is like the camera's lens
		glm::mat4 _projMatrix;

		// Current rotation information about the camera
		float _cameraAngleX, _cameraAngleY;

		// Position of the single point-light in the scene
		glm::vec3 _lightPosition;

		// The orientation of the camera
		glm::quat _cameraOrientation;
};
