#pragma once

#include<vector>
#include"Window.h"
#include"3d_Primitive.h"
#include"QuadTree.h"

#define Collider       CollisionSphere::Collision_ObjectList 
#define MaxObjects     1000
class Mass{
    public:
        Mass(){}
        Mass(float weight, Vec3 pos);
        Mass(float weight,float x, float y, float z){Mass(weight, Vec3(x,y,z));}
       ~Mass(){}


    Vec3   Velocity,
           Position, 
           Acceleration,
           Angular,
           Force;

 
    float  Kg;

    void Apply_Gravity  ();
    void Apply_Physics  ();
    void Set_Force      (float x, float y);
    void Set_Position   (float x, float y);

    Vec3 Get_Position();

    inline float Get_X(){return Position.x;}
    inline float Get_Y(){return Position.y;}
    inline float Get_Z(){return Position.z;}

    struct convert{
        inline float Pounds_to_Kg  (float lb) { return lb * .453; }
        inline float Newtons_to_Kg (float N)  { return N / 9.8;   }
        inline float Kg_to_Newtons (float Kg) { return Kg * 9.8;  }
    }Convert;

    static void  Set_Timestep(float time){Current_Timestep = time;}
    static void  Set_Gravity(float g){Gravity = g;}

    static float Get_Timestep(){return Current_Timestep;}
    static float Get_Gravity(){ return Gravity;}
private:
       
    static float Current_Timestep;
    static float Gravity; 
};

class QuadTree;
class Node;

class CollisionSphere{

public:
     CollisionSphere(){}
     CollisionSphere(Vec3 pos, float radius, int parent);
     CollisionSphere(const CollisionSphere &other);

     int ID;
     int ParentID;

     Node *QuadTreeIndex;

     float  Radius;

     Mass Body;

     float  DeltaTime, 
            PresentTime;

//------------ Getters && Setters ------------------------
     void   SetPosition(Vec3 pos)   { Body.Position = pos;}
     void   SetRadius(float radius) { Radius=radius; }
 
     Vec3   GetPosition(){return Body.Position;}
     float  GetRadius(){return Radius;}

//--------------------------------------------------------

     float  Is_Collision(int other);
     void   CollisionDetection();
     void   Update();

    struct convert{
        inline float Pounds_to_Kg  (float lb) { return lb * .453; }
        inline float Newtons_to_Kg (float N)  { return N / 9.8;   }
        inline float Kg_to_Newtons (float Kg) { return Kg * 9.8;  }
    }Convert;

// Static object list
public:
     static std::vector<CollisionSphere*> Collision_ObjectList;
     static unsigned int  Collision_ObjectCount;
//     static OctTree Tree;
 };
#include"Camera.h"
extern int MousePicker(Camera cam, int x, int y);
