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

    Buffer *VBO;

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






class Ball{
public:
     Vec3 Position;
     Vec3 Rotation;
     Vec3 Scale;


public:// OpenGL Stuff

     GLuint BUFFER_ID[2];
  
     Ball(Vec3 pos, float radius);
  
     GLfloat *Normals;
//     GLfloat *Color;
     RGBf  Colors  [648];
     Vec3  Vertices[648];
     int   VertexCount;

     float Radius;
  
     void Set_Position(float x, float y, float z);
     void Set_Rotation(float x, float y, float z);
  
     void Rotate(float x, float y, float z);
     void Render();

     void ChangeVerts();
};




  //  vertices.resize(rings * sectors * 3);
  //  normals.resize(rings * sectors * 3);
  //  texcoords.resize(rings * sectors * 2);
  //
  //  std::vector<GLfloat>::iterator v = vertices.begin();
  //  std::vector<GLfloat>::iterator n = normals.begin();
  // std::vector<GLfloat>::iterator t = texcoords.begin();



//
//
//#define _USE_MATH_DEFINES
//#include"Window.h"
//
//// your framework of choice here
//
//class SolidSphere
//{
//protected:
//    std::vector<GLfloat> vertices;
//    std::vector<GLfloat> normals;
//    std::vector<GLfloat> texcoords;
//    std::vector<GLushort> indices;
//
//public:
//    SolidSphere(float radius, unsigned int rings, unsigned int sectors)
//    {
//        float const R = 1./(float)(rings-1);
//        float const S = 1./(float)(sectors-1);
//        int r, s;
//
//        vertices.resize(rings * sectors * 3);
//        normals.resize(rings * sectors * 3);
//        texcoords.resize(rings * sectors * 2);
//        std::vector<GLfloat>::iterator v = vertices.begin();
//        std::vector<GLfloat>::iterator n = normals.begin();
//        std::vector<GLfloat>::iterator t = texcoords.begin();
//        for(r = 0; r < rings; r++) for(s = 0; s < sectors; s++) {
//                float const y = sin( -M_PI_2 + M_PI * r * R );
//                float const x = cos(2*M_PI * s * S) * sin( M_PI * r * R );
//                float const z = sin(2*M_PI * s * S) * sin( M_PI * r * R );
//
//                *t++ = s*S;
//                *t++ = r*R;
//
//                *v++ = x * radius;
//                *v++ = y * radius;
//                *v++ = z * radius;
//
//                *n++ = x;
//                *n++ = y;
//                *n++ = z;
//        }
//
//        indices.resize(rings * sectors * 4);
//        std::vector<GLushort>::iterator i = indices.begin();
//        for(r = 0; r < rings-1; r++) for(s = 0; s < sectors-1; s++) {
//                *i++ = r * sectors + s;
//                *i++ = r * sectors + (s+1);
//                *i++ = (r+1) * sectors + (s+1);
//                *i++ = (r+1) * sectors + s;
//        }
//    }
//
//    void draw(GLfloat x, GLfloat y, GLfloat z)
//    {
//        glMatrixMode(GL_MODELVIEW);
//        glPushMatrix();
//        glTranslatef(x,y,z);
//
//        glEnableClientState(GL_VERTEX_ARRAY);
//        glEnableClientState(GL_NORMAL_ARRAY);
//        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
//
//        glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
//        glNormalPointer(GL_FLOAT, 0, &normals[0]);
//        glTexCoordPointer(2, GL_FLOAT, 0, &texcoords[0]);
//        glDrawElements(GL_QUADS, indices.size(), GL_UNSIGNED_SHORT, &indices[0]);
//        glPopMatrix();
//    }
//};
//
//SolidSphere sphere(1, 12, 24);
//
//void display()
//{
//    int const win_width  = …; // retrieve window dimensions from
//    int const win_height = …; // framework of choice here
//    float const win_aspect = (float)win_width / (float)win_height;
//
//    glViewport(0, 0, win_width, win_height);
//
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(45, win_aspect, 1, 10);
//
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//
//#ifdef DRAW_WIREFRAME
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//#endif
//    sphere.draw(0, 0, -5);
//
//    swapBuffers();
//}
//
//int main(int argc, char *argv[])
//{
//    // initialize and register your framework of choice here
//    return 0;
//}
//
//
//
















                  

                                            
/*void glVertexAttribPointer(	GLuint index,
 	GLint size,
 	GLenum type,
 	GLboolean normalized,
 	GLsizei stride,
 	const GLvoid * pointer);*/






