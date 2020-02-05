/*
Sabrina Baldassarre
sjb4sy
1/28/2020
AffineTransformation.cpp
*/

#ifndef DISPLAYOBJECT_H
#define DISPLAYOBJECT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <set>
#include "AffineTransform.h"
#include <string>
#include <fstream>

using namespace std;

class DisplayObject {

public:
	string id = "DEFAULT_ID";
	string imgPath = "";
	int red,green,blue;
	string type = "DisplayObject";

	// Transform info
	SDL_Point position = {0,0};
	SDL_Point pivot = {0,0};
	double scaleX = 1;
	double scaleY = 1;
	double rotation = 0;
	
	// Dimensions of DisplayObject
	int width = 100; 
	int height = 100;

	bool isRGB = false;
	int alpha = 255; // Transparency [0,255]
	bool visible = true; // Whether or not to display

	DisplayObject();
	DisplayObject(string id, string path);
	DisplayObject(string id, int red, int green, int blue);
	virtual ~DisplayObject();
	
	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

	void loadTexture(string filepath);
	void loadRGBTexture(int red, int green, int blue);
	void setTexture(SDL_Texture* t);

	// Added functions
	double dist(SDL_Point &a, SDL_Point &b); // distance formula
	void applyTransformations(AffineTransform &at);
	void reverseTransformations(AffineTransform &at);
	double calcRotation(SDL_Point &left, SDL_Point &right); // Get global angle between 2 points.

private:
	
	SDL_Texture* texture = NULL;
	SDL_Surface* image = NULL;

	/* Texture currently being drawn. Equal to texture for normal DO */
	SDL_Texture* curTexture;
};

#endif