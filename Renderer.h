#pragma once
#include<vector>
#include"Vertex.h"
#include"Window.h"

#define VERTEX_ATTRIB     0
#define NORMAL_ATTRIB     1
#define TEXTURE_ATTRIB    2
#define COLOR_ATTRIB      3

#define BUFFER_OFFSET(i)   ((char *)NULL + (i))

#define MAX_OBJECTS    10000


struct Vertex
{
    Vec3 Position;
    Vec3 Normals;
    Vec2 Uv;
};


class Renderer
{
public: 
     
     void Submit();
     void Flush_Renderer();

   private:

       std::vector<Matrix4> Transformation_Stack;

       void Push(Matrix4 mat4);
       Matrix4 Pop();
};



// CONVERT THIS NAME TO SOMETHING LIKE IMAGE SINCE IT DOES NOT MAKE A TEXTURE BUT INSTEAD LOADS AN IMAGE
// THE TEXTUREBUFFER SHOULD EITHER BECOME TEXTURE OR PROB EVEN BETTER CALLED UV_BUFFER OR SOMETHING AND HAVE 
// A TEXTURE CLASS WHICH IS ITSELF A COMBINATION OF THE IMAGE AND THE TEXTURE COORDS SO THAT THEY CAN BE LOADED
// AND UNLOADED AT THE SAME TIME OR SEPERATELY AS NEEDED.


class Image
{
public:
        Image();
       ~Image();
        Image(const char *filename);
        Image(GLenum param, const char *filename);
       
        GLuint ID;
       
        GLubyte header[54];
        GLuint  dataPos;
       
        GLuint  Width,
                Height,
                ImageSize;
       
        GLubyte *Data;
       
        GLuint ElementCount;
       
        GLubyte* LoadBMP      (const char *filename);
       
        void SetWH(float width, float height);
        void GenColorTexture(float W, float H);
        void GenDepthTexture(float W, float H);
        void Bind();
        void Unbind();
};


//#include"glm.hpp"
//#include"Shader.h"


class VertexBuffer
{
    public:
        VertexBuffer(){}
       ~VertexBuffer();
        VertexBuffer(Vec3 *Vertexdata, GLsizei count);

        GLuint ID;
        GLint  ElementCount; 

        Vec3  *Data;

        void Bind();
        void Unbind();

        void Lock(GLenum access);
        void Unlock();

        GLfloat *Read();

        void Write(GLuint pos, GLfloat data);
        void Rebuild();
};  

class IndexBuffer
{
    public:
        IndexBuffer();
       ~IndexBuffer();
        IndexBuffer(GLuint *data, GLsizei count);

        GLuint ID;
        GLuint ElementCount;
        GLuint *Data;

    public:

        void Bind();
        void Unbind();
        void Rebuild();

        inline GLushort Get_Count(){return ElementCount;}
};

class ColorBuffer
{
   public:
        ColorBuffer(){}
       ~ColorBuffer();
        ColorBuffer(Vec3 *ColorData, GLsizei count);
//        ColorBuffer(Vec4 *ColorData, GLsizei count);

        GLuint ID;
        GLint  ElementCount; 

        Vec3 *Data;

    public:
        void Bind();
        void Unbind();
};




class NormalBuffer
{
    public:
        NormalBuffer(){}
       ~NormalBuffer();
        NormalBuffer(Vec3 *NormalData, GLsizei count);

        GLuint ID;
        GLint  ElementCount; 
        Vec3  *Data;

    public:
        void Bind();
        void Unbind();
};

class TextureBuffer
{
public:
    TextureBuffer();
   ~TextureBuffer();
    TextureBuffer(Image &img, Vec2 *UVdata, GLsizei count);

    GLuint ID;
    GLuint ElementCount;

    Vec2     *Data;
    Image ImageData;
public:

    void Bind();
    void Unbind();
};

//=============================================================================================================================================
//_______________________________________________________________________________________________________________________________________________________________

class VAOBuffer
{
public:
        VAOBuffer();
       ~VAOBuffer(){}

       VertexBuffer    *Vertices;
       IndexBuffer     *Indices;
       NormalBuffer    *Normals;
       TextureBuffer   *Textures;
       ColorBuffer     *Colors;

       void Attach(VertexBuffer  *vertices);
       void Attach(IndexBuffer   *indices);
       void Attach(NormalBuffer  *normals);
       void Attach(TextureBuffer *textures);
       void Attach(ColorBuffer   *colors);

       void Bind();
       void Unbind();
};































/*

//=============================================================================================================================================
//_______________________________________________________________________________________________________________________________________________________________



//=============================================================================================================================================
//________________TEST STRUCTURES TO HANDLE THE VAO Issues___________________________________________________________________________________________________________________________

struct VertexFormat
{
  bool enabled;
  int attribute_index;
  float data_type; //Is f32, f64, or int32.
  int num_components;
  bool normalized;
  GLenum type;
  int binding;    //The `bindings` index this attribute gets its data from.
  int *offset;
};

struct VertexBufferBinding// Mesh
{
  Buffer buffer;// VBO
  int  *offset; // Number of Vertices 
  int  *stride;
  int instancing;
};

struct VertexArrayObject
{
  VertexFormat formats[16];
  VertexBufferBinding bindings[16];
};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





// Renderable2d = BatchSprite
class Renderable2D{
public:
    Renderable2D::Renderable2D();
    Renderable2D::~Renderable2D();

    Vec3 Position;
    Vec2 Size;
    Vec4 Color;
    vector<VertexData> VertexArray;
    IndexBuffer *IBO;
    GLuint VBO;

    unsigned int IndexCount;
    Shader &SHADER;


};



class Renderer2D{
public:
    virtual void submit(const Renderable2D *renderable);
    virtual void flush();
};














#define RENDERER_MAX_SPRITES 10000
#define RENDERER_VERTEX_SIZE   sizeof(VertexData)
#define RENDERER_SPRITE_SIZE RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE RENDERER_MAX_SPRITES * 6
struct VertexData{
    Vec3 Vertex;
    Vec3 Color;
}; // 28 Bytes Currently
 


class BatchRender2D: public Renderer2D{
private:
    //VertexArray VAO;
    IndexBuffer IBO;
    GLsizei IndexCount;
    GLuint VBO;
public:
    void submit(const Renderable2D *BatchSprite) override;
    void flush() override;

};




BatchSprite::BatchSprite(){}

BatchSprite::~BatchSprite(){
    delete(IBO);
}




void BatchSprite::Init(){
    
}
*/