#include"Renderer.h"
void GenVertexArrays(GLsizei n, GLuint *arrays);
//===================================================================================================================================================
//_______________________________________BUFFER CLASS _______________________________________________________________________________________________


Buffer::Buffer(Vec3 *Vertexdata,Vec3 *Colordata ,GLsizei vcount, GLint colorcount)
    :VertexCount(vcount), 
     ColorCount(colorcount)
{
    if(Colordata != nullptr){
            glGenBuffers(2 , &ID[0]);
            glBindBuffer(GL_ARRAY_BUFFER, ID[0]);
                glBufferData(GL_ARRAY_BUFFER,VertexCount * sizeof(Vec3), Vertexdata, GL_STATIC_DRAW) ; 
            glBindBuffer(GL_ARRAY_BUFFER,0);         // Unbind BUFFER_ID since its now bound to the ID;
    }

     if(Vertexdata != nullptr){
            glBindBuffer(GL_ARRAY_BUFFER, ID[1]); // Bind our second Vertex Buffer Object  
                glBufferData(GL_ARRAY_BUFFER, ColorCount * sizeof(RGBf), Colordata, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW  
                glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer  
                    glEnableVertexAttribArray(1); 
            glBindBuffer(GL_ARRAY_BUFFER,0);         // Unbind BUFFER_ID since its now bound to the ID;}
     } 
}

/// Hmmmmm Cant KEEP THIS UP,. MUST FIND A BETTER WAY TO HANDLE THE BUFFERING AND MANAGEMENT OF THE MESH DATA
Buffer::Buffer(Vec3 *Vertexdata,Vec3 *Colordata ,Vec3 *Normals ,GLsizei vcount, GLint colorcount, GLint normalCount)
    :VertexCount(vcount), 
     ColorCount(colorcount),
     NormalCount(normalCount)
{
    if(Colordata != nullptr){
            glGenBuffers(3 , &ID[0]);
            glBindBuffer(GL_ARRAY_BUFFER, ID[0]);
                glBufferData(GL_ARRAY_BUFFER,VertexCount * sizeof(Vec3), Vertexdata, GL_STATIC_DRAW) ; 
            glBindBuffer(GL_ARRAY_BUFFER,0);         // Unbind BUFFER_ID since its now bound to the ID;
    }

     if(Vertexdata != nullptr){
            glBindBuffer(GL_ARRAY_BUFFER, ID[1]); // Bind our second Vertex Buffer Object  
                glBufferData(GL_ARRAY_BUFFER, ColorCount * sizeof(RGBf), Colordata, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW  
                glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer  
                    glEnableVertexAttribArray(1); 
            glBindBuffer(GL_ARRAY_BUFFER,0);         // Unbind BUFFER_ID since its now bound to the ID;}
     } 
     if(Normals != nullptr){
            glBindBuffer(GL_ARRAY_BUFFER, ID[2]); // Bind our second Vertex Buffer Object  
                glBufferData(GL_ARRAY_BUFFER, NormalCount * sizeof(Vec3), Normals, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW  
                glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer  
                    glEnableVertexAttribArray(2); 
            glBindBuffer(GL_ARRAY_BUFFER,0);         // Unbind BUFFER_ID since its now bound to the ID;}
     }

}












void Buffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, ID[1]);
        glColorPointer(3,GL_FLOAT,0,(char *) NULL);
            glEnableClientState(GL_COLOR_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, ID[0]);
        glVertexPointer( 3, GL_FLOAT, 0, (char *) NULL);
            glEnableClientState(GL_VERTEX_ARRAY);
}

void Buffer::Unbind(){
                glDisableClientState(GL_VERTEX_ARRAY);
            glDisableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER,0);
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







