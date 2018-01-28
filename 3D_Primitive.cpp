#include"3D_Primitive.h"

GLuint Primitive::CUBE (Vec3 pos,float size){
    // The distance from the center to the outside of the cube
    // is half the size.
    size = size / 2.0f;
 
    GLuint displayList = glGenLists(1);
    if(!displayList) Print("Failed to make Object:CUBE");

    glNewList( displayList, GL_COMPILE );
    {
        glBegin( GL_QUADS );
        // Top face
        glColor3f(   0.0f, 1.0f,  0.0f );  // Green
        glVertex3d(  size, size, -size );  // Top-right of top face
        glVertex3f( -size, size, -size );  // Top-left of top face
        glVertex3f( -size, size,  size );  // Bottom-left of top face
        glVertex3f(  size, size,  size );  // Bottom-right of top face
 
        // Bottom face
        glColor3f(   1.0f,  0.5f,  0.0f ); // Orange
        glVertex3f(  size, -size, -size ); // Top-right of bottom face
        glVertex3f( -size, -size, -size ); // Top-left of bottom face
        glVertex3f( -size, -size,  size ); // Bottom-left of bottom face
        glVertex3f(  size, -size,  size ); // Bottom-right of bottom face
 
        // Front face
        glColor3f(   1.0f,  0.0f, 0.0f );  // Red
        glVertex3f(  size,  size, size );  // Top-Right of front face
        glVertex3f( -size,  size, size );  // Top-left of front face
        glVertex3f( -size, -size, size );  // Bottom-left of front face
        glVertex3f(  size, -size, size );  // Bottom-right of front face
 
        // Back face
        glColor3f(   1.0f,  1.0f,  0.0f ); // Yellow
        glVertex3f(  size, -size, -size ); // Bottom-Left of back face
        glVertex3f( -size, -size, -size ); // Bottom-Right of back face
        glVertex3f( -size,  size, -size ); // Top-Right of back face
        glVertex3f(  size,  size, -size ); // Top-Left of back face
 
        // Left face
        glColor3f(   0.0f,  0.0f,  1.0f);  // Blue
        glVertex3f( -size,  size,  size);  // Top-Right of left face
        glVertex3f( -size,  size, -size);  // Top-Left of left face
        glVertex3f( -size, -size, -size);  // Bottom-Left of left face
        glVertex3f( -size, -size,  size);  // Bottom-Right of left face
 
        // Right face
        glColor3f(   1.0f,  0.0f,  1.0f);  // Magenta
        glVertex3f(  size,  size,  size);  // Top-Right of left face
        glVertex3f(  size,  size, -size);  // Top-Left of left face
        glVertex3f(  size, -size, -size);  // Bottom-Left of left face
        glVertex3f(  size, -size,  size);  // Bottom-Right of left face
        glEnd();        
    }
    glEndList();
 
    return displayList;
}



void Primitive::display(void)
{

   glColor3f (1.0, 1.0, 1.0);
//   glCallList(Mesh);
  // glFlush();
}                                                                                 


void Primitive::init(void)
{
   Mesh = glGenLists (1);
   glNewList(Mesh, GL_COMPILE);
       //Vec3 POS ={0,0,0};
       CUBE(Vec3(0,0,0), 1);
   glEndList();

   glShadeModel(GL_FLAT);
   glClearColor(0.0, 0.0, 0.0, 0.0);
}                                                                                    
                                                                                    
                                                                                    
void Primitive::reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(30, (GLfloat) w/(GLfloat) h, 1.0, 100.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
}                                                                 

//struct Vec3_COLOR{
//        Vec3   m_Pos;
 //       Vec3   m_Color; 
//};


GLuint Primitive::CUBE2 (Vec3 pos,float size){
        Vec3_COLOR Mesh[8] = {
            { Vec3(  1,  1,  1 ), Vec3( 1, 1, 1 ) }, // 0
            { Vec3( -1,  1,  1 ), Vec3( 0, 0, 0 ) }, // 1
            { Vec3( -1, -1,  1 ), Vec3( 0, 0, 1 ) }, // 2
            { Vec3(  1, -1,  1 ), Vec3( 1, 0, 1 ) }, // 3
            { Vec3(  1, -1, -1 ), Vec3( 1, 0, 0 ) }, // 4
            { Vec3( -1, -1, -1 ), Vec3( 0, 0, 0 ) }, // 5
            { Vec3( -1,  1, -1 ), Vec3( 0, 1, 0 ) }, // 6
            { Vec3(  1,  1, -1 ), Vec3( 1, 1, 0 ) }, // 7
        };
        
        GLuint g_Indices[24] = {
            0, 1, 2, 3,                 // Front face
            7, 4, 5, 6,                 // Back face
            6, 5, 2, 1,                 // Left face
            7, 0, 3, 4,                 // Right face
            7, 6, 1, 0,                 // Top face
            3, 2, 5, 4,                 // Bottom face
        };
}





                                                                                                                                                                                                                                                                            
GLuint Make_Triangle(float size)
{
    size = -1;
    float z = -4;
        GLuint displayList = glGenLists(1);
        glNewList( displayList, GL_COMPILE );
                glBegin(GL_TRIANGLES);
                        glVertex3f(-size, -size/2, -z);
                        glVertex3f( size, -size/2, -z);
                        glVertex3f( 0.0f,  size/2, -z);
                glEnd();
return displayList;
}
