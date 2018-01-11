
// This is the main SDL include file
#include <SDL/SDL.h>

// I have added glew.h, wglew.h and glew.c to my VS project
// I find this the easiest way to include it
// To compile and link GLEW like this ('statically') you must add  GLEW_STATIC  into Configuration Properties -> C/C++ -> Preprocessor -> Preprocessor Definitions
#include "glew.h"
#include "GLM/ext.hpp"

#include "Scene.h"

// Include iostream so we can output error messages to console
#include <iostream>
#include <string>
#include <vector>

// An initialisation function, mainly for GLEW
// This will also print to console the version of OpenGL we are using
bool InitGL()
{
	// GLEW has a problem with loading core OpenGL
	// The temporary workaround is to enable its 'experimental' features
	glewExperimental = GL_TRUE;

	GLenum err = glewInit();
	if( GLEW_OK != err )
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		std::cerr<<"Error: GLEW failed to initialise with message: "<< glewGetErrorString(err) <<std::endl;
		return false;
	}
	std::cout<<"INFO: Using GLEW "<< glewGetString(GLEW_VERSION)<<std::endl;

	std::cout<<"INFO: OpenGL Vendor: "<< glGetString( GL_VENDOR ) << std::endl;
	std::cout<<"INFO: OpenGL Renderer: "<< glGetString( GL_RENDERER ) << std::endl;
	std::cout<<"INFO: OpenGL Version: "<< glGetString( GL_VERSION ) << std::endl;
	std::cout<<"INFO: OpenGL Shading Language Version: "<< glGetString( GL_SHADING_LANGUAGE_VERSION ) << std::endl;
	
	return true;
}

