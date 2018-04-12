#pragma once

#include "Window.h"
#include"3d_Primitive.h"

#include<vector>

 class CollisionSphere{
 public:
     CollisionSphere(Vec3 pos, float radius);

//     Mesh *Object;

     unsigned int ID;
//------------ Getters && Setters ------------------------
     void  SetPosition(Vec3 pos);
     void  SetRadius(float radius){Radius=radius;}
 
     Vec3  GetPosition(){return Position;}
     float GetRadius(){return Radius;}

//--------------------------------------------------------

     bool  Is_Collision(CollisionSphere &other);

 private:
     float Radius;
     Vec3  Position;
// Static object list
 public:
     static std::vector<CollisionSphere*> ObjectList;
     static unsigned int ObjectCount;
 };



 
class AABB{
public: 
    AABB(Vec2 points);

    struct boundingbox{
        Vec3 Corners[8];
        void Set(Vec3 pos, float size);
    }BoundingBox;

    struct{
        Vec3 Location;
        float Radius;
        void Set(Vec3 pos, float radius);
    }BoundingSphere;

    void Merge(AABB other){
	     // const minA:Vector2 = a.m_centre.Sub( a.m_halfExtents );
	     // const maxA:Vector2 = a.m_centre.Add( a.m_halfExtents );
         // 
	     // const minB:Vector2 = b.m_centre.Sub( b.m_halfExtents );
	     // const maxB:Vector2 = b.m_centre.Add( b.m_halfExtents );
         // 
	     // const min:Vector2 = minA.Min(minB);
	     // const max:Vector2 = maxA.Max(maxB);
         // 
	     // const centre:Vector2 = min.Add(max).MulScalar(0.5);
	     // const halfExtents:Vector2 = max.Sub(min).MulScalar(0.5);
         // 
	     // return new AABB( centre, halfExtents );
    }


    static void Merge(AABB first, AABB second);
};

////typedef AABB::Box::Se  Boxes;
// void AABB::boundingbox::Set(Vec3 pos, float size)
//{
//    Corners[0].x = pos.x + size;
//    Corners[0].y = pos.y + size;
//    Corners[0].z = pos.z + size;
//
//}
//