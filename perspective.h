#include <stdio.h>
#include "vector.h"
#include "ray.h"

#ifndef PERSP_H
#define PERSP_H
class Perspective
{
	public:
		Vector lightSource;
		Vector cameraPos;
		float distanceToScreen;
		int screenWidthWorld;
		int screenHeightWorld;
		int screenWidthPixels;
		int screenHeightPixels;
		Perspective(){}
		Perspective(Vector camPos, Vector light, float dist, int worldWidth, int worldHeight, int pixelWidth, int pixelHeight);
		Ray getRay(float, float);
};
#endif