/*
Sabrina Baldassarre
sjb4sy
1/28/2020
AffineTransformation.cpp
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>
#include "AffineTransform.h"
#include <iostream>


/**
 * Affine Transforms
 * 
 * */	
AffineTransform::AffineTransform(){
	transform = identity();
}

AffineTransform::~AffineTransform(){
	cleanMatrix(transform);
}

void AffineTransform::cleanMatrix(double** m){
	for(int i=0; i<3; i++)
		delete m[i];
	delete m;
}

/* Returns the identity matrix as an array */ 
double** AffineTransform::identity(){
	double** id = new double*[3];
	for(int i=0; i<3; i++){
		id[i] = new double[3];
		for(int j=0; j<3; j++){
			if(i == j) id[i][j] = 1.0;
			else id[i][j] = 0.0;
		}
	}
	return id;
}

/* Takes a point in the local coordinate system and transforms it to global space given this AffineTransform */ 
SDL_Point AffineTransform::transformPoint(int x, int y){
	SDL_Point temp;

	int xCord = (transform[0][0] * x) + (transform[0][1] * y) + transform[0][2] * 1;
	int yCord = (transform[1][0] * x) + (transform[1][1] * y) + transform[1][2] * 1;

	temp = {xCord, yCord};
	return temp;
}

/* Add another transform to this one, is basically just matrix multiply */
void AffineTransform::concatenate(AffineTransform &at) {
	double** mult = identity();

	for(int i=0; i < 3; i++){
		for(int j=0; j< 3; j++){
			double tot = 0.0;
			for(int pos=0; pos < 3; pos++){
				tot += transform[i][pos] * at.transform[pos][j];
			}
			mult[i][j] = tot;
		}
	}

	for (int i=0; i< 3; i++){
		for (int j=0; j<3; j++){
			transform[i][j] = mult[i][j];
		}
	}
	
	cleanMatrix(mult);
}

/* Move points in the x and y direction */
void AffineTransform::translate(int x, int y) {
	AffineTransform temp;
	temp.transform[0][2] = x;
	temp.transform[1][2] = y;
	concatenate(temp);
}

/* rotate points by r radians */
void AffineTransform::rotate(double r){
	AffineTransform temp;
	temp.transform[0][0] = cos(r);
	temp.transform[0][1] = -sin(r); 
	temp.transform[1][0] = sin(r);
	temp.transform[1][1] = cos(r);
	concatenate(temp);
}

/* scale in the x and y direction accordingly */
// creating a new matrix then concatenate to 
void AffineTransform::scale(double x, double y) {
	AffineTransform temp; 
	temp.transform[0][0] = x;
	temp.transform[1][1] = y;
	concatenate(temp);
}

double AffineTransform::getScaleX(){
	return sqrt((transform[0][0] * transform[0][0]) + (transform[0][1] * transform[0][1]));
}

double AffineTransform::getScaleY(){
	return sqrt((transform[1][0] * transform[1][0]) + (transform[1][1] * transform[1][1]));
}