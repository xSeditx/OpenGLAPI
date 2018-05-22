//                                                                                                                                           
//                                           OPENGL 2.0 Abstraction API
//                                                January 24 2018
//                                               -----------------                                                                           
//                                                                                                                                           
//                                        COLLISION AND SIMPLE PHYSICS LIB                                                                    
// 
//
// EFFICIENT DISTANCE COMPUTATION:  https://arxiv.org/ftp/arxiv/papers/1410/1410.4603.pdf
//==========================================================================================================================


#include "Collision.h"
#include "3d_Primitive.h"
#include "Camera.h"


std::vector<CollisionSphere*> Collider;
unsigned int CollisionSphere::Collision_ObjectCount = 0;
float Mass::Current_Timestep;
float Mass::Gravity; 

extern QT *Tree;
Mass::Mass(float weight, Vec3 pos)
    : Force(0,0,0),
      Acceleration(0,0,0),
      Velocity(0,0,0),
      Kg(weight)
{
}

CollisionSphere::CollisionSphere(Vec3 pos, float radius, int parent)
    : 
      Radius(radius), 
      ParentID(parent),
      ID( Collision_ObjectCount++),
      Body(radius, pos)
{
    Collision_ObjectList.push_back(this);
}

 float CollisionSphere::Is_Collision(int otherid)
{ 
    if(Collider[otherid]->ID != this->ID){

     float dist = Body.Position.GetDistance(Collider[otherid]->Body.Position); 

        if(dist  < (Radius + Collider[otherid]->Radius))
        {
            return dist;
        }
    }
    return false;
}

CollisionSphere::CollisionSphere(const CollisionSphere &other)
{
     std::memcpy(this, &other, sizeof(other));
}
//  Young's modulus E = Stress / Strain
//                  k = E * (Area / Length)
// angle_deg = RADIANS(acos(Vec3::DotProduct(VectorA.Normalize(), VectorB.Normalize() ))
// Force =  Axis Displacement   * Spring Factor - Damping Factor
 
 void  CollisionSphere::CollisionDetection()
 {  
     float DamperCoefficient = .1; // Dampening Factor
     float K = 1.;

     //for(CollisionSphere *List: CollisionLIST) //this->QuadTreeIndex->Entities)
     std::vector<CollisionSphere*> results;
     results = Tree->RootNode->QueryRange(Vec2(Body.Position.x, Body.Position.z),Vec2(10,10));

for(CollisionSphere *List: results)
     {

         if(List != this){
         float CollisionDist = Is_Collision(List->ID); // Returns False if Same Object or No Collision

         if(CollisionDist != 0 )
         {                  // Returns Distance from Colliding object or FALSE for no Collision
              float     Displacement = .5f * (CollisionDist - Radius - List->Radius);
              Vec3  AxisDisplacement = (Body.Position - List->Body.Position) * .25;
               
	                Body.Position -= (Body.Position - List->Body.Position) * Displacement  / CollisionDist;
              List->Body.Position += (Body.Position - List->Body.Position) * Displacement  / CollisionDist;
#if 1            
              Body.Force -=       (((AxisDisplacement * (-K)) - (Body.Velocity       * DamperCoefficient)) * .5); 
              List->Body.Force += (((AxisDisplacement * (-K)) - (List->Body.Velocity * DamperCoefficient)) * .5);
#else              
               float m1, m2, x1, x2;
               Vec3 v1temp, v1, v2, v1x, v2x, v1y, v2y, x(Body.Position - List->Body.Position);
               
               x.Normalize();
               v1 = Body.Velocity;
               x1 = x.DotProduct(v1);
               v1x = x * x1;
               v1y = v1 - v1x;
               m1 = Body.Kg;
               
               x = x*-1;
               v2 = List->Body.Velocity;
               x2 = x.DotProduct(v2);
               v2x = x * x2;
               v2y = v2 - v2x;
               m2 = List->Body.Kg;
               
               Body.Velocity = Vec3( v1x*(m1-m2)/(m1+m2) + v2x*(2*m2)/(m1+m2) + v1y );
               List->Body.Velocity = Vec3( v1x*(2*m1)/(m1+m2) + v2x*(m2-m1)/(m1+m2) + v2y );

#endif
         }

     }
     }
     Terrain::GROUND->SampleTerrain(Body.Position.x, 
                                    Body.Position.z, 
                                    Sphere::s_SphereList[ParentID]);
 }
 void  CollisionSphere::Update()
 {
     Body.Velocity = Body.Velocity * .95f ;         

     Vec3  Last_Acceleration = Body.Acceleration;
           Body.Position += Body.Velocity *  Mass::Get_Timestep() + ( Last_Acceleration * 0.5f * Squared(Mass::Get_Timestep()) );
           Body.Acceleration = Body.Force / Body.Kg ;
     Body.Force = 0.0f;
     Vec3  Avg_Acceleration = ( Last_Acceleration + Body.Acceleration ) / 2;
           Body.Velocity += Avg_Acceleration * Mass::Get_Timestep();
   
       CollisionDetection();  
 }

int MousePicker(Camera cam, int x, int y)
{
    Vec3 StartPosition = cam.Position;
    Vec3 EndPosition = Vec3::RayCast(StartPosition, Vec3(0.,0.,0.), 100);
  //  glLineWidth(5.);
    glBegin(GL_LINES);
       /// glVertex3f(0.,0.,0.);
         glVertex3f(100+EndPosition.x,100+EndPosition.y,100+EndPosition.z);
         glVertex3f(100-StartPosition.x,100-StartPosition.y,100-StartPosition.z);
       
       // glVertex3f(10,10,10);
       // glVertex3f(-100,-100,-100);
    glEnd();
    glFlush();
    return 1;
}

//  Acceleration = Force / Mass;
//  Velocity += Acceleration;
//  Position += Velocity;
//  Force = 0.0;