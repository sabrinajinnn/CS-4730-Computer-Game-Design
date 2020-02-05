/*
Sabrina Baldassarre
sjb4sy
1/28/2020
AffineTransformation.cpp
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "MyGame.h"

using namespace std;

// not sure where to create new display objects 
// and make them children of the root 
MyGame::MyGame() : Game(1200, 1000){
	character = new DisplayObject("character","./resources/character/Idle_1.png");
	//earth = new DisplayObject("character", "./resources/character/earth.png");
}

MyGame::~MyGame(){
	delete character;
}

void MyGame::update(set<SDL_Scancode> pressedKeys){
	for (SDL_Scancode key : pressedKeys) {
		switch(key) {
			// ARROW KEYS (UP, DOWN, LEFT, RIGHT)
			case SDL_SCANCODE_UP: // moves character up
				character->position.y -=1;
			break;

			case SDL_SCANCODE_DOWN: // moves character down
				character->position.y +=1;
			break;

			case SDL_SCANCODE_LEFT: // moves character left
				character->position.x-=1;
			break;

			case SDL_SCANCODE_RIGHT: // moves character right
				character->position.x +=1;
			break;


			// SCALE FROM PIVOT POINT (Q, W)
			case SDL_SCANCODE_Q:
				character->scaleX -=0.1;
				if (character->scaleX < 0) {
					character->scaleX = 0.1;
				}

				character->scaleY -=0.1;
				if (character->scaleY < 0) {
					character->scaleY = 0.1;
				}
			break;

			case SDL_SCANCODE_W:
				character->scaleX +=0.1;
				if (character->scaleX < 0) {
					character->scaleX = 0.1;
				}

				character->scaleY +=0.1;
				if (character->scaleY < 0) {
					character->scaleY = 0.1;
				}

			break;


			// MOVE PIVOT POINT (I, J, K, L)
			case SDL_SCANCODE_I:
				character->pivot.y -=1;
			break;

			case SDL_SCANCODE_K:
				character->pivot.y +=1;
			break;

			case SDL_SCANCODE_J:
				character->pivot.x -=1;
			break;

			case SDL_SCANCODE_L:
				character->pivot.x +=1;
			break;


			// ROTATION (A, S)
			case SDL_SCANCODE_A: // rotate clockwise
				character->rotation +=1;
			break;

			case SDL_SCANCODE_S: // rotate counter-clockwise
				character->rotation -=1;
			break;

			
			// FADING (Z, X)
			case SDL_SCANCODE_Z: // fade in
				if (character->alpha > 254) {
					character->alpha = 255;
				}
				else {
					character->alpha +=1;
				}

			break;

			case SDL_SCANCODE_X: // fade out
				character->alpha -=1;
				if (character->alpha < 1) {
					character->alpha = 0;
				}
				else {
					character->alpha -=1;
				}
			break;


			// VISIBILITY (P)
			case SDL_SCANCODE_P: // makes character visible or invisible
				character->visible = !character->visible;
			break;
		}
	}
	Game::update(pressedKeys);
}

void MyGame::draw(AffineTransform &at){
	Game::draw(at);

	SDL_RenderClear(Game::renderer);
	character->draw(at);
	SDL_RenderPresent(Game::renderer);
}
