#include "vector.h"
#ifndef GEOMETRY_H
#define GEOMETRY_H
class Material
{
	public: 
		bool isLight;
		bool reflective;
		bool refractive;
		bool specular;
		bool diffuse;
		Color color;
		Material(){color = Color(1, 0, 0); reflective = 0; refractive = 0; 
				specular = 0; diffuse = 0; isLight = 0;}
		Material(bool light, bool refl, bool refr, bool spec, bool diff, Color col)
				{isLight = light; reflective = refl; refractive = refr; specular = spec;
					diffuse = diff; color = col;}
};

class RayHit{
	public:
		float tNear;
		float tFar;
		Material material;
		int intersect; // 0 if no intersect, 1 if a sphere, 2 if a triangle
		Vector normal;
		Vector location;
		Ray incomingRay;
		RayHit(){intersect = 0; tNear = 10000;}
		RayHit(float t, float t1, Material mat, Vector norm, Vector loc, Ray inCome, int sect)
		{
			tNear = t;
			tFar = t1;
			material = mat;
			normal = norm;
			location = loc;
			incomingRay = inCome;
			intersect = sect;
		}
};

/*
	Abstract shape class
*/
class Shape
{
	public:
		Vector vertA, vertB, vertC;
		Vector pos;
		Material mat;
		virtual RayHit intersect(Ray) = 0;
		virtual void print() = 0;
		virtual Vector newLightPos() = 0;
};

/*
	Sphere class

	Inherits from Shape
*/
class Sphere : public Shape
{
	public:
		// float radius;
		Sphere(){}
		Sphere(Vector p, float r, Material m){pos = p; radius = r; mat = m;}
		RayHit intersect(Ray ray);
		void print(){printf("Sphere\nPosition: "); pos.print();printf("radius: %f\n", radius);}
		Vector newLightPos(){
			return pos;// + (drand48()*(radius + radius) - (radius));
		}
	private:
		float radius;
};

/*
	Triangle - composed of three vectors

	Inherits from Shape

	The 'pos' in Triangle is explicitly used for calculating the 
	position of the light
*/
class Triangle : public Shape
{
	public:
		Triangle(Vector in1, Vector in2, Vector in3){vertA = in1; vertB = in2; vertC = in3;}
		Triangle(Vector in1, Vector in2, Vector in3, Material m){
			vertA = in1; vertB = in2; vertC = in3; mat = m; 
			pos = vertC + (vertB-vertC)*0.25 + (vertA-vertC)*0.25;
		}
		RayHit intersect(Ray ray);
		void print(){printf("Triangle:\nPosition: ");vertA.print();vertB.print();vertC.print();}
		Vector newLightPos(){
			float randomX = drand48()/2.0;
			float randomY = drand48()/2.0;
			return vertA + (vertB - vertA)*randomX + (vertC - vertA)*randomY;;
		}
};
#endif