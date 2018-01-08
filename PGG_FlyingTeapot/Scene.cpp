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
	_projMatrix = glm::perspective(45.0f, 1.0f, 0.1f, 10000.0f);

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
	// Create a material for the player
	Material *shipMaterial = new Material();
	// Load the shaders for the player's material
	shipMaterial->LoadShaders("VertShader.txt", "FragShader.txt");
	// Set the basic colour for the material (Use 1,1,1 to just use the texture colour)
	shipMaterial->SetDiffuseColour(glm::vec3(1.0, 1.0, 1.0));
	// Set the texture for the material
	shipMaterial->SetTexture("Asteroid.bmp");
	// Set the lights position for the material
	shipMaterial->SetLightPosition(_lightPosition);
	// Assign the material to the game object
	_player->SetMaterial(shipMaterial);
	// Create a mesh for the player
	Mesh *shipMesh = new Mesh();
	// Load the obj file for the model
	shipMesh->LoadOBJ("Ship.obj");
	// Set the mesh loaded from the obj file to the game object
	_player->SetMesh(shipMesh);
	// Set the position of the game object in the scene
	_player->SetPosition(0.0f, 50.0f, 0.0f);

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
	_stars->SetMesh(starsMesh);*/
	//_stars->SetPosition(100.0f, 0.0f, 0.0f); // x should be from -100 to 100

	//Create and set up an asteroid
	_asteroid = new Asteroid();
	/*Material *asteroidMaterial = new Material();
	asteroidMaterial->LoadShaders("VertShader.txt", "FragShader.txt");
	asteroidMaterial->SetDiffuseColour(glm::vec3(1.0f, 1.0f, 1.0f));
	asteroidMaterial->SetTexture("Asteroid.bmp");
	asteroidMaterial->SetLightPosition(_lightPosition);
	_asteroid->SetMaterial(asteroidMaterial);
	Mesh *asteroidMesh = new Mesh();
	asteroidMesh->LoadOBJ("Asteroid.obj");
	_asteroid->SetMesh(asteroidMesh);
	_asteroid->SetPosition(10.0f, 50.0f, 0.0f);*/

	//Create and set up an laser
	_laser = new Laser();
	Material *laserMaterial = new Material();
	laserMaterial->LoadShaders("VertShader.txt", "FragShader.txt");
	laserMaterial->SetDiffuseColour(glm::vec3(1.0f, 1.0f, 1.0f));
	laserMaterial->SetTexture("Laser.bmp");
	laserMaterial->SetLightPosition(_lightPosition);
	_laser->SetMaterial(laserMaterial);
	Mesh *laserMesh = new Mesh();
	laserMesh->LoadOBJ("Laser.obj");
	_laser->SetMesh(laserMesh);
	//_laser->SetPosition(5.0f, 50.0f, 0.0f);
	_laser->SetPosition(_player->GetPosition().x + 1, _player->GetPosition().y, _player->GetPosition().z);

}

Scene::~Scene()
{
	// You should neatly clean everything up here
}

void Scene::Update( float deltaTs )
{
	// Update the game object (this is currently hard-coded to rotate)
	//_model->Update( deltaTs );
	_stars->Update(deltaTs);
	_player->Update(deltaTs);
	_asteroid->Update(deltaTs);
	_laser->Update(deltaTs);

	glm::vec3 playerPos = _player->GetPosition();
	glm::quat playerOrientation = _player->GetOrientation();


	// This updates the camera's position and orientation based on those of the player

	// Build the viewing matrix:
	_viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -5.0f, -15.0f)); // Provides offset away from player object
	_viewMatrix = glm::rotate(_viewMatrix,_cameraAngleX,glm::vec3(1,0,0)); // Allows player to rotate camera using player object as pivot
	_viewMatrix = glm::rotate(_viewMatrix,_cameraAngleY,glm::vec3(0,1,0));
	_viewMatrix = glm::translate( _viewMatrix, -glm::vec3(0.0f, 50.0f, 0.0f)); // Move to player's position
}

void Scene::Draw()
{
	// Draw that model, giving it the camera's position and projection
	//_model->Draw(_viewMatrix,_projMatrix);
	_stars->Draw(_viewMatrix,_projMatrix);
	_player->Draw(_viewMatrix,_projMatrix);
	_asteroid->Draw(_viewMatrix, _projMatrix);
	_laser->Draw(_viewMatrix, _projMatrix);


}



