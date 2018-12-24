/*
	Raytracer program
	@author Neil Culbertson
	December 5, 2018
*/

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "stb_image_write.h"
#include "perspective.h"
#include "geometry.h"
using namespace std;

const int dim = 512;
unsigned char arrayContainingImage[dim*dim*3];

Material refl;
Material red;
Material blue;
Material green;
Material orange;
Material yellow;
Material violet;
Material indigo;
Material white;
Material grey;
Material greyrefl;
Material liteBlue;
Material whiterefl;
Material redSpec;

int spheres;
int triangles;
Sphere *sphere;
Triangle *triangle;

Perspective per;
Vector light;
Vector cameraPosition;

/* set up the reference scene */
void setupReference(){
	spheres = 3;
	triangles = 5;
	sphere = (Sphere *)malloc(spheres * sizeof(Sphere));
	triangle = (Triangle *)malloc(triangles * sizeof(Triangle));

	// make a material which is reflective
	refl.reflective = 1;
	refl.color = Color(0, 0, 0);

	// make several diffuse materials to choose from
	red.reflective = 0;
	red.color = Color(1, 0, 0);
	red.diffuse = 1;
	blue.reflective = 0;
	blue.color = Color(0, 0, 1);
	blue.diffuse = 1;
	white.reflective = 0;
	white.color = Color(1, 1, 1);
	white.diffuse = 1;
	redSpec.diffuse = 1;
	redSpec.specular = 1;
	redSpec.color = Color(1, 0, 0);

	// create three spheres
	sphere[0].pos = Vector(0,0,-16);
	sphere[0].radius = 2;
	sphere[0].mat = refl;
	
	sphere[1].pos = Vector(3,-1,-14);
	sphere[1].radius = 1;
	sphere[1].mat = refl;
	
	sphere[2].pos = Vector(-3,-1,-14);
	sphere[2].radius = 1;
	sphere[2].mat = redSpec;

	// back wall
	triangle[0] = Triangle(Vector(-8,-2,-20), Vector(8,-2,-20), Vector(8,10,-20));
	triangle[0].mat = blue;
	
	triangle[1] = Triangle(Vector(-8,-2,-20), Vector(8,10,-20), Vector(-8,10,-20));
	triangle[1].mat = blue;

	// floor
	triangle[2] = Triangle(Vector(-8,-2,-20), Vector(8, -2, -10), Vector(8,-2,-20));
	triangle[2].mat = white;
                                  // vertB           // vertA           // vertC
	triangle[3] = Triangle(Vector(-8,-2,-20), Vector(-8,-2,-10), Vector(8, -2,-10));
	triangle[3].mat = white;

	// right red triangle
	triangle[4] = Triangle(Vector(8,-2,-20), Vector(8, -2,-10), Vector(8,10,-20));
	triangle[4].mat = red;

	// set up perspective projection
	cameraPosition = Vector(0, 0, 0);
	light = Vector(3, 5, -15);
	per = Perspective(
		cameraPosition, // position of camera
		light, 			// position of light
		-2, 			// distance camera is from screen
		2, 				// world width
		2,              // world height
		dim,            // world width in pixels
		dim);		    // world height in pixels
}

