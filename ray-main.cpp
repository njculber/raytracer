/*
	Raytracer program
	@author Neil Culbertson
	December 5, 2018
*/

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "perspective.h"
#include "geometry.h"
using namespace std;

// width & height of the image
const int width = 512;
const int height = 512;
unsigned char arrayContainingImage[width*height*3];

static int shapes;
Shape **shape;

Perspective per;
Shape *light;
Shape *light2;
float ambientShade;

/* set up the reference scene */
void setupReference(){
	shapes = 9;
	shape = new Shape*[shapes];

	/* make several materials to choose from */

				      // light  // reflective // refractive // specular // diffuse // color
	Material     refl(0,        1,            0,            0,          0,         Color(0,0,0));
	Material      red(0,        0,            0,            0,          1,         Color(1,0,0));
	Material     blue(0,        0,            0,            0,          1,         Color(0,0,1));
	Material    white(0,        0,            0,            0,          1,         Color(1,1,1));
	Material  redSpec(0,        0,            0,            1,          1,         Color(1,0,0));

	// create sphere & triangles
	shape[0] = new Sphere(Vector(0,0,-16),   2, refl);
	shape[1] = new Sphere(Vector(3,-1,-14),  1, refl);
	shape[2] = new Sphere(Vector(-3,-1,-14), 1, redSpec);
	shape[3] = new Triangle(Vector(-8,-2,-20), Vector(8,-2,-20), Vector(8,10,-20), blue);
	shape[4] = new Triangle(Vector(-8,-2,-20), Vector(8,10,-20), Vector(-8,10,-20), blue);
	shape[5] = new Triangle(Vector(-8,-2,-20), Vector(8, -2, -10), Vector(8,-2,-20), white);
	shape[6] = new Triangle(Vector(-8,-2,-20), Vector(-8,-2,-10), Vector(8, -2,-10), white);
	shape[7] = new Triangle(Vector(8,-2,-20), Vector(8, -2,-10), Vector(8,10,-20), red);

	// set up light
	Material lightMat(1, 0, 0, 0, 0, Color(1,1,1));
	light = new Sphere(Vector(3,5,-15), 0.25, lightMat);
	light2 = new Sphere(Vector(3,5,-15), 0.25, lightMat);
	shape[8] = light;
	ambientShade = 0.2;

	// set up perspective projection
	per = Perspective(
		Vector(0,0,0), // position of camera
		-2, 			// distance camera is from screen
		2, 				// world width
		2,              // world height
		width,          // world width in pixels
		height);		// world height in pixels
}

