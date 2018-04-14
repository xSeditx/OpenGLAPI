//                                                                                                                          
//                          OPENGL 2.0 Abstraction API
//                               January 24 2018
//                              -----------------                                                                           
//                                                                                                                          
//                             CANERA HANDLING LIB                                                                     
//==========================================================================================================================


#include"Camera.h"
#include <GLFW/glfw3.h> 
#include "Window.h"

Camera::Camera()
      :
      Position(0,0,0),
      Rotation(0,0,0),
      Speed(1)
{}

void Camera::MoveForward(const float &speed)
{
    Speed = speed;
float  SIN_X = sin(RADIANS( Rotation.x  - 90));
            Position.x -= (cos(RADIANS(Rotation.y - 90)) * SIN_X) * Speed;
            Position.y -=  cos(RADIANS(Rotation.x - 90)) * speed;
            Position.z -= (sin(RADIANS(Rotation.y - 90)) * SIN_X) * Speed;
}
void Camera::MoveBack(const float &speed)
{
        Speed = speed;
float  SIN_X = sin(RADIANS( Rotation.x  - 90));
            Position.x += (cos(RADIANS(Rotation.y - 90))* SIN_X) * Speed;
            Position.y +=  cos(RADIANS(Rotation.x - 90))* speed;
            Position.z += (sin(RADIANS(Rotation.y - 90))* SIN_X) * Speed;
}
void Camera::MoveLeft(const float &speed)
{
            Speed = speed;
            Position.x +=  cos(RADIANS(Rotation.y - 0)) * Speed;
            Position.z +=  sin(RADIANS(Rotation.y - 0)) * Speed;
}
void Camera::MoveRight(const float &speed)
{
            Speed = speed;
            Position.x += cos(RADIANS(Rotation.y - 180)) * Speed;
            Position.z += sin(RADIANS(Rotation.y - 180)) * Speed;
}
void Camera::Rotate(float x,float y){
        Rotation.y += (x * .8);  
        Rotation.x += (y * .8);
}
void Camera::Update()
{
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
//  ROTATE the Camera  
        glRotatef(Rotation.x ,  1.0f,  0.0f,  0.0f);
        glRotatef(Rotation.y ,  0.0f,  1.0f,  0.0f);
        glRotatef(Rotation.z ,  0.0f,  0.0f,  1.0f);
//  Move Camera into Position       
        glTranslatef(Position.x, 0., 0.);
        glTranslatef(  0., Position.y,   0.);
        glTranslatef(  0.,   0., Position.z);
}