/* set up the custom scene */
void setupCustom(){
	spheres = 19;
	triangles = 30;
	sphere = (Sphere *)malloc(spheres * sizeof(Sphere));
	triangle = (Triangle *)malloc(triangles * sizeof(Triangle));

	// make several diffuse materials to choose from
	refl.reflective = 1;
	refl.color = Color(0, 0, 0);
	red.reflective = 0;
	red.color = Color(1, 0, 0);
	red.diffuse = 1;
	red.specular = 1;
	blue.reflective = 0;
	blue.color = Color(0, 0, 1);
	blue.diffuse = 1;
	blue.specular = 1;
	indigo.reflective = 0;
	indigo.color = Color(0.29, 0, 0.51);
	indigo.diffuse = 1;
	indigo.specular = 1;
	violet.reflective = 0;
	violet.color = Color(0.5, 0, 0.5);
	violet.diffuse = 1;
	violet.specular = 1;
	white.reflective = 0;
	white.color = Color(1, 1, 1);
	white.diffuse = 1;
	green.reflective = 0;
	green.color = Color(0, 0.75, 0);
	green.diffuse = 1;
	green.specular = 1;
	orange.reflective = 0;
	orange.color = Color(1, 0.75, 0);
	orange.diffuse = 1;
	orange.specular = 1;
	yellow.reflective = 0;
	yellow.color = Color(1, 1, 0);
	yellow.diffuse = 1;
	yellow.specular = 1;
	grey.reflective = 0;
	grey.color = Color(0.4, 0.4, 0.4);
	grey.diffuse = 1;

	// create spheres
	sphere[0].pos = Vector(0,-3.5,-15);
	sphere[0].radius = 1;
	sphere[0].mat = refl;

	sphere[3].pos = Vector(0,-4.5,-12);
	sphere[3].radius = 0.5;
	sphere[3].mat = green;
	
	sphere[1].pos = Vector(1.75,-4.5,-13);
	sphere[1].radius = 0.5;
	sphere[1].mat = blue;
	
	sphere[4].pos = Vector(2.5,-4.5,-15);
	sphere[4].radius = 0.5;
	sphere[4].mat = indigo;
	
	sphere[2].pos = Vector(-2.5,-4.5,-15);
	sphere[2].radius = 0.5;
	sphere[2].mat = orange;
	
	sphere[5].pos = Vector(-1.75,-4.5,-13);
	sphere[5].radius = 0.5;
	sphere[5].mat = yellow;

	sphere[6].pos = Vector(1.5,-4.5,-17);
	sphere[6].radius = 0.5;
	sphere[6].mat = violet;
	
	sphere[7].pos = Vector(-1.5,-4.5,-17);
	sphere[7].radius = 0.5;
	sphere[7].mat = red;

	sphere[8].pos = Vector(-6,1.2,-18);
	sphere[8].radius = 0.75;
	sphere[8].mat = white;

	sphere[9].pos = Vector(6,1.2,-18);
	sphere[9].radius = 0.75;
	sphere[9].mat = white;

	sphere[10].pos = Vector(-3,-1.8,-19.5);
	sphere[10].radius = 0.2;
	sphere[10].mat = green;

	sphere[11].pos = Vector(3,-1.8,-19.5);
	sphere[11].radius = 0.2;
	sphere[11].mat = green;

	sphere[12].pos = Vector(0,0.2,-19.5);
	sphere[12].radius = 0.2;
	sphere[12].mat = green;

	sphere[13].pos = Vector(-3.5,-1.8,-19.5);
	sphere[13].radius = 0.2;
	sphere[13].mat = red;

	sphere[14].pos = Vector(2.5,-1.8,-19.5);
	sphere[14].radius = 0.2;
	sphere[14].mat = red;

	sphere[15].pos = Vector(-0.5,0.2,-19.5);
	sphere[15].radius = 0.2;
	sphere[15].mat = red;

	sphere[16].pos = Vector(-2.5,-1.8,-19.5);
	sphere[16].radius = 0.2;
	sphere[16].mat = blue;

	sphere[17].pos = Vector(3.5,-1.8,-19.5);
	sphere[17].radius = 0.2;
	sphere[17].mat = blue;

	sphere[18].pos = Vector(0.5,0.2,-19.5);
	sphere[18].radius = 0.2;
	sphere[18].mat = blue;



	// floor                      // vertB           // vertC           // vertD
	triangle[0] = Triangle(Vector(-8,-5,-20), Vector(8, -5, -10), Vector(8,-5,-20));
	triangle[0].mat = grey;
                                  // vertB           // vertA           // vertC
	triangle[1] = Triangle(Vector(-8,-5,-20), Vector(-8,-5,-10), Vector(8, -5,-10));
	triangle[1].mat = grey;

	// diamond 1
	triangle[2] = Triangle(Vector(-5.8, -2,-17.5), Vector(-6.2,-2,-17.5), Vector(-6,-5,-18));
	triangle[2].mat = white;

	triangle[3] = Triangle(Vector(-6,-5,-18), Vector(-5.8,-2,-18.5), Vector(-5.8, -2,-17.5));
	triangle[3].mat = white;

	triangle[4] = Triangle(Vector(-6,0,-18), Vector(-6.2,-2,-17.5), Vector(-5.8, -2,-17.5));
	triangle[4].mat = white;

	triangle[5] = Triangle(Vector(-5.8, -2,-17.5), Vector(-5.8,-2,-18.5), Vector(-6,0,-18));
	triangle[5].mat = white;

	triangle[14] = Triangle(Vector(-6,0,-18), Vector(-6.2,-2,-18.5), Vector(-5.8, -2,-18.5));
	triangle[14].mat = white;

	triangle[15] = Triangle(Vector(-5.8, -2,-18.5), Vector(-6.2,-2,-18.5), Vector(-6,-5,-18));
	triangle[15].mat = white;

	// diamond 2
	triangle[6] = Triangle(Vector(6,-5,-18), Vector(6.2,-2,-17.5), Vector(5.8, -2,-17.5));
	triangle[6].mat = white;

	triangle[7] = Triangle(Vector(5.8, -2,-17.5), Vector(5.8,-2,-18.5), Vector(6,-5,-18));
	triangle[7].mat = white;

	triangle[8] = Triangle(Vector(5.8, -2,-17.5), Vector(6.2,-2,-17.5), Vector(6,0,-18));
	triangle[8].mat = white;

	triangle[9] = Triangle(Vector(6,0,-18), Vector(5.8,-2,-18.5), Vector(5.8, -2,-17.5));
	triangle[9].mat = white;

	triangle[16] = Triangle(Vector(6,0,-18), Vector(6.2,-2,-18.5), Vector(5.8, -2,-18.5));
	triangle[16].mat = white;

	triangle[17] = Triangle(Vector(5.8, -2,-18.5), Vector(6.2,-2,-18.5), Vector(6,-5,-18));
	triangle[17].mat = white;

	// ceiling                   // vertB           // vertC           // vertD
	triangle[10] = Triangle(Vector(8,5,-20), Vector(8, 5, -10), Vector(-8,5,-20));
	triangle[10].mat = grey;
                                  // vertC           // vertA           // vertB
	triangle[11] = Triangle(Vector(8, 5,-10), Vector(-8,5,-10), Vector(-8,5,-20));
	triangle[11].mat = grey;

	// back wall                    // vertB           // vertC           // vertD
	triangle[12] = Triangle(Vector(8,-5,-20), Vector(8, 5, -20), Vector(-8,-5,-20));
	triangle[12].mat = grey;
                                  // vertC           // vertA           // vertD
	triangle[13] = Triangle(Vector(8, 5,-20), Vector(-8,5,-20), Vector(-8,-5,-20));
	triangle[13].mat = grey;

	//side walls
	triangle[18] = Triangle(Vector(8,-5,-20), Vector(8, -5,-10), Vector(8,5,-20));
	triangle[18].mat = grey;

	triangle[19] = Triangle( Vector(8,-5,-10), Vector(8, 5,-10),Vector(8,5,-20));
	triangle[19].mat = grey;

	triangle[20] = Triangle(Vector(-8,5,-20), Vector(-8, -5,-10),Vector(-8,-5,-20));
	triangle[20].mat = grey;

	triangle[21] = Triangle(Vector(-8,5,-20), Vector(-8, 5,-10), Vector(-8,-5,-10));
	triangle[21].mat = grey;

	// light square
	triangle[22] = Triangle(Vector(1,4.9,-16), Vector(1, 4.9, -14), Vector(-1,4.9,-16));
	triangle[22].mat = white;
	                                 // vertC           // vertA           // vertB
	triangle[23] = Triangle(Vector(1, 4.9,-14), Vector(-1,4.9,-14), Vector(-1,4.9,-16));
	triangle[23].mat = white;

	// shelves                     // vertB           // vertC           // vertD
	triangle[24] = Triangle(Vector(-4,-2,-19), Vector(-2, -2, -20), Vector(-4,-2,-20));
	triangle[24].mat = white;
                                  // vertC           // vertA           // vertD
	triangle[25] = Triangle(Vector(-4,-2,-19), Vector(-2,-2,-19), Vector(-2, -2,-20));
	triangle[25].mat = white;

	triangle[26] = Triangle(Vector(2,-2,-19), Vector(4, -2, -20), Vector(2,-2,-20));
	triangle[26].mat = white;
                                  // vertC           // vertA           // vertD
	triangle[27] = Triangle(Vector(2,-2,-19), Vector(4,-2,-19), Vector(4, -2,-20));
	triangle[27].mat = white;

	triangle[28] = Triangle(Vector(-1,0,-19), Vector(1, 0, -20), Vector(-1,0,-20));
	triangle[28].mat = white;
                                  // vertC           // vertA           // vertD
	triangle[29] = Triangle(Vector(-1,0,-19), Vector(1,0,-19), Vector(1, 0,-20));
	triangle[29].mat = white;


	// set up perspective projection
	cameraPosition = Vector(0, 0, 0);
	light = Vector(0, 4.5, -15);
	per = Perspective(
		cameraPosition, // position of camera
		light, 			// position of light
		-2, 
		2,			// distance camera is from screen
		2, 				// size of the world
		dim,
		dim);			// size of world in pixels
}