/* set up the custom scene */
void setupCustom(){
	shapes = 49;
	shape = new Shape*[shapes];

	/* make several materials to choose from */ 

				      // light  // reflective // refractive // specular // diffuse // color
	Material     refl(0,        1,            0,            0,          0,         Color(0,0,0));
	Material      red(0,        0,            0,            1,          1,         Color(1,0,0));
	Material     blue(0,        0,            0,            1,          1,         Color(0,0,1));
	Material    white(0,        0,            0,            0,          1,         Color(1,1,1));
	Material  redSpec(0,        0,            0,            1,          1,         Color(1,0,0));
	Material   indigo(0,        0,            0,            1,          1,         Color(0.29,0,0.51));
	Material   violet(0,        0,            0,            1,          1,         Color(0.5,0,0.5));
	Material    green(0,        0,            0,            1,          1,         Color(0,1,0));
	Material   orange(0,        0,            0,            1,          1,         Color(1,0.62,0));
	Material   yellow(0,        0,            0,            1,          1,         Color(1,1,0));
	Material     grey(0,        0,            0,            0,          1,         Color(0.4,0.4,0.4));
	Material greySpec(0,        0,            0,            1,          1,         Color(0.4,0.4,0.4));

	// create some spheres
	shape[0] =  new Sphere(Vector(0,-3.5,-15), 		1, 		refl);
	shape[1] =  new Sphere(Vector(0,-4.5,-12), 		0.5, 	green);
	shape[2] =  new Sphere(Vector(1.75,-4.5,-13), 	0.5, 	blue); 
	shape[3] =  new Sphere(Vector(2.5,-4.5,-15), 	0.5, 	indigo);
	shape[4] =  new Sphere(Vector(-2.5,-4.5,-15), 	0.5, 	orange);
	shape[5] =  new Sphere(Vector(-1.75,-4.5,-13), 	0.5, 	yellow);
	shape[6] =  new Sphere(Vector(1.5,-4.5,-17), 	0.5, 	violet);
	shape[7] =  new Sphere(Vector(-1.5,-4.5,-17), 	0.5, 	red);
	shape[8] =  new Sphere(Vector(-6,1.2,-18), 		0.75, 	greySpec);
	shape[9] =  new Sphere(Vector(6,1.2,-18), 		0.75, 	greySpec);
	shape[10] = new Sphere(Vector(-3,-1.8,-19.5), 	0.2 , 	green);
	shape[11] = new Sphere(Vector(3,-1.8,-19.5), 	0.2, 	green);
	shape[12] = new Sphere(Vector(0,-0.3,-19.5), 	0.2, 	green);
	shape[13] = new Sphere(Vector(-3.5,-1.8,-19.5), 0.2, 	red);
	shape[14] = new Sphere(Vector(2.5,-1.8,-19.5), 	0.2, 	red);
	shape[15] = new Sphere(Vector(-0.5,-0.3,-19.5), 0.2, 	red);
	shape[16] = new Sphere(Vector(-2.5,-1.8,-19.5), 0.2, 	blue);
	shape[17] = new Sphere(Vector(3.5,-1.8,-19.5), 	0.2, 	blue);
	shape[18] = new Sphere(Vector(0.5,-0.3,-19.5), 	0.2, 	blue);

	// floor
	shape[19] = new Triangle(Vector(-8,-5,-20), Vector(8, -5, -10), Vector(8,-5,-20), grey);
	shape[20] = new Triangle(Vector(-8,-5,-20), Vector(-8,-5,-10), Vector(8, -5,-10), grey);

	// diamond left
	shape[21] = new Triangle(Vector(-5.8, -2,-17.5), Vector(-6.2,-2,-17.5), Vector(-6,-5,-18), white);
	shape[22] = new Triangle(Vector(-6,-5,-18), Vector(-5.8,-2,-18.5), Vector(-5.8, -2,-17.5), white);
	shape[23] = new Triangle(Vector(-6,0,-18), Vector(-6.2,-2,-17.5), Vector(-5.8, -2,-17.5), white);
	shape[24] = new Triangle(Vector(-5.8, -2,-17.5), Vector(-5.8,-2,-18.5), Vector(-6,0,-18), white);
	shape[25] = new Triangle(Vector(-6,0,-18), Vector(-6.2,-2,-18.5), Vector(-5.8, -2,-18.5), white);
	shape[26] = new Triangle(Vector(-5.8, -2,-18.5), Vector(-6.2,-2,-18.5), Vector(-6,-5,-18), white);

	// diamond right
	shape[27] = new Triangle(Vector(6,-5,-18), Vector(6.2,-2,-17.5), Vector(5.8, -2,-17.5), white);
	shape[28] = new Triangle(Vector(5.8, -2,-17.5), Vector(5.8,-2,-18.5), Vector(6,-5,-18), white);
	shape[29] = new Triangle(Vector(5.8, -2,-17.5), Vector(6.2,-2,-17.5), Vector(6,0,-18), white);
	shape[30] = new Triangle(Vector(6,0,-18), Vector(5.8,-2,-18.5), Vector(5.8, -2,-17.5), white);
	shape[31] = new Triangle(Vector(6,0,-18), Vector(6.2,-2,-18.5), Vector(5.8, -2,-18.5), white);
	shape[32] = new Triangle(Vector(5.8, -2,-18.5), Vector(6.2,-2,-18.5), Vector(6,-5,-18), white);

	// ceiling        
	shape[33] = new Triangle(Vector(8,5,-20), Vector(8, 5, -10), Vector(-8,5,-20), grey);
	shape[34] = new Triangle(Vector(8, 5,-10), Vector(-8,5,-10), Vector(-8,5,-20), grey);

	// back wall                    
	shape[35] = new Triangle(Vector(8,-5,-20), Vector(8, 5, -20), Vector(-8,-5,-20), grey);
	shape[36] = new Triangle(Vector(8, 5,-20), Vector(-8,5,-20), Vector(-8,-5,-20), grey);

	//side walls
	shape[37] = new Triangle(Vector(8,-5,-20), Vector(8, -5,-10), Vector(8,5,-20), grey);
	shape[38] = new Triangle(Vector(8,-5,-10), Vector(8, 5,-10),Vector(8,5,-20), grey);
	shape[39] = new Triangle(Vector(-8,5,-20), Vector(-8, -5,-10),Vector(-8,-5,-20), grey);
	shape[40] = new Triangle(Vector(-8,5,-20), Vector(-8, 5,-10), Vector(-8,-5,-10), grey);

	// shelves
	shape[41] = new Triangle(Vector(-4,-2,-19), Vector(-2, -2, -20), Vector(-4,-2,-20), white);
	shape[42] = new Triangle(Vector(-4,-2,-19), Vector(-2,-2,-19), Vector(-2, -2,-20), white);
	shape[43] = new Triangle(Vector(2,-2,-19), Vector(4, -2, -20), Vector(2,-2,-20), white);
	shape[44] = new Triangle(Vector(2,-2,-19), Vector(4,-2,-19), Vector(4, -2,-20), white);
	shape[45] = new Triangle(Vector(-1,-0.5,-19), Vector(1,-0.5, -20), Vector(-1,-0.5,-20), white);
	shape[46] = new Triangle(Vector(-1,-0.5,-19), Vector(1,-0.5,-19), Vector(1,-0.5,-20), white);

	// set up light                  // intensity & color
	Material lightMat(1, 0, 0, 0, 0, Color(1,1,1));
	light =  new Triangle(Vector(1,4.9,-16), Vector(1, 4.9,-14), Vector(-1,4.9,-16), lightMat);
	light2 = new Triangle(Vector(1,4.9,-14), Vector(-1,4.9,-14), Vector(-1,4.9,-16), lightMat);
	shape[47] = light;
	shape[48] = light2;
	ambientShade = 0.2;

	// set up perspective projection
	per = Perspective(
		Vector(0,0,0),  // position of camera
		-2, 			// distance camera is from screen
		2,				// width of the world
		2, 				// height of the world
		width,			// width of world in pixels
		height);		// height of world in pixels
}

