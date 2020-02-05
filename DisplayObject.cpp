/*
Sabrina Baldassarre
sjb4sy
1/28/2020
AffineTransformation.cpp
*/

#include "DisplayObject.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game.h"
#include <iostream>
#include <algorithm>

DisplayObject::DisplayObject() {
	image = NULL;
	texture = NULL;
	curTexture = NULL;
}

DisplayObject::DisplayObject(string id, string filepath) {
	this->id = id;
	this->imgPath = filepath;

	loadTexture(filepath);
}

DisplayObject::DisplayObject(string id, int red, int green, int blue) {
	isRGB = true;
	this->id = id;

	this->red = red;
	this->blue = blue;
	this->green = green;

	this->loadRGBTexture(red, green, blue);
}

DisplayObject::~DisplayObject() {
	//TODO: Get this freeing working
	if(image != NULL) SDL_FreeSurface(image);
	if(texture != NULL) SDL_DestroyTexture(texture);
	
}

void DisplayObject::loadTexture(string filepath) {
	image = IMG_Load(filepath.c_str());
	texture = SDL_CreateTextureFromSurface(Game::renderer, image);
	setTexture(texture);
}

void DisplayObject::loadRGBTexture(int red, int green, int blue){
	image = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0x000000ff);
	SDL_FillRect(image, NULL, SDL_MapRGB(image->format, red, green, blue));
	texture = SDL_CreateTextureFromSurface(Game::renderer, image);
	SDL_SetTextureBlendMode( texture, SDL_BLENDMODE_BLEND );
	setTexture(texture);
}

void DisplayObject::setTexture(SDL_Texture* t) {
	this->curTexture = t;
}

double DisplayObject::dist(SDL_Point &a, SDL_Point &b) { // distance formula
	return sqrt(pow(b.x-a.x,2.0)+pow(b.y-a.y,2.0));
} 

void DisplayObject::applyTransformations(AffineTransform &at) { 
	at.translate(position.x, position.y); 
	at.rotate(rotation * (M_PI/180.0));
	at.scale(scaleX, scaleY);	
}

void DisplayObject::reverseTransformations(AffineTransform &at) {		
	at.scale((1.0/scaleX),(1.0/scaleY));
	at.rotate(-rotation * (M_PI/180.0));			
	at.translate(-position.x, -position.y); 	

}

double DisplayObject::calcRotation(SDL_Point &left, SDL_Point &right) { 	// Get global angle between 2 points.
	return (atan2(left.y-right.y, left.x - right.x)); 
}

void DisplayObject::update(set<SDL_Scancode> pressedKeys) {
}

void DisplayObject::draw(AffineTransform &at) {
	if(visible && curTexture != NULL)  {

		applyTransformations(at); 
		at.translate(-pivot.x, -pivot.y);


		SDL_Point origin = at.transformPoint(0,0); 
		SDL_Point topRight = at.transformPoint(image->w, 0); 
		SDL_Point bottomRight = at.transformPoint(image->w, image->h); 

		SDL_Rect dstrect = { origin.x, origin.y, (int) dist(origin, topRight), (int) dist(topRight, bottomRight) };
		SDL_Point pivot2;
		pivot2.x=0; pivot2.y=0;

		SDL_RendererFlip flip = SDL_FLIP_NONE;
		
		SDL_SetTextureAlphaMod(curTexture, alpha);
		SDL_RenderCopyEx(Game::renderer, curTexture, NULL, &dstrect, calcRotation(topRight, origin) * 180.0 / 3.14159, &pivot2, flip);
	
		at.translate(pivot.x, pivot.y);	

		reverseTransformations(at);
	}
}