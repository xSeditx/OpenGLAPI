
#include"Collision.h"

std::vector<CollisionSphere*> CollisionSphere::ObjectList;
unsigned int CollisionSphere::ObjectCount;
//
//
//
//
//CollisionSphere::CollisionSphere(Vec3 pos, float radius): Position(pos), Radius(radius), ID(ObjectCount++)
//{
//    ObjectList.push_back(this);
//}
//
//void CollisionSphere::SetPosition(Vec3 pos)
//{
//    Position = pos;
//}
//
//
//
//bool  CollisionSphere::Is_Collision(CollisionSphere &other)
//{
//    for(CollisionSphere *&Obj: ObjectList)
//    {
//        if( Object->Position.GetDistance( Obj->Object->Position) < Radius)
//        {
//            Print("Collision");
//            return true;
//        }
//    }
//    return false;
//}