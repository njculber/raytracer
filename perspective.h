#include "vector.h"

#ifndef PERSP_H
#define PERSP_H
class Perspective
{
	public:
		Vector cameraPos;
		float distanceToScreen;
		int screenWidthWorld;
		int screenHeightWorld;
		int screenWidthPixels;
		int screenHeightPixels;
		Perspective(){}
		Perspective(Vector camPos, float dist, int worldWidth, 
					int worldHeight, int pixelWidth, int pixelHeight){
			cameraPos = camPos;
			distanceToScreen = dist;
			screenWidthWorld = worldWidth;
			screenHeightWorld = worldHeight;
			screenWidthPixels = pixelWidth;
			screenHeightPixels = pixelHeight;
		}
		Ray getRay(float x, float y){
			float NDCx = x / (float)screenWidthPixels;
			float NDCy = y / (float)screenHeightPixels;

			float pixelX = (screenWidthWorld * NDCx) - 1;
			float pixelY = 1 - (screenHeightWorld * NDCy);

			// calculate direction
			Vector direction = Vector(pixelX, pixelY, distanceToScreen) - cameraPos;
			direction.normalize();

			return Ray(cameraPos, direction);
		}
};
#endif