/*
	find nearest object in the scene

	Will return RayHit object no matter what -- but will use
	the intersect flag and tNear data to determine which to use
*/
RayHit findNearest(Ray ray){
	RayHit hit, tempHit;

	// find closest sphere
	for(int i = 0; i < spheres; i += 1){
		tempHit = sphere[i].intersect(ray);
		if(tempHit.tNear < hit.tNear && tempHit.tNear >= 0){
			hit = tempHit;
		}
	}
	// find closest triangle
	for(int i = 0; i < triangles; i += 1){
		tempHit = triangle[i].intersect(ray);
		if(tempHit.tNear < hit.tNear && tempHit.tNear >= 0){
			hit = tempHit;
		}
	}

	return hit;
}

// restrain @value to be between @min & @max
float clamp(float value, float min, float max){
	if(value < min) return min;
	if(value > max) return max;
	return value;
}

// return 1 if we're in shadow -- 0 otherwise
int inShadow(RayHit hit){
	// calculate direction to light and magnitude
	Vector direction = light - hit.location;
	float mag = direction.magnitude();
	direction.normalize();

	Ray newRay(hit.location, direction);
	newRay.origin = newRay.origin + (newRay.direction * 0.0001);

	// check if closest object is between source of light
	if(findNearest(newRay).tNear < mag) return 1;

	return 0;
}

