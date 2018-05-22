#pragma once

#include"Vertex.h"
#include"Renderer.h"
#include"3d_Primitive.h"


#define  VERTEX_OFFSET          0
#define  NORMALS_OFFSET         1
#define  COLOR_OFFSET           2
#define  MAX_INDICES        20000 



class  Renderable 
{
public:
Vec3 GetPosition();
Vec3 GetColor();
GLsizei Size;
};



struct VertexData{
    Vec3 Vertex,
         Normals,
         Color;
};
class BatchRenderer{
public:
       BatchRenderer(){}
      ~BatchRenderer(){}

      VertexData  *VertexBuffer;
      GLuint  IndexBuffer;

      GLushort Indices[MAX_INDICES];

      void Submit(const Renderable *object);
      void Begin();
};


// glMapBuffer returns a pointer to a VBO object 


void BatchRenderer::Begin()
{
        VertexBuffer = (VertexData*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
}
void BatchRenderer::Submit(const Renderable *object)
{
    // CAREFUL stupid Extensions
    
  //  VertexBuffer->Vertex = object->GetPosition();
   // VertexBuffer->Vertex = object->GetColor();
    VertexBuffer++;
}