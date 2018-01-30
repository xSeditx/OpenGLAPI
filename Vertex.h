#pragma once
//#include "Window.h"
#include <iostream>


//======================================================================================================================================================================
//_________________ VERTEX 2D X/Y ______________________________________________________________________________________________________________________________________
//======================================================================================================================================================================

struct Vec2{
        float x;float y;
        Vec2();
        Vec2(const float& x,const float& y);
    float   X,
            Y;
        
        Vec2& add(const Vec2& other);
        Vec2& subtract(const Vec2& other);
        Vec2& divide(const Vec2& other);
        Vec2& multiply(const Vec2& other);
        
        friend Vec2 operator +(Vec2 left, const Vec2& right);
        friend Vec2 operator -(Vec2 left, const Vec2& right);
        friend Vec2 operator /(Vec2 left, const Vec2& right);
        friend Vec2 operator *(Vec2 left, const Vec2& right);
        
        Vec2& operator +=(const Vec2& other);
        Vec2& operator -=(const Vec2& other);
        Vec2& operator *=(const Vec2& other);
        Vec2& operator /=(const Vec2& other);
        
        bool operator ==(const Vec2& other);
        bool operator !=(const Vec2& other);
        
        friend std::ostream& operator<<(std::ostream& stream,const Vec2& vector);
};


//======================================================================================================================================================================
//___________________ VERTEX 3D X/Y ____________________________________________________________________________________________________________________________________
//======================================================================================================================================================================

struct Vec3{
        float x;float y;float z;
        Vec3();
        Vec3(const float& x,const float& y,const float& z);
        
        Vec3& add(const Vec3& other);
        Vec3& subtract(const Vec3& other);
        Vec3& divide(const Vec3& other);
        Vec3& multiply(const Vec3& other);
        
        friend Vec3 operator +(Vec3 left, const Vec3& right);
        friend Vec3 operator -(Vec3 left, const Vec3& right);
        friend Vec3 operator /(Vec3 left, const Vec3& right);
        friend Vec3 operator *(Vec3 left, const Vec3& right);
        
        Vec3& operator +=(const Vec3& other);
        Vec3& operator -=(const Vec3& other);
        Vec3& operator *=(const Vec3& other);
        Vec3& operator /=(const Vec3& other);
        
        bool operator ==(const Vec3& other);
        bool operator !=(const Vec3& other);
        
        friend std::ostream& operator<<(std::ostream& stream,const Vec3& vector);
};

//======================================================================================================================================================================
//_________________ VERTEX 4D X/Y ______________________________________________________________________________________________________________________________________
//======================================================================================================================================================================

struct Vec4{
        float x;float y;float z;float w;
        Vec4();
        Vec4(const float& x,const float& y,const float& z, const float& w);
        
        Vec4& add(const Vec4& other);
        Vec4& subtract(const Vec4& other);
        Vec4& divide(const Vec4& other);
        Vec4& multiply(const Vec4& other);
        
        friend Vec4 operator +(Vec4 left, const Vec4& right);
        friend Vec4 operator -(Vec4 left, const Vec4& right);
        friend Vec4 operator /(Vec4 left, const Vec4& right);
        friend Vec4 operator *(Vec4 left, const Vec4& right);
        
        Vec4& operator +=(const Vec4& other);
        Vec4& operator -=(const Vec4& other);
        Vec4& operator *=(const Vec4& other);
        Vec4& operator /=(const Vec4& other);
        
        bool operator ==(const Vec4& other);
        bool operator !=(const Vec4& other);
        
        friend std::ostream& operator<<(std::ostream& stream,const Vec4& vector);
};



//======================================================================================================================================================================
//_________________ MATRIX 4D ___________________________________________________________________________________________________________________________________________
//======================================================================================================================================================================
       
        
struct Matrix4{
        
        	union{
        		   float elements[16];
        		struct{
        			Vec4 columns[4];
        		};
        	};
        
        Matrix4();
        Matrix4(float Diagonal);
        
        static Matrix4 Identity();
        
        Matrix4& Multiply(const Matrix4& other);
        
        friend Matrix4 operator*(Matrix4 left,const Matrix4& right);
        Matrix4& operator*=(const Matrix4& other);
        
        
        static Matrix4 Orthographic(float Left,float Right,float Top,float Bottom,float Near, float Far);
        static Matrix4 Perspective(float FOV,float Aspect_Ratio,float Near,float far);
                    	
        static Matrix4 Translation(const Vec3& Translation);
        static Matrix4 Rotation(float Angle,const Vec3& Axis);
        static Matrix4 Scale(const Vec3& Translation);
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
 
 