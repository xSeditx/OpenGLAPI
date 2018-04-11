#include"Renderer.h"
void GenVertexArrays(GLsizei n, GLuint *arrays);
//===================================================================================================================================================
//_______________________________________BUFFER CLASS _______________________________________________________________________________________________

Buffer::Buffer(){} ; Buffer::~Buffer(){}

Buffer::Buffer(GLfloat *data,GLsizei count,GLint componentcount)
    :NUM_COMPONENTS(componentcount), 
     COUNT(count)
{
        _GL(glGenBuffersARB(1,&BUFFER_ID));                                                //Allocate memory and Assign Pointer to BUFFER_ID
        _GL(glBindBuffer(GL_ARRAY_BUFFER,BUFFER_ID));                                   //Bind the Data to the BUFFER ID so it points to it
        _GL(glBufferData(GL_ARRAY_BUFFER,count * sizeof(GLfloat),data,GL_STATIC_DRAW)); //<------------------------------------------------
        _GL(glBindBuffer(GL_ARRAY_BUFFER,0));                                           // DELETE BUFFER since its now bound to the ID;
}
        
void Buffer::Bind(){
        _GL(glBindBuffer(GL_ARRAY_BUFFER, BUFFER_ID));
}

void Buffer::Unbind(){
        _GL(glBindBuffer(GL_ARRAY_BUFFER,0));
}

//===================================================================================================================================================
//__________________________________ INDEX BUFFER CLASS _____________________________________________________________________________________________
IndexBuffer::IndexBuffer(){} ; IndexBuffer::~IndexBuffer(){}


IndexBuffer::IndexBuffer(GLushort *data,GLsizei count)
    : COUNT(count)
{
        _GL(glGenBuffers(1,&BUFFER_ID));
        _GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,BUFFER_ID));
        _GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER,count * sizeof(GLushort),data,GL_STATIC_DRAW));
        _GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0));
}

void IndexBuffer::Bind()
{
        _GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BUFFER_ID));
}
void IndexBuffer::Unbind()
{
        _GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0));
}
        
//===================================================================================================================================================
//__________________________________ VERTEX BUFFER CLASS ____________________________________________________________________________________________

 
VertexArray::VertexArray(){ 
 ARRAY_ID = 0;
#if GL_VERSION > 2
  _GL(glGenVertexArrays(1, &ARRAY_ID));  //<--- I hate you and your Children!
          Print("SUCCESS");//<-LIAR!!!
#endif
}
VertexArray::~VertexArray()
{
        for (int i =0;i< BUFFERS.size(); i++)delete(BUFFERS[i]);
}

void VertexArray::Addbuffer (Buffer *buffer, GLuint index){
       Print("enter"); 
     //   Bind();
        buffer->Bind();
       
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, buffer->Get_Component(), GL_FLOAT, false, 0  , 0 );
       
        buffer->Unbind();
}

void VertexArray::Bind(){
        glBindVertexArray(ARRAY_ID);
}
void VertexArray::Unbind(){
        glBindVertexArray(0);
}


//===================================================================================================================================================
//__________________________________ RENDERER CLASS _________________________________________________________________________________________________

void Renderer::Push(Matrix4 mat4){
        Transformation_Stack.push_back(mat4);
}

 Matrix4 Renderer::Pop(){
        Matrix4 ret = Transformation_Stack.back();
        Transformation_Stack.pop_back();
        return ret;
}







