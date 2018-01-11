#include "Scene.h"

#include <iostream>
#include <SDL/SDL.h>

#define PI 3.14159265358979323846;
#define PI_2 1.57079632679489661923;

Scene::Scene()
{
	// Set the angles for the camera so it is in a top down position
	_cameraAngleX = 1.5f, _cameraAngleY = PI_2;

	// Set up the viewing matrix
	// This represents the camera's orientation and position
	_viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0,0,-3.5f) );

	// Set up a projection matrix
	_projMatrix = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);

	// Position of the light, in world-space
	_lightPosition = glm::vec3(0,10,0); 
	
	// Create a new game object for the player
	_player = new Player();

	// Create and set up the stars
	_stars = new Stars();

	// Build the viewing matrix:
	_viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -5.0f, -15.0f)); // Provides offset away from player object
	_viewMatrix = glm::rotate(_viewMatrix, _cameraAngleX, glm::vec3(1, 0, 0)); // Rotates camera into position
	_viewMatrix = glm::rotate(_viewMatrix, _cameraAngleY, glm::vec3(0, 1, 0));
	_viewMatrix = glm::translate(_viewMatrix, -glm::vec3(0.0f, 50.0f, 0.0f)); // Move to player's position

	// Set the status of the game, if this is ever false, the game will end
	_gameStatus = true;
}

Scene::~Scene()
{
	
}

void Scene::Update(float deltaTs, std::vector<Laser*> &allLasers, std::vector<Asteroid*> &allAsteroids)
{
	// Update the game objects
	_stars->Update(deltaTs);
	_player->Update(deltaTs);

	// Update all the asteroids on the screen and delete any that are off screen
	for (size_t i = 0; i < allAsteroids.size(); i++)
	{
		allAsteroids.at(i)->Update(deltaTs);
		if (allAsteroids.at(i)->GetPosition().x < -20)
		{
			delete allAsteroids.at(i);
			allAsteroids.erase(allAsteroids.begin() + i);
			i--;
		}
	}

	// Update all the lasers in the scene and delete any that are off screen
	for (size_t i = 0; i < allLasers.size(); i++)
	{
		allLasers.at(i)->Update(deltaTs);
		if (allLasers.at(i)->GetPosition().x > 20)
		{
			delete allLasers.at(i);
			allLasers.erase(allLasers.begin() + i);
			i--;				
		}
	}

	// Check for collisions between the lasers and asteroids
	bool collision = false;
	for (size_t a = 0; a < allAsteroids.size(); a++)
	{
		// Find the distance between the player and the current asteroid
		float distanceBetweenAP = glm::distance(_player->GetPosition(), allAsteroids.at(a)->GetPosition());
		// Find the minimum distance between the player and asteroid (any less than this and the player should be destroyed)
		float minDistance = (_player->GetSize() + allAsteroids.at(a)->GetSize());
		if (distanceBetweenAP < minDistance)
		{
			// Destroy player upon collision and end the game
			delete _player;
			_gameStatus = false;
			break;
		}

		// Go through all the lasers to check for collisions against the asteroids
		for (size_t l = 0; l < allLasers.size(); l++)
		{
			// If collision, break loop and destroy laser and asteroid
			// Get the distance between the current laser and the current asteroid
			float distanceBetweenAL = glm::distance(allLasers.at(l)->GetPosition(), allAsteroids.at(a)->GetPosition());
			// If the distance between the points is less than the radius of the asteroid, the objects must have collided
			if (distanceBetweenAL < allAsteroids.at(a)->GetSize())
			{
				delete allLasers.at(l);
				allLasers.erase(allLasers.begin() + l);
				if (l > 0) l--;
				// Only delete the asteroid if it can be destroyed
				if (allAsteroids.at(a)->GetDestructable())
				{
					delete allAsteroids.at(a);
					allAsteroids.erase(allAsteroids.begin() + a);
					if (a > 0) a--;
					collision = true;
				}
				break;
			}
		}
		
	}
	// Increment the number destroyed if there is a collision between a laser and a destructable asteroid
	if (collision)
	{
		_numberDestroyed++;
	}
}

void Scene::Draw(std::vector<Laser*> &allLasers, std::vector<Asteroid*> &allAsteroids)
{
	// Draw the objects, giving them the camera's position and projection
	// Draw the stars and player
	_stars->Draw(_viewMatrix,_projMatrix);
	_player->Draw(_viewMatrix,_projMatrix);

	// Draw all asteroids in the vector
	if (allAsteroids.size() > 0)
	{
		for (size_t i = 0; i < allAsteroids.size(); i++)
		{
			allAsteroids.at(i)->Draw(_viewMatrix, _projMatrix);
		}
	}

	// Draw all lasers in the vector
	if (allLasers.size() > 0)
	{
		for (size_t i = 0; i < allLasers.size(); i++)
		{
			allLasers.at(i)->Draw(_viewMatrix, _projMatrix);
		}
	}	
}

bool Scene::GetGameStatus()
{
	return _gameStatus;
}

int Scene::GetNumberDestroyed()
{
	return _numberDestroyed;
}