/*
Vertex_buffer_object::Vertex_buffer_object()
{
    initVB();
}
 
Vertex_buffer_object::~Vertex_buffer_object() {}
 
void Vertex_buffer_object::draw()
{
    glEnable(GL_DEPTH_TEST);
 
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
 
    glPushMatrix();
 
    glBindVertexArray(_vao);
 
    // bind buffer storing positions
    glBindBuffer(GL_ARRAY_BUFFER, _positionVBO);
    glEnableClientState(GL_VERTEX_ARRAY);
 
    // take positions from buffer bound to GL_ARRAY_BUFFER
    // this command 'remembers' which buffer is bound to
    // GL_ARRAY_BUFFER at the time of the call
    glVertexPointer(3, GL_FLOAT, 0, 0);
 
    // bind buffer storing normals
    // this has no effect on which buffer the positions are taken from
    glBindBuffer(GL_ARRAY_BUFFER, _normalVBO);
    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, 0, 0);
 
    // bind buffer storing colors
    glBindBuffer(GL_ARRAY_BUFFER, _colorVBO);
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_UNSIGNED_BYTE, 0, NULL);
 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexVBO);
 
    glEnableClientState(GL_ELEMENT_ARRAY_BUFFER);
 
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
 
    glBindVertexArray(0);
 
    //desabilitando modos de desenho.
    glDisableClientState(GL_ELEMENT_ARRAY_BUFFER);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
 
    //desabilitando vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
 
void Vertex_buffer_object::initVB()
{
    if (!glGenBuffers || !glBindBuffer || !glBufferData)
    {
        std::cerr << "VBOs are not supported by your graphics card" << std::endl;
    }
 
 
    // Variables for the cube data
    float _vertex[] =
    {
        // front
        -1.0, -1.0,  1.0,
        1.0, -1.0,  1.0,
        1.0,  1.0,  1.0,
        -1.0,  1.0,  1.0,
        // back
        -1.0, -1.0, -1.0,
        1.0, -1.0, -1.0,
        1.0,  1.0, -1.0,
        -1.0,  1.0, -1.0,
    };
 
    float _normal[] = {((-1.0f, -1.0f, 1.0f),
                        ( 1.0f, -1.0f, 1.0f),
                        ( 1.0f, 1.0f, 1.0f),
                        (-1.0f, 1.0f, 1.0f),
                        (-1.0f, -1.0f, -1.0f),
                        (1.0f, -1.0f, -1.0f),
                        (1.0f, 1.0f, -1.0f),
                        (-1.0f, 1.0f, -1.0f))
                      };
 
    static const GLsizeiptr ColorSize = 8 * 3 * sizeof(GLubyte);
    static const GLubyte _color[] =
    {
        255,   0,   0,
        255, 255,   0,
        0, 255,   0,
        0, 255,   0,
        0,   0, 255,
        255,   0,   0,
        255, 255,   0,
        0, 255,   0
    };
    // Element Indicies for the Cube
    unsigned int _index[] =
    {
        // front
        0, 1, 2,
        2, 3, 0,
        // top
        3, 2, 6,
        6, 7, 3,
        // back
        7, 6, 5,
        5, 4, 7,
        // bottom
        4, 5, 1,
        1, 0, 4,
        // left
        4, 0, 3,
        3, 7, 4,
        // right
        1, 5, 6,
        6, 2, 1,
    };
 
    const unsigned _vertexSize = 24;
 
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);
 
    //gerando a vbo para as posições
    glGenBuffers(1, &_positionVBO);
    glBindBuffer(GL_ARRAY_BUFFER, _positionVBO);
    glBufferData(GL_ARRAY_BUFFER, _vertexSize * sizeof(float), NULL, GL_STATIC_DRAW);
    void* positionPtr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    memcpy(positionPtr, (float*) _vertex, 24 * sizeof(float));
    glUnmapBuffer(GL_ARRAY_BUFFER);
 
    //gerando a vbo para as normais
    glGenBuffers(1, &_normalVBO);
    glBindBuffer(GL_ARRAY_BUFFER, _normalVBO);
    glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float) , NULL, GL_STATIC_DRAW);
    void* normalPtr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    memcpy(normalPtr, (float*) _normal, 24 * sizeof(float));
    glUnmapBuffer(GL_ARRAY_BUFFER);
 
    //gerando a vbo para as cores
    glGenBuffers(1, &_colorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, _colorVBO);
    glBufferData(GL_ARRAY_BUFFER, ColorSize , NULL, GL_STATIC_DRAW);
    void* colorPtr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    memcpy(colorPtr, (GLubyte*) _color, ColorSize);
    glUnmapBuffer(GL_ARRAY_BUFFER);
 
    //gerando a vbo para os indices
    glGenBuffers(1, &_indexVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(unsigned int), NULL, GL_STATIC_DRAW);
 
    //setando os dados para index
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexVBO);
    void* indexPtr = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
    memcpy(indexPtr,(unsigned int*) _index,  36 * sizeof(unsigned int));
    glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
 
    glBindVertexArray(0);
}

*/