#include <cmath>
#include "ray.h"

class Material
{
	public: 
		bool reflective;
		bool specular;
		Color color;
		void print();
};

class Sphere
{
	public:
		Material mat;
		Vector pos;
		float radius;
		RayHit intersect(Ray ray);
		void print();
};

class Triangle
{
	public:
		Material mat;
		Vector vertA, vertB, vertC;
		Triangle(){}
		Triangle(Vector, Vector, Vector);
		RayHit intersect(Ray ray);
		void print();
};