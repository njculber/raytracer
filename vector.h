#include <cmath>
using namespace std;

#ifndef VECTOR_H
#define VECTOR_H
class Vector 
{
	public:
		float x, y, z;
		Vector(){x = y = z = 0;}
		Vector(float xIn, float yIn, float zIn){x = xIn; y = yIn; z = zIn;}
		float magnitude(){return sqrt( (x*x) + (y*y) + (z*z) );}
		void normalize(){float magnitude = sqrt( (x*x) + (y*y) + (z*z) ); 
			x = x/magnitude; y = y/magnitude; z = z/magnitude;}
		float dot(Vector vec){return (x * vec.x) + (y * vec.y) + (z * vec.z);}
		void print(){printf("<%f %f %f>\n", x, y, z);}
		Vector cross(Vector vec){return 
			Vector( (y * vec.z) - (z * vec.y), (z * vec.x) - (x * vec.z), (x * vec.y) - (y * vec.x) );}
		Vector operator - (Vector vec){return Vector(x-vec.x, y-vec.y, z-vec.z);}
		Vector operator + (Vector vec){return Vector(x+vec.x, y+vec.y, z+vec.z);}
		Vector operator * (Vector vec){return Vector(x*vec.x, y*vec.y, z*vec.z);}
		Vector operator / (float in){return Vector(x/in, y/in, z/in);}
		Vector operator * (float in){return Vector(x*in, y*in, z*in);}
		Vector operator + (float in){return Vector(x+in, y+in, z+in);}
};

class Color
{
	public:
		float r, g, b;
		Color(){r = 0;g = 0;b = 0;}
		void print(){printf("< %f %f %f >\n", r, g, b);}
		float clamp(float v, float min, float max){if(v < min) return min;if(v > max) return max;return v;}
		Color(float red, float green, float blue){r = clamp(red, 0, 1); 
												  g = clamp(green, 0, 1); 
												  b = clamp(blue, 0, 1);}
		Color operator * (float in){return   Color(r *  in,    g *  in,    b *  in);}
		Color operator * (Color in){return   Color(r *  in.r,  g *  in.g,  b *  in.b);}
		Color operator *= (float in){return  Color(r *= in,    g *= in,    b *= in);}
		Color operator *= (Color in){return  Color(r *= in.r,  g *= in.g,  b *= in.b);}
		Color operator += (float in){return  Color(r += in,    g += in,    b += in);}
		Color operator += (Color in){return  Color(r += in.r,  g += in.g,  b += in.b);}
		Color operator + (Color in){return   Color(r +  in.r,  g +  in.g,  b +  in.b);}
		Color operator ^ (int in){return Color(pow(r,   in), pow(g, in), pow(b, in));}
};
#endif