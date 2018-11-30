#include "perspective.h"

Perspective::Perspective(Vector camPos, Vector light, float dist, int worldWidth, int worldHeight, int pixelWidth, int pixelHeight){
	cameraPos = camPos;
	lightSource = light;
	distanceToScreen = dist;
	screenWidthWorld = worldWidth;
	screenHeightWorld = worldHeight;
	screenWidthPixels = pixelWidth;
	screenHeightPixels = pixelHeight;
}

Ray Perspective::getRay(int x, int y){
	float NDCx = (x + 0.5) / (float)screenWidthPixels;
	float NDCy = (y + 0.5) / (float)screenHeightPixels;

	float pixelX = (screenWidthWorld * NDCx) - 1;
	float pixelY = 1 - (screenHeightWorld * NDCy);

	// calculate direction
	Vector dir = Vector(pixelX, pixelY, distanceToScreen) - cameraPos;
	dir.normalize();

	// calculate position
	Vector pos = cameraPos;

	// return the ray
	Ray newRay(pos, dir);
	return newRay;
}