#include "geometry.h"

RayHit Sphere::intersect(Ray ray){
	// calculate where the vector is pointing
	Vector direction = ray.direction;

	// formaulation of quadratic formula
	float b = direction.dot(ray.origin - pos);
	float a = direction.dot(direction);
	float c = ( (ray.origin - pos).dot(ray.origin - pos) ) - (radius*radius);
	
	// calculate discriminant
	float disc = (b * b) - (a * c);

	// calculate time vector hit
	float t0 = (-b - sqrt(disc)) / a;
	float t1 = (-b + sqrt(disc)) / a;

	// return a RayHit object
	if(disc >= 0){
		// calculate location of hit
		Vector location = (ray.direction * t0) + ray.origin;
		
		// calculate normal
		Vector normal = location - pos;
		normal.normalize();

		// return RayHit object
		return RayHit(t0, t1, mat, normal, location, ray, 1);
	}
	else return RayHit();
}

RayHit Triangle::intersect(Ray ray){
	// barycentric coordinates
	float A = vertA.x - vertB.x;
	float B = vertA.y - vertB.y;
	float C = vertA.z - vertB.z;
	float D = vertA.x - vertC.x;
	float E = vertA.y - vertC.y;
	float F = vertA.z - vertC.z;
	float G = ray.direction.x;
	float H = ray.direction.y;
	float I = ray.direction.z;
	float J = vertA.x - ray.origin.x;
	float K = vertA.y - ray.origin.y;
	float L = vertA.z - ray.origin.z;

	// calculate M
	float M = ( A * ( (E*I) - (H*F) ) ) + ( B * ( (G*F) - (D*I) ) ) + ( C * ( (D*H) - (E*G) ) );

	// calculate t -- if it's less than 0, return no hit
	float t =  -1 * ( ( F * ( (A*K) - (J*B) ) ) + ( E * ( (J*C) - (A*L) ) ) + ( D * ( (B*L) - (K*C) ) ) ) / M;
	if(t < 0) return RayHit();

	// calculate gamma -- if it isnt between 0 & 1, return no hit
	float gamma = ( ( I * ( (A*K) - (J*B) ) ) + ( H * ( (J*C) - (A*L) ) ) + ( G * ( (B*L) - (K*C) ) ) ) / M;
	if(gamma < 0 || gamma > 1) return RayHit();

	// calculate beta -- if it isnt between 0 and (1-gamma), return no hit
	float beta = ( ( J * ( (E*I) - (H*F) ) ) + ( K * ( (G*F) - (D*I) ) ) + ( L * ( (D*H) - (E*G) ) ) ) / M;
	if(beta < 0 || beta > (1 - gamma)) return RayHit();

	//calculate location of hit
	Vector location = (ray.direction * t) + ray.origin;

	// calculate normal
	Vector normal = Vector(A,B,C).cross(Vector(D,E,F));
	normal.normalize();

	return RayHit(t, t, mat, normal, location, ray, 2);
}