#pragma once

#include<vector>
#include"Window.h"
#include"3d_Primitive.h"

#define Collider       CollisionSphere::Collision_ObjectList 



class CollisionSphere{

public:
     CollisionSphere(){}
     CollisionSphere(Vec3 pos, float radius, int parent);

     int ID;
     int ParentID;

     float  Radius;
// ------------------ PHYSICS ----------------------------
     Vec3   Position,
            Force,
            Acceleration,
            Velocity;

     float  Mass;

     float  DeltaTime, 
            PresentTime;

//------------ Getters && Setters ------------------------
     void   SetPosition(Vec3 pos)   { Position = pos;}
     void   SetRadius(float radius) { Radius=radius; }
 
     Vec3   GetPosition(){return Position;}
     float  GetRadius(){return Radius;}

//--------------------------------------------------------

     float  Is_Collision(int other);
     void   CollisionDetection();
     void   Update();
// Static object list
public:
     static std::vector<CollisionSphere*> Collision_ObjectList;
     static unsigned int  Collision_ObjectCount;
 };