int main(int argc, char *argv[])
{
	// Initialise SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		// Something went very wrong in initialisation -> Exit the game
		std::cout<<"Whoops! Something went very wrong, cannot initialise SDL :("<<std::endl;
		return -1;
	}



	// This is how we set the context profile
	// We need to do this through SDL, so that it can set up the OpenGL drawing context that matches this
	// Set the version of OpenGL to 4.3
	// Major version number (4):
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );
	// Minor version number (3):
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
	// Then we say whether we want the core profile or the compatibility profile
	// Flag options are either: SDL_GL_CONTEXT_PROFILE_CORE   or   SDL_GL_CONTEXT_PROFILE_COMPATIBILITY
	// We'll go for the core profile
	// This means we are using the latest version and cannot use the deprecated functions
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );



	//Create the window: Set the size and any options for an SDL window, including the title
	int winPosX = 100;
	int winPosY = 100;
	int winWidth = 800;
	int winHeight = 800;
	SDL_Window *window = SDL_CreateWindow("Asteroids!",
		winPosX, winPosY,
		winWidth, winHeight,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	// Initialise the renderer
	SDL_Renderer * renderer = SDL_CreateRenderer( window, -1, 0 );
	
	// Create a context for the renderer
	SDL_GLContext glcontext = SDL_GL_CreateContext( window );

	// Call the initialisation function to set up GLEW and print GL info to console
	if( !InitGL() )
	{
		return -1;
	}
	
	// Store the number of milliseconds passed since SDL was initialised
	unsigned int lastTime = SDL_GetTicks();
		
	
	// Enable the depth test to make sure triangles in front are always in front no matter the order they are drawn
	glEnable(GL_DEPTH_TEST);

	// Create a scene to contain all the objects
	Scene myScene;

	// Initialise the booleans used for key presses
	bool cmdRotateLeft = false, cmdRotateRight = false, cmdRotateUp = false, cmdRotateDown = false;
	bool cmdRollLeft = false, cmdRollRight = false, cmdMoveForward = false, cmdMoveBackward = false, cmdThrustUp = false, cmdThrustDown = false;
	bool cmdShoot = false, cmdHasShot = false, cmdSlowDown = false;
	
	// Create the player
	// Look in Player.cpp to see how I'm creating game objects
	Player *mainPlayer = myScene.GetPlayer();

	// Create the vectors to store all of the lasers and asteroids of which there will be multiple
	std::vector<Laser*> allLasers;
	std::vector<Asteroid*> allAsteroids;

	// These variables will be used to manipulate how often a new asteroid is released into the game
	// Release time is the number of milliseconds in between each asteroid being released
	// Release time will be reduced as more asteroids are released to increase the difficulty of the game
	unsigned int releaseTime = 1000;
	unsigned int previousRelease = 0;

	// Number released is a counter for the amount of asteroids released in the game
	int numberReleased = 0;

	//Initialise the random number generator for use in setting the asteroids spawn point
	srand(time(NULL));

	// Set up the game loop - when gameStatus is false the game will end
	bool gameStatus = true;
	while(gameStatus)
	{
		// Get the gameStatus from the scene (this is where collisions are calculated and therefore dictate the gameStatus)
		gameStatus = myScene.GetGameStatus();

		// Don't carry on with the loop if the game should be exiting
		if (!gameStatus)
			break;

		// Set up an event to check for any user inputs
		SDL_Event incomingEvent;
		
		// Use poll event if there are any inputs in the queue
		while( SDL_PollEvent( &incomingEvent ) )
		{
			// Check which type of input is in the event
			switch( incomingEvent.type )
			{
			case SDL_QUIT:
				// If the user requests we exit, change the gameStatus to false
				gameStatus = false;
				break;				
			case SDL_KEYDOWN:
				// Check which key has been pressed
				// Change the boolean for the action to be performed by a certain key
				switch( incomingEvent.key.keysym.sym )
				{
					case SDLK_DOWN:
						// For example if we press the down arrow, we want the player to move backwards
						cmdMoveBackward = true;
						break;
					case SDLK_UP:
						cmdMoveForward = true;
						break;
					case SDLK_LEFT:
						cmdRollLeft = true;
						break;
					case SDLK_RIGHT:
						cmdRollRight = true;
						break;
					case SDLK_a:
						cmdRollLeft = true;
						break;
					case SDLK_d:
						cmdRollRight = true;
						break;
					case SDLK_w:
						cmdMoveForward = true;
						break;
					case SDLK_s:
						// We can also have two keys do the same thing (E.G. WASD and the arrow keys perform the same actions)
						cmdMoveBackward = true;
						break;
					case SDLK_PAGEUP:
						cmdThrustUp = true;
						break;
					case SDLK_PAGEDOWN:
						cmdThrustDown = true;
						break;
					case SDLK_LSHIFT:
						cmdSlowDown = true;
						break;
					case SDLK_SPACE:
						cmdShoot = true;
						break;
					case SDLK_ESCAPE:
						gameStatus = false;
						break;
				}
				break;
			
			case SDL_KEYUP:
				// Here we will check which key has been released
				// We will change the corresponding action to false to stop the action when a key has been released
				switch( incomingEvent.key.keysym.sym )
				{
					case SDLK_DOWN:
						cmdMoveBackward = false;
						break;
					case SDLK_UP:
						cmdMoveForward = false;
						break;
					case SDLK_LEFT:
						cmdRollLeft = false;
						break;
					case SDLK_RIGHT:
						cmdRollRight = false;
						break;
					case SDLK_a:
						cmdRollLeft = false;
						break;
					case SDLK_d:
						cmdRollRight = false;
						break;
					case SDLK_w:
						cmdMoveForward = false;
						break;
					case SDLK_s:
						cmdMoveBackward = false;
						break;
					case SDLK_PAGEUP:
						cmdThrustUp = false;
						break;
					case SDLK_PAGEDOWN:
						cmdThrustDown = false;
						break;
					case SDLK_LSHIFT:
						cmdSlowDown = false;
						break;
					case SDLK_SPACE:
					{
						cmdShoot = false;
						cmdHasShot = false;
						break;
					}
				}
				break;
			}
		}


		// Here we need to update our world

		// We are going to work out the time between each frame
		// First, find the current time using the GetTicks function
		unsigned int current = SDL_GetTicks();

		// Next, we want to work out the change in time between the previous frame and the current one
		// DeltaTs = Change in time in seconds
		float deltaTs = (float) (current - lastTime) / 1000.0f;

		// Now that we've done this we can use the current time as the next frame's previous time
		lastTime = current;


		// Now we need to use the input given by the user to control the actions in the game
		
		// Move and roll the player left and right if the move is valid (within the boundaries)
		if ((cmdRollLeft & !cmdRollRight) && (mainPlayer->GetPosition().z > -7))
		{
			// Check to see if the player wants to move the player slower (holding down the left shift key)
			if (cmdSlowDown)
			{
				mainPlayer->ChangeRoll(-0.5f);
				mainPlayer->ChangeHorizontalPos(10.0f);
			}
			// If not then just move the player at normal pace
			else
			{
				mainPlayer->ChangeRoll(-1.0f);
				mainPlayer->ChangeHorizontalPos(20.0f);
			}			
		}
		else if ((cmdRollRight &! cmdRollLeft) && (mainPlayer->GetPosition().z < 7))
		{
			if (cmdSlowDown)
			{
				mainPlayer->ChangeRoll(0.5f);
				mainPlayer->ChangeHorizontalPos(-10.0f);
			}
			else
			{
				mainPlayer->ChangeRoll(1.0f);
				mainPlayer->ChangeHorizontalPos(-20.0f);
			}			
		}
		else
		{
			// If no input has been made, make no action
			mainPlayer->ChangeRoll( 0.0f );
			mainPlayer->ChangeHorizontalPos(0.0f);
		}

		// Move forward or backward if the move is valid
		if ((cmdMoveForward & !cmdMoveBackward) && (mainPlayer->GetPosition().x < 3))
		{
			// Check if we need to move the player slower
			if (cmdSlowDown)
			{
				mainPlayer->ChangeVerticalPos(10.0f);
			}
			else
			{
				mainPlayer->ChangeVerticalPos(20.0f);
			}			
		}
		else if ((cmdMoveBackward & !cmdMoveForward) && (mainPlayer->GetPosition().x > -2.5))
		{
			if (cmdSlowDown)
			{
				mainPlayer->ChangeVerticalPos(-10.0f);
			}
			else
			{
				mainPlayer->ChangeVerticalPos(-20.0f);
			}			
		}
		// Do nothing if no action is made
		else
		{
			mainPlayer->ChangeVerticalPos(0.0f);
		}

		// If the player wants to shoot and has not shot already before releasing the spacebar
		// This ensures the player only shoots once per button press
		if (cmdShoot & !cmdHasShot)
		{
			cmdHasShot = true;
			// Create a new laser and add it to the vector
			Laser *laser = new Laser(mainPlayer);
			allLasers.push_back(laser);
		}

		// Check if enough time has passed between the last time an asteroid to now
		if (current > (previousRelease + releaseTime))
		{
			//If yes, change the time for when an asteroid has been released to the current time
			previousRelease = current;
			// Reduce time between releases based on how many asteroids have been released
			if (numberReleased < 100)
			{
				releaseTime -= 7;
				numberReleased++;
			}
			// Create a new asteroid and add it to the vector
			Asteroid *asteroid = new Asteroid();
			allAsteroids.push_back(asteroid);			
		}

		// Update the scene
		myScene.Update(deltaTs, allLasers, allAsteroids);

		// Check that the game status is still valid
		if (!myScene.GetGameStatus())
		{
			// If not then we need to exit the loop before we draw
			gameStatus = false;
			break;
		}

		// Now we need to draw our world

		// Specify the colour to clear the framebuffer to
		glClearColor(0.0f,0.0f,0.0f,0.0f);
		// This writes the above colour to the colour part of the framebuffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw the scene
		myScene.Draw(allLasers, allAsteroids);

		// This tells the renderer to actually show its contents to the screen
		SDL_GL_SwapWindow( window );
		
		// Limiter in case we're running really quick
		if( deltaTs < (1.0f/50.0f) )
		{
			SDL_Delay((unsigned int) (((1.0f/50.0f) - deltaTs)*1000.0f) );
		}		
	}

	// If we get outside the main game loop, it means our user has requested we exit
	SDL_GL_DeleteContext( glcontext );
	SDL_DestroyWindow( window );
	SDL_Quit();

	return 0;
}
