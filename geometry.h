#include <cmath>
#include "ray.h"

class Material
{
	public: 
		bool reflective;
		bool specular;
		bool diffuse;
		Color color;
		Material(){color = Color(0, 0, 0); reflective = 0; specular = 0; diffuse = 0;}
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