/* Find the nearest intersection given a ray */
RayHit findNearest(Ray ray){
	RayHit hit, tempHit;

	// find nearest shape
	for(int i = 0; i < shapes; i += 1){
		tempHit = shape[i]->intersect(ray);
		if(tempHit.tNear < hit.tNear && tempHit.tNear > 0){
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

// calculate average amount of shadow
float shadowAvg(RayHit hit){
	int hits = 0;
	float shadowRays = 5;
	for(int i = 0; i < shadowRays; i += 1){
		// calculate direction to light
		Vector direction = light->newLightPos() - hit.location;
		// if(drand48() > 0.5) direction = light2->newLightPos() - hit.location;
		direction.normalize();

		// create new ray and bump it a little to prevent noise
		Ray newRay(hit.location, direction);
		newRay.origin = newRay.origin + (newRay.direction * 0.001);

		// see if we successfully hit the light
		if(findNearest(newRay).material.isLight) hits += 1;
	}

	return clamp((float)hits/shadowRays, ambientShade, 1);
}

// calculate specular shading
Color specular(RayHit hit){ if(!hit.material.specular) return Color(0,0,0);
	// find direction to light & camera
	Vector lightDir = light->pos - hit.location;
	Vector toCamera = hit.incomingRay.origin - hit.location;
	lightDir.normalize();
	toCamera.normalize();

	// calculate scalar
	Vector halfVector = (lightDir + toCamera) / (lightDir + toCamera).magnitude();
	float specular = hit.normal.dot(halfVector);

	specular = pow(specular, 180);
	return Color(specular, specular, specular);
}

// calculate diffuse & ambient shading
Color diffuse(RayHit hit){ if(!hit.material.diffuse) return Color(0,0,0);
	Vector lightDir = light->pos - hit.location;
	lightDir.normalize();
	float diffuse = lightDir.dot(hit.normal);
	diffuse = clamp(diffuse, ambientShade, 1);

	// return diffuse shading including amount of shadow
	return hit.material.color *= diffuse;
}

// calculate reflection vector
Vector reflect(Vector v, Vector n){
	return v - (n * (2 * v.dot(n)));
}

// trace ray - calculate reflection, diffuse, & specular
Color trace(Ray ray, int depth){
	if(depth >= 10) return Color(0,0,0);
	RayHit hit = findNearest(ray);

	// check reflective property
	if(hit.material.reflective){
		// create new reflection ray
		Vector reflectVector = reflect(hit.incomingRay.direction, hit.normal);
		reflectVector.normalize();
		Ray newRay = Ray(hit.location, reflectVector);
		newRay.origin += (newRay.direction * 0.0001);

		return trace(newRay, depth+1);
	}

	if(hit.material.isLight) return light->mat.color;

	return ((diffuse(hit) + specular(hit)) * shadowAvg(hit)) * light->mat.color;
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

	// start tracing
	for(int y = 0; y < height; y += 1){
		for(int x = 0; x < width; x += 1){

			int rays = 3; // NOTE: total rays sent is (rays^2)
			Color avgColor = Color(0, 0, 0);

			// trace
			for(int i = 1; i < rays+1; i += 1){
				for(int j = 1; j < rays+1; j += 1){
					Ray ray = per.getRay(x + (float)j/(rays+1), y + (float)i/(rays+1));
					avgColor += trace(ray, 0) ^ 2;	
				}
			}

			// calculate final color from all the rays and draw to pixel x, y
			arrayContainingImage[ (y*width*3) + (x*3)]      = (sqrt(avgColor.r/(rays*rays))) * 255;
			arrayContainingImage[((y*width*3) + (x*3)) + 1] = (sqrt(avgColor.g/(rays*rays))) * 255;
			arrayContainingImage[((y*width*3) + (x*3)) + 2] = (sqrt(avgColor.b/(rays*rays))) * 255;
		}
	}
	free(shape);

	// export PNG using data from array containing image
	stbi_write_png(fileName, width, height, 3, arrayContainingImage, width*3);
	return 0;
}