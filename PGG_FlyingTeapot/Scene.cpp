
#include "Scene.h"

#define PI 3.14159265358979323846;
#define PI_2 1.57079632679489661923;

#include <iostream>
#include <SDL/SDL.h>



Scene::Scene()
{
	_cameraAngleX = 1.5f, _cameraAngleY = PI_2;

	// Set up the viewing matrix
	// This represents the camera's orientation and position
	_viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0,0,-3.5f) );

	// Set up a projection matrix
	_projMatrix = glm::perspective(45.0f, 1.0f, 0.1f, 10000.0f);

	// Position of the light, in world-space
	_lightPosition = glm::vec3(10,10,0);

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
	Material *teapotMaterial = new Material();
	// Load the shaders for the player's material
	teapotMaterial->LoadShaders("VertShader.txt", "FragShader.txt");
	// Set the basic colour for the material (Use 1,1,1 to just use the texture colour)
	teapotMaterial->SetDiffuseColour(glm::vec3(1.0, 1.0, 1.0));
	// Set the texture for the material
	teapotMaterial->SetTexture("FlyingTeapotColour.bmp");
	// Set the lights position for the material
	teapotMaterial->SetLightPosition(_lightPosition);
	// Assign the material to the game object
	_player->SetMaterial( teapotMaterial);
	// Create a mesh for the player
	Mesh *modelMesh = new Mesh();
	// Load the obj file for the model
	modelMesh->LoadOBJ("Ship.obj");
	//modelMesh->LoadOBJ("wingedTeapot.obj");
	// Set the mesh loaded from the obj file to the game object
	_player->SetMesh(modelMesh);
	// Set the position of the game object in the scene
	_player->SetPosition(0.0f, 50.0f, 0.0f);
	

	//// Create and set up the ground
	//_model = new GameObject();
	//Material *modelMaterial = new Material();
	//Mesh *groundMesh = new Mesh();
	//modelMaterial->LoadShaders("VertShader.txt", "FragShader.txt");
	//modelMaterial->SetDiffuseColour(glm::vec3(0.8, 0.1, 0.1));
	//modelMaterial->SetTexture("Stars.bmp");
	//modelMaterial->SetLightPosition(_lightPosition);
	//_model->SetMaterial(modelMaterial);
	//groundMesh->LoadOBJ("ground.obj");
	//_model->SetMesh(groundMesh);

	// Create and set up the stars
	_stars = new Stars();
	Material *starsMaterial = new Material();
	starsMaterial->LoadShaders("VertShader.txt", "FragShader.txt");
	starsMaterial->SetDiffuseColour(glm::vec3(1.0f, 1.0f, 1.0f));
	starsMaterial->SetTexture("Stars.bmp");
	starsMaterial->SetLightPosition(_lightPosition);
	_stars->SetMaterial(starsMaterial);
	Mesh *starsMesh = new Mesh();
	_stars->SetMesh(starsMesh);
	_stars->SetPosition(0.0f, 20.0f, 0.0f);


	//Create and set up an asteroid
	_asteroid = new Player();
	Material *asteroidMaterial = new Material();
	asteroidMaterial->LoadShaders("VertShader.txt", "FragShader.txt");
	asteroidMaterial->SetDiffuseColour(glm::vec3(1.0f, 1.0f, 1.0f));
	asteroidMaterial->SetTexture("FlyingTeapotColour.bmp");
	asteroidMaterial->SetLightPosition(_lightPosition);
	_asteroid->SetMaterial(asteroidMaterial);
	Mesh *asteroidMesh = new Mesh();
	asteroidMesh->LoadOBJ("Asteroid.obj");
	_asteroid->SetMesh(asteroidMesh);
	_asteroid->SetPosition(0.0f, 50.0f, 0.0f);

}

Scene::~Scene()
{
	// You should neatly clean everything up here
}

void Scene::Update( float deltaTs )
{
	// Update the game object (this is currently hard-coded to rotate)
	//_model->Update( deltaTs );

	_player->Update( deltaTs );

	glm::vec3 playerPos = _player->GetPosition();
	glm::quat playerOrientation = _player->GetOrientation();


	// This updates the camera's position and orientation based on those of the player

	// Build the viewing matrix:
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


}



