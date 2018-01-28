//                                                                                                                                                                        
//                                                  OPENGL 2.0 Abstraction API
//                                                       January 27 2018
//                                                      -----------------                                                                                                                                                        
//                                                                                                                                                                        
//                                                                                                                                                                        
//                                               OPEN_GL 3D OBJECT MANAGEMENT LIB                                                                                                                     
//                                                                                                                                                                        
//                                                                                                                                                                        
//                                                                                                                                                                        
//                                                                                                                                                                        
//                                                                                                                                                                        
//                                                                                                                                                                        
//======================================================================================================================================================================
#pragma once

#include"Vector.h"
#include"Window.h"
                                                                                                                                                                                                                                                                                                                    
class Object{
public:
        Vec3 POSITION;
		Vec3 SPEED;
		Vec3 ANGLE;
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
         void init(void);
		 void reshape(int w, int h);

protected:
private:
                                                                        
};
                                                                                    
class Terrain : public Object{
public:
protected:
private:
};

class Mesh : public Object{
public:
protected:
private:
};
                                                                                    
 
                                                                                    
class CUBEclass : public Primitive{
    CUBEclass(int siz,int color):SIZ(siz),COLOR(color){}
    int SIZ, 
        COLOR;
    Vec3_COLOR Mesh[8];
};
                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    

                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                    
                                                                                    
                                                                                    
                                                                                    
                                                                                    