// calculate specular shading
Color specularScalar(RayHit hit){ if(!hit.specular) return Color(0,0,0);
	// find direction to light & camera
	Vector lightDir = light - hit.location;
	Vector toCamera = hit.incomingRay.origin - hit.location;
	lightDir.normalize();
	toCamera.normalize();

	// calculate scalar
	Vector halfVector = (lightDir + toCamera) / (lightDir + toCamera).magnitude();
	float specular = hit.normal.dot(halfVector);

	// check if we're in shadow, if so, return no color
	if(inShadow(hit)) return Color(0, 0, 0);

	specular = pow(specular, 180);
	return Color(specular, specular, specular);
}

// calculate diffuse shading
Color diffuseScalar(RayHit hit){ if(!hit.diffuse) return Color(0,0,0);
	Vector lightDir = light - hit.location;
	lightDir.normalize();
	float diffuse = lightDir.dot(hit.normal);
	diffuse = clamp(diffuse, 0.2, 1);

	// check if we're in shadow, if so, return ambient lighting
	if(inShadow(hit)) return hit.color *= 0.2;

	// otherwise, return diffuse shading
	return hit.color *= diffuse;
}

// calculate reflection vector
Vector reflect(Vector d, Vector n){
	return d - (n * (2 * d.dot(n)));
}

/* 
	recurse through reflection until we dont hit a reflective object

	return black once we've recursed 10 times
*/
Color calculateReflection(RayHit hit, int depth){ if(!hit.reflective) return Color(0,0,0);
	if(depth >= 10) return Color(0, 0, 0);

	RayHit tempHit;

	// get reflection vector
	Vector refl = reflect(hit.incomingRay.direction, hit.normal);
	refl.normalize();
	Ray reflRay(hit.location, refl);

	// bump ray
	reflRay.origin = reflRay.origin + (reflRay.direction * 0.0001);

	// find the nearest hit for both spheres & triangles
	tempHit = findNearest(reflRay);

	// if object isn't reflective -- return that color
	if(!tempHit.reflective) return diffuseScalar(tempHit) + specularScalar(tempHit);

	// otherwise recurse
	return calculateReflection(tempHit, depth+1);
}

int main(int argc, char *argv[]){
	(void)argc;
	char fileName[20];

	// set up the scene
	if(argv[1]){
		if(strcmp(argv[1], "reference") == 0){
			setupReference();
			strcpy(fileName, "reference.png");
		}
		else if(strcmp(argv[1], "custom") == 0){
			setupCustom();
			strcpy(fileName, "custom.png");
		}
		else{
			printf("Argument options: 'reference' or 'custom'\n");
			return 1;
		}
	} 
	else{
		setupCustom();
		strcpy(fileName, "custom.png");
	}

	// start drawing image
	for(int y = 0; y < dim; y += 1){
		for(int x = 0; x < dim; x += 1){

			int rays = 5; // total rays = rays ^ 2;
			Color avgColor = Color(0, 0, 0);

			for(int i = 1; i < rays+1; i += 1){
				for(int j = 1; j < rays+1; j += 1){

					// find nearest object in the scene
					RayHit hit = findNearest(per.getRay(x + (float)j/(rays+1), 
														y + (float)i/(rays+1)));

					avgColor += (calculateReflection(hit, 0) + diffuseScalar(hit) + specularScalar(hit)) ^ 2;			
				}
			}

			// calculate final color from all rays and draw
			arrayContainingImage[ (y*dim*3) + (x*3)]      = (sqrt(avgColor.r/(rays*rays))) * 255;
			arrayContainingImage[((y*dim*3) + (x*3)) + 1] = (sqrt(avgColor.g/(rays*rays))) * 255;
			arrayContainingImage[((y*dim*3) + (x*3)) + 2] = (sqrt(avgColor.b/(rays*rays))) * 255;
		}
	}

	stbi_write_png(fileName, dim, dim, 3, arrayContainingImage, dim*3);
	free(sphere);
	free(triangle);
	return 0;
}