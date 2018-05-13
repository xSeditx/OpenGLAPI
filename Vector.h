#pragma once
//#include "Window.h"

struct Vec2{
       Vec2( float _x = 0.0f, float _y = 0.0f) 
            : X(_x), Y(_y) {}
	float   X,
            Y;
};

struct Vec3{
       Vec3( float _x = 0.0f, float _y = 0.0f, float _z = 0.0f ) 
            : X(_x), Y(_y), Z(_z) {}
	float   X,
            Y,
            Z;
};

struct Vec4{
       Vec4( float _x = 0.0f, float _y = 0.0f, float _z = 0.0f , float _w = 0.0f ) 
            : X(_x), Y(_y), Z(_z) , W(_w){}
	float   X,
            Y,
            Z,
            W;
};


class Matrix3{
public:
protected:
private:
};


class Matrix4{
public:
protected:
private:
};

struct Vec3_COLOR
{
    Vec3 m_Pos;
    Vec3 m_Color;
};



struct float3
{
    float3( float _x = 0.0f, float _y = 0.0f, float _z = 0.0f ) 
        : x(_x), y(_y), z(_z) {}
     
    float x;
    float y;
    float z;
};
 
// Vertex definition
struct VertexXYZColor
{
    float3 m_Pos;
    float3 m_Color;
};
 
 