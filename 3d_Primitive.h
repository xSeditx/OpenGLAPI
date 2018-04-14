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


//Buffer VBO(Vertex, sizeof(Vec3) * count, 3)

class Ball{
public:
     Vec3 Position;
     Vec3 Rotation;
     Vec3 Scale;

     int Mesh_ID;
     int CollisionID;
     float Radius;

public:// OpenGL Stuff

     Ball(){}  
     Ball(Vec3 pos, float radius, int sectors);

     GLuint BUFFER_ID[2];

     Vec3  Vertices[648];
     RGBf  Colors  [648];

     GLuint VertexCount;
     GLuint ColorCount;

     Buffer Vbo;

     void Set_Position(float x, float y, float z)    {Position = Vec3(x,y,z);}
     void Set_Position(Vec3 pos)                          {Position = pos;}
     void Set_Rotation(float x, float y, float z)    {Rotation = Vec3(x,y,z);}
     void SetRotation(Vec3 rot)                      {Rotation = rot;}

     Vec3 Get_Position(){return Position;}
     Vec3 Get_Rotation(){return Rotation;}

     Vec3 GetVert(int index){return Vertices[index];}
     void ChangeVert(int index, Vec3 newpos);
     void Submit(Vec3 *data); // <---- Set this up to Update the Vertex or ColorBuffer

     void Update();
     void Render();

private:
     void CollisionDetection();

// Static object list
public:
     static std::vector<Ball*> s_BallList;
     static unsigned int BallCount;

     static int MakeCollisionSphere(Vec3 pos, float rad, int p);
};















extern Vec3 GetNormal(Vec3 v1, Vec3 v2, Vec3 v3);


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
