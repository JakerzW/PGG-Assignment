#include "Scene.h"

#include <iostream>
#include <SDL/SDL.h>

#define PI 3.14159265358979323846;
#define PI_2 1.57079632679489661923;

Scene::Scene()
{
	_cameraAngleX = 1.5f, _cameraAngleY = PI_2;

	// Set up the viewing matrix
	// This represents the camera's orientation and position
	_viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0,0,-3.5f) );

	// Set up a projection matrix
	_projMatrix = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);

	// Position of the light, in world-space
	_lightPosition = glm::vec3(0,10,0);

	// Create a game object
	// This needs a material and a mesh
	// Create the material for the game object
	// Shaders are now in files
	// Create the material for the game object
	// Shaders are now in files
	// The mesh is the geometry for the object
	// Load from OBJ file. This must have triangulated geometry
	//modelMesh->LoadOBJ("spaceship.obj"); 
	
	// Create a new game object for the player
	_player = new Player();
	//// Create a material for the player
	//Material *shipMaterial = new Material();
	//// Load the shaders for the player's material
	//shipMaterial->LoadShaders("VertShader.txt", "FragShader.txt");
	//// Set the basic colour for the material (Use 1,1,1 to just use the texture colour)
	//shipMaterial->SetDiffuseColour(glm::vec3(1.0, 1.0, 1.0));
	//// Set the texture for the material
	//shipMaterial->SetTexture("SpaceShip.bmp");
	//// Set the lights position for the material
	//shipMaterial->SetLightPosition(_lightPosition);
	//// Assign the material to the game object
	//_player->SetMaterial(shipMaterial);
	//// Create a mesh for the player
	//Mesh *shipMesh = new Mesh();
	//// Load the obj file for the model
	//shipMesh->LoadOBJ("SpaceShip.obj");
	//// Set the mesh loaded from the obj file to the game object
	//_player->SetMesh(shipMesh);
	//// Set the position of the game object in the scene
	//_player->SetPosition(0.0f, 50.0f, 0.0f);

	// Create and set up the stars
	_stars = new Stars();
	/*Material *starsMaterial = new Material();
	starsMaterial->LoadShaders("VertShader.txt", "FragShader.txt");
	starsMaterial->SetDiffuseColour(glm::vec3(1.0f, 1.0f, 1.0f));
	starsMaterial->SetTexture("Stars.bmp");
	starsMaterial->SetLightPosition(_lightPosition);
	_stars->SetMaterial(starsMaterial);
	Mesh *starsMesh = new Mesh();
	starsMesh->LoadOBJ("Stars.obj");
	_stars->SetMesh(starsMesh);
	//_stars->SetPosition(100.0f, 0.0f, 0.0f); // x should be from -100 to 100*/

	//Create and set up an asteroid
	/*_asteroid = new Asteroid();
	Material *asteroidMaterial = new Material();
	asteroidMaterial->LoadShaders("VertShader.txt", "FragShader.txt");
	asteroidMaterial->SetDiffuseColour(glm::vec3(1.0f, 1.0f, 1.0f));
	asteroidMaterial->SetTexture("Asteroid.bmp");
	asteroidMaterial->SetLightPosition(_lightPosition);
	_asteroid->SetMaterial(asteroidMaterial);
	Mesh *asteroidMesh = new Mesh();
	asteroidMesh->LoadOBJ("Asteroid.obj");
	_asteroid->SetMesh(asteroidMesh);
	_asteroid->SetPosition(10.0f, 50.0f, 0.0f);

	//Create and set up an laser
	_laser = new Laser(_player);
	Material *laserMaterial = new Material();
	laserMaterial->LoadShaders("VertShader.txt", "FragShader.txt");
	laserMaterial->SetDiffuseColour(glm::vec3(1.0f, 1.0f, 1.0f));
	laserMaterial->SetTexture("Laser.bmp");
	laserMaterial->SetLightPosition(_lightPosition);
	_laser->SetMaterial(laserMaterial);
	Mesh *laserMesh = new Mesh();
	laserMesh->LoadOBJ("Laser.obj");
	_laser->SetMesh(laserMesh);
	_laser->SetPosition(_player->GetPosition().x + 1, _player->GetPosition().y, _player->GetPosition().z);*/

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
	// You should neatly clean everything up here
}

void Scene::Update(float deltaTs, std::vector<Laser*> allLasers, std::vector<Asteroid*> allAsteroids)
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
			//delete allAsteroids.at(i);
			//allAsteroids.erase(allAsteroids.begin() + i);

			allAsteroids.at(i)->~Asteroid();
		}
	}

	// Update all the lasers in the scene and delete any that are off screen
	for (size_t i = 0; i < allLasers.size(); i++)
	{
		allLasers.at(i)->Update(deltaTs);
		if (allLasers.at(i)->GetPosition().x > 20)
		{
			allLasers.at(i)->~Laser();
			//allLasers.pop_back();
		}
	}

	// Check for collisions between the lasers and asteroids
	bool collision = false;
	for (size_t a = 0; a < allAsteroids.size(); a++)
	{
		
		float distanceBetweenAP = glm::distance(_player->GetPosition(), allAsteroids.at(a)->GetPosition());
		float minDistance = (_player->GetSize() + allAsteroids.at(a)->GetSize());
		if (distanceBetweenAP < minDistance)
		{
			// Destroy player and asteroid upon collision and end the game
			_player->~Player();
			allAsteroids.at(a)->~Asteroid();
			_gameStatus = false;
			break;
		}

		for (size_t l = 0; l < allLasers.size(); l++)
		{
			//if collision, break loop and destroy laser and asteroid
			float distanceBetweenAL = glm::distance(allLasers.at(l)->GetPosition(), allAsteroids.at(a)->GetPosition());

			// If the distance between the points is less than the radius of thea asteroid, the objects must have collided
			if (distanceBetweenAL < allAsteroids.at(a)->GetSize())
			{
				allLasers.at(l)->~Laser();
				//allLasers.erase(allLasers.begin() + l);
				if (allAsteroids.at(a)->GetDestructable())
				{
					allAsteroids.at(a)->~Asteroid();
					//allAsteroids.erase(allAsteroids.begin() + a);
					collision = true;
				}
				
				break;
			}
		}
		
	}
	if (collision)
	{
		_numberDestroyed++;
	}
}

void Scene::Draw(std::vector<Laser*> allLasers, std::vector<Asteroid*> allAsteroids)
{
	// Draw the objects, giving them the camera's position and projection
	_stars->Draw(_viewMatrix,_projMatrix);
	_player->Draw(_viewMatrix,_projMatrix);

	if (allAsteroids.size() > 0)
	{
		for (size_t i = 0; i < allAsteroids.size(); i++)
		{
			allAsteroids.at(i)->Draw(_viewMatrix, _projMatrix);
		}
	}

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



