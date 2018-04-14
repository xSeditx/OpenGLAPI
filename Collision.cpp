//                                                                                                                                           
//                                           OPENGL 2.0 Abstraction API
//                                                January 24 2018
//                                               -----------------                                                                           
//                                                                                                                                           
//                                        COLLISION AND SIMPLE PHYSICS LIB                                                                    
//==========================================================================================================================


#include"Collision.h"

std::vector<CollisionSphere*> Collider;
unsigned int CollisionSphere::Collision_ObjectCount =0;;


 CollisionSphere::CollisionSphere(Vec3 pos, float radius, int parent)
    : 
      Radius(radius), 
      ParentID(parent),
      ID( Collision_ObjectCount++),
      Force(0,0,0),
      Acceleration(0,0,0),
      Velocity(0,0,0),
      Mass(radius)

{
    Position = pos;
    Collision_ObjectList.push_back(this);
}

 float CollisionSphere::Is_Collision(int otherid)
{ 
    if(Collider[otherid]->ID != this->ID){

     float dist = Position.GetDistance(Collider[otherid]->Position); 

        if(dist  < (Radius + Collider[otherid]->Radius))
        {
            return dist;
        }
    }
    return false;
}
 void  CollisionSphere::CollisionDetection()
 {
     for(CollisionSphere *List: Collider)
     {
         float CollisionDist = Is_Collision(List->ID); // Returns False if Same Object or No Collision

         if(CollisionDist != 0 ){                  // Returns Distance from Colliding object or FALSE for no Collision
                  
             float Displacement = 0.5f * (CollisionDist - Radius - List->Radius);

                    Position -= (Position - List->Position) * Displacement  / CollisionDist;
              List->Position += (Position - List->Position) * Displacement  / CollisionDist;
//            REMINDER: Vec3  -=  (Vec3- Vec3) * Float / Float
             } 
     }
     if (Position.y + Radius >= 0)  Position.y  = -Radius; /// CHEEP GROUND COLLISION DETECTION, Just dont let it go below 0;
 }
 
 void CollisionSphere::Update()
 {
            Velocity = Velocity * .90f ;
            Acceleration = Force / Mass;
            Velocity += Acceleration;
            Position += Velocity;     // Change in Position over time equals Velocity  
            CollisionDetection();
 }
