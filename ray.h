#include <stdio.h>
#include "vector.h"
#ifndef RAY_H
#define RAY_H
class Ray
{
	public:
		Vector origin;
		Vector direction;
		void print(){
			printf("origin: <%f %f %f>\nDirection: <%f %f %f>\n", 
			origin.x, origin.y, origin.z, direction.x, direction.y, direction.z);}
		Ray(){}
		Ray(Vector pos, Vector dir){origin = pos; direction = dir;}
};

class RayHit{
	public:
		float tNear;
		float tFar;
		bool reflective;
		bool specular;
		bool diffuse;
		int intersect; // 0 if no intersect, 1 if a sphere, 2 if a triangle
		Color color;
		Vector normal;
		Vector location;
		Ray incomingRay;
		RayHit(){intersect = 0; tNear = 10000;}
		RayHit(float t, float t1, bool refl, bool spec, bool dif, Color col, Vector norm, Vector loc, Ray inCome, int sect){
			tNear = t;
			tFar = t1;
			reflective = refl;
			specular = spec;
			diffuse = dif;
			color = col;
			normal = norm;
			location = loc;
			incomingRay = inCome;
			intersect = sect;
		}
};
#endif