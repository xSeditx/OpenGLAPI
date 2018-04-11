#pragma once

#include "Window.h"
#include <iostream>
#include "Vertex.h"       // Include our custom Vec3 class




class Camera{
    public:
        Camera();
        
        Vec3 Position;
        Vec3 Rotation;
        
        float Speed;
        
        void MoveForward(const float &Speed);
        void MoveBack(const float &speed);
        void MoveLeft(const float &Speed);
        void MoveRight(const float &Speed);
        void Rotate(float x,float y);
        void Update();
};
