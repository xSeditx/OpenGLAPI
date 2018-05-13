#include<vector>
#include"Vertex.h"
#include"Window.h"

using namespace std;

class Buffer{
public:
        Buffer();
       ~Buffer();
        Buffer(GLfloat *data,GLsizei count,GLint componentcount);
        
        GLuint BUFFER_ID;
        GLuint NUM_COMPONENTS; //How many vertex per count
        
        void Bind();
        void Unbind();
public:
        inline GLuint Get_Count(){return NUM_COMPONENTS;}

};

class IndexBuffer{
public:
        IndexBuffer();
       ~IndexBuffer();
        IndexBuffer(GLushort *data,GLsizei count);
        
        GLsizei COUNT; // Number of Indices
        GLuint  BUFFER_ID;

public:
        void Bind();
        void Unbind();
};


class VertexArray{/*      THIS MOTHER FUCKER RIGHT HERE HAS WASTED A WEEK OR SO OF MY FUCKING LIFE RESEARCHING SHIT !!! FUCK YOU VAO !!!*/
public:
    VertexArray();
   ~VertexArray();

    GLuint ARRAY_ID;
    vector<Buffer*> BUFFERS;
	
    void Bind();
    void Unbind();
    void Addbuffer (Buffer *buffer, GLuint index);
};



//=============================================================================================================================================
//_______________________________________________________________________________________________________________________________________________________________

class Renderer{
public: 
     
     void Submit();
     void Flush_Renderer();

   private:
       vector<Matrix4> Transformation_Stack;

       void Push(Matrix4 mat4);
       Matrix4 Pop();
};


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