#pragma once
#include"Vertex.h"



class Cube {
	Cube();
   ~Cube(){}
};



class Object {
public:


	float  *VBuffer;
	unsigned short   IBuffer;

	Vec3 Position;
	void Render();
};
