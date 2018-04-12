//                                                                                                                                                                        
//                                                  OPENGL 2.0 Abstraction API
//                                                       January 27 2018
//                                                      -----------------                                                                                                                                                        
//                                                                                                                                                                        
//                                                                                                                                                                        
//                                               OPEN_GL 3D OBJECT MANAGEMENT LIB                                                                                                                     
//   MOSTLY EXPERIMENTAL WIP                                                                                                                                                                     
//======================================================================================================================================================================
#pragma once
#include<vector>
#include"vertex.h"
#include"Window.h"
#include"Renderer.h"
#include"Collision.h"


class Mesh{
public:
    Mesh(){}
    Vec3 Rotation;
    Vec3 Position;
    Vec3 Scale;
    GLuint List;

    enum objecttype{
        Torus_t,
        Sphere_t,
        Cube_t
    }ObjectType;

    void Set_Position(float x, float y, float z);
    void Set_Rotation(float x, float y, float z);

    void Rotate(float x, float y, float z);
    void Render();
    void RenderVBO();
};


class Torus: public Mesh{
public:
    Torus(int numc, int numt, float x, float y, float z, float scale);
    Torus(int numc, int numt, float x, float y, float z);

   // Buffer *VBO;

    void Set_Position(float x, float y, float z);
    void Set_Rotation(float x, float y, float z);

    void Rotate(float x, float y, float z);
    void Render();
    void RenderVBO();
};
class Sphere : public Mesh{
public:
    
    Sphere(Vec3 pos, float radius);

    void Set_Position(float x, float y, float z);
    void Set_Rotation(float x, float y, float z);

    void Rotate(float x, float y, float z);
    void Render();
};
class Cube : public Mesh{
public:
    Cube(Vec3 pos, float size);

    void Set_Position(float x, float y, float z);
    void Set_Rotation(float x, float y, float z);

    void Rotate(float x, float y, float z);
    void Render();
};


//Buffer VBO(Vertex, sizeof(Vec3) * count, 3)


class Ball{
public:
     Vec3 Position;
     Vec3 Rotation;
     Vec3 Scale;

public:// OpenGL Stuff

     GLuint BUFFER_ID[2];
  
     Ball(Vec3 pos, float radius, int sectors);

     RGBf  Colors  [648];
     Vec3  Vertices[648];

     GLuint VertexCount;
     GLuint ColorCount;

     float Radius;
     
     Buffer Vbo;


     void Set_Position(float x, float y, float z){Position.x = x; Position.y = y; Position.z = z;}
     void Set_Rotation(float x, float y, float z);

     Vec3 Get_Position(){return Position;}
     Vec3 Get_Rotation(){return Rotation;}

     void Rotate(float x, float y, float z);
     void Render();

     void Submit(Vec3 *data); // <---- Set this up to Update the Vertex or ColorBuffer
};

extern Vec3 GetNormal(Vec3 v1, Vec3 v2, Vec3 v3);


