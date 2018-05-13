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
                                                                                                                                                                                                                                                                                                                    
class Object{
public:
        Vec3 POSITION;
		Vec3 SPEED;
		Vec3 ANGLE;

        void Rotate(GLfloat angle);
        void Translate(GLfloat x,GLfloat y,GLfloat z);

        bool Init();
        void Destroy();
private:
};
                                                                                    
class Primitive : public Object{
public:
         enum{
            SPHERE,
            CONE,
            TORUS,
         }Type;

		 unsigned int Mesh;   

		 GLuint CUBE(Vec3 pos,float size);
         GLuint CUBE2 (Vec3 pos,float size); // This is just debug stuff to test different construction methods
		 void display(void);
         void Init(void);
		 void reshape(int w, int h);
         void Destroy();
protected:
private:
                                                                        
};
                                                                                    
class Terrain : public Object{
public:
        bool Init();
        void Destroy();
        void Rotate(GLfloat angle);

protected:
private:
};

class Mesh : public Object{
public:
        bool Init();
        void Destroy();
        void Rotate(GLfloat angle);
        GLuint  VBO;
        GLuint  OFFSET;
protected:
private:
};
  


 
 //===========================================================TEST STUFF                                                                                   
class CUBEclass : public Primitive{
    CUBEclass(int siz,int color):SIZ(siz),COLOR(color){}
    int SIZ, 
        COLOR;
    Vec3_COLOR Mesh[8];
};
                                                                                    
                                                                                                                                                                                                                                                                                                                    

                                       

                                            
/*void glVertexAttribPointer(	GLuint index,
 	GLint size,
 	GLenum type,
 	GLboolean normalized,
 	GLsizei stride,
 	const GLvoid * pointer);*/

                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                    
                                                                                    
                                                                                    
                                                                                    
