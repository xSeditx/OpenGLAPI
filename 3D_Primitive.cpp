#include "window.h"                                                                                                                 
#include "3D_Primitive.h"                                                                                                           
                                                                                                                                    
#define BUFFER_OFFSET(i) ((char *)NULL + (i))                                                                                       
                                                                                                                                    
#define SphereList   Sphere::s_SphereList  

std::vector<Sphere*> Sphere::s_SphereList;                                                                                          
Terrain *Terrain::GROUND;                                                                                                                                  
unsigned int Sphere::SphereCount = 0;                                                                                               
  
class CollisionSphere;          

                                                                                                                                    
 Sphere::Sphere(Vec3 pos, float radius, int sectors) 
    : Position (pos),
      VertexCount(0),
      ColorCount(0),
      Radius(radius)
      //(Shader("Basic.vert", "Basic.Frag"))
{

   float size = 20;

   float  x=0,   y=0,   z=0;
   float x1=0,  y1=0,  z1=0;
   float x2=0,  y2=0,  z2=0;
   float x3=0,  y3=0,  z3=0;

   for(float Long =0;Long < 180;Long+=size){
        for(float Lat =0;Lat < 360;Lat+=size){
               x = radius * (sin(RADIANS(Lat)) * cos(RADIANS(Long)));
               y = radius * (sin(RADIANS(Lat)) * sin(RADIANS(Long)));
               z = radius *  cos(RADIANS(Lat));
            
               x1 = radius * (sin(RADIANS(Lat + size)) * cos(RADIANS(Long)));
               y1 = radius * (sin(RADIANS(Lat + size)) * sin(RADIANS(Long)));
               z1 = radius *  cos(RADIANS(Lat + size));
            
               x2 = radius * (sin(RADIANS(Lat)) * cos(RADIANS(Long+size)));
               y2 = radius * (sin(RADIANS(Lat)) * sin(RADIANS(Long+size)));
               z2 = radius *  cos(RADIANS(Lat));
            
               x3 = radius * (sin(RADIANS(Lat+ size)) * cos(RADIANS(Long+ size)));
               y3 = radius * (sin(RADIANS(Lat+ size)) * sin(RADIANS(Long+ size)));
               z3 = radius *  cos(RADIANS(Lat+ size));

               Colors[ColorCount].r = GL_Color(x * 255);
               Colors[ColorCount].g = GL_Color(y * 255);
               Colors[ColorCount].b = GL_Color(z * 255);
               Vertices[VertexCount].Coord[0]   =  x ;
               Vertices[VertexCount].Coord[1]   =  y ;
               Vertices[VertexCount].Coord[2]   =  z ;

               Colors[ColorCount + 1].r = GL_Color(x * 255);
               Colors[ColorCount + 1].g = GL_Color(y * 255);
               Colors[ColorCount + 1].b = GL_Color(z * 255);
               Vertices[VertexCount + 1].Coord[0]    =  x1 ;
               Vertices[VertexCount + 1].Coord[1]    =  y1;
               Vertices[VertexCount + 1].Coord[2]    =  z1;

               Colors[ColorCount + 2].r = GL_Color(x * 255);
               Colors[ColorCount + 2].g = GL_Color(y * 255);
               Colors[ColorCount + 2].b = GL_Color(z * 255);
               Vertices[VertexCount + 2].Coord[0]    =  x2 ;
               Vertices[VertexCount + 2].Coord[1]    =  y2 ;
               Vertices[VertexCount + 2].Coord[2]    =  z2 ;

               Colors[ColorCount + 3].r = GL_Color(x * 255);
               Colors[ColorCount + 3].g = GL_Color(y * 255);
               Colors[ColorCount + 3].b = GL_Color(z * 255);
               Vertices[VertexCount + 3].Coord[0]    =  x3 ;
               Vertices[VertexCount + 3].Coord[1]    =  y3 ;
               Vertices[VertexCount + 3].Coord[2]    =  z3 ;

               VertexCount += 4;
               ColorCount  += 4;
        }
   }

   Vbo = Buffer(Vertices, Colors, VertexCount, ColorCount);
   Mesh_ID = SphereCount++;
   CollisionID = MakeCollisionSphere(Position, Radius, Mesh_ID);

   SphereList.push_back(this);
}                                                                       
                                                                                                                                    
void Sphere::Update ()                                                                                                              
 {                                                                                                                                  
   Collider[CollisionID]->Update();   
   Set_Position(  Collider[CollisionID]->Body.Position);        
 //  float Unit = Collider[CollisionID]->Body.Velocity.z  / (2 * M_PI * Radius)
       // (Collider[CollisionID]->Body.Velocity.z  / (2 * M_PI * Radius)) * M_PI /180;

    


   Rotation.x -=  (Collider[CollisionID]->Body.Velocity.z / (2 * M_PI * Radius)) * 360.0f;//(Collider[CollisionID]->Body.Velocity.z  / (2 * M_PI * Radius)) * M_PI /180; ;   //(Squared(Radius) * M_PI );              //atan2f(Position.z - (Position.z +  Collider[CollisionID]->Body.Velocity.z), 
   Rotation.z -=  (Collider[CollisionID]->Body.Velocity.x / (2 * M_PI * Radius)) * 360.0f;//(Collider[CollisionID]->Body.Velocity.x  / (2 * M_PI * Radius)) * M_PI /180; ;   //(Squared(Radius) * M_PI );                                    //       Position.x + (Position.x +  Collider[CollisionID]->Body.Velocity.x));                                                                                                                            

//   1 full rotation is 3 * radius
}                                                                                                                                   
// x = x + dist * cos(angle) 

//  circumference = 2 * M_PI * Radius
//  roll_in_degrees = (distance / circumference) * 360 degrees;
//  roll_in_radians = (distance / circumference) * pi/180; 
//glRotated(roll_in_degrees, forward_roll_percent, sideways_roll_percent, 0);




void Sphere::Render ()
{

  glPushMatrix();
     glTranslatef(Position.x,  Position.y, Position.z);
     glRotatef(Rotation.x, 1,0,0);
     glRotatef(Rotation.z, 0,0,1);
     glRotatef(Rotation.y, 0,1,0);
 
     Vbo.Bind();
          glDrawArrays(GL_TRIANGLE_STRIP, 0, VertexCount);
      Vbo.Unbind();
  glPopMatrix();
}                                                                                                     
                                                                                                                                    
void Sphere::ChangeVert (int index, Vec3 newpos)
{
    Vertices[index] = newpos;
}                                                                           
                                                                                                                                    
void Sphere::Submit (Vec3 *data)
{
// In DirectX MapBuffer Moves the Vertex Buffer to the CPU
// DX CODE: Vbo->Map(Buffer_ID, 0 , Map Write Discoard, 0 , &MappedResource<- returns the buffer);
// So I need OpenGL Map Buffer code;
   Vbo = Buffer(data, Colors, VertexCount, ColorCount);
}                                                                                           
                                                                                                                                    
int  Sphere::MakeCollisionSphere (Vec3 pos, float rad, int p)
{
    CollisionSphere *Bounds = new CollisionSphere(pos, rad, p);

    Bounds->Body.Position = pos;
    Bounds->Radius   = rad;
    Bounds->ParentID = p;

    return Bounds->ID;
}                                                              

void Sphere::Rotate(float x, float y, float z)
{
    Rotation.x += x;
    Rotation.y += y;
    Rotation.z += z;
}




//================================================================================================================================= 
//______________________________________ TERRAIN __________________________________________________________________________________ 
//================================================================================================================================= 
                      



Terrain::~Terrain(){
       delete( Vertices); 
       delete( Colors  ); 
//       delete( Normals ); 
}                                                                                                        
                                                                                                                                    
                                                                                                                                    
Terrain::Terrain(int w, int d, int gw, int gd)
       : Position(-(w * .5) ,0 ,-(d * .5)),
         width   (w), 
         depth   (d), 
         gridw   (gw), 
         gridd   (gd), 
         VertexCount(0.0f), 
         ColorsCount(0.0f),
         NormalCount(0.0f)
{        
    Vertices = new Vec3[ (w) * (d)];
    Colors   = new Vec3[ (w) * (d)];
    Normals  = new Vec3[ (w - 1) * (d - 1) * 2];
    Indices  = new GLushort[(w * d * 3) * 2];
    Data     = new MetaData[(w) * (d)];


    Vec3 Origin;
    Origin.x = Position.x / 2;
    Origin.y = Position.y;
    Origin.z = Position.z / 2;


    float FinalHeight =0;
//--------------------------------------------- CALCULATE VERTICES -------------------------------------------------------------------------
  float H1 = 1, H2 = 1, H3 = 1, H4 = 1;
    
    for_loop(Z, d )
    {
           
        for_loop(X , w)
        {
            if(X % 10 > 5 && Z % 10 > 5) H1  = (-20); else H1 = 0;//RANDOM(-20); else H1 = 0; //-= RANDOM(5) - 2.5;
            if(X % 10 > 2 && Z % 10 > 2) H2  = ( -5); else H2 = 0;//RANDOM( -5); else H2 = 0;   
            if(X % 10 > 3 && Z % 10 > 3) H3 =  (-10); else H3 = 0;//RANDOM(-10); else H3 = 0;

            Vertices[VertexCount].x = X * gw;
            Vertices[VertexCount].y = H1 + H2 + H3 + H4 ;//X * Y / 2; //<-- Just debug so I know what Vertex it is
            Vertices[VertexCount].z = Z * gd;

            Colors[ColorsCount].r = GL_Color((ColorsCount % 4) * 64);
            Colors[ColorsCount].g = GL_Color(((ColorsCount +1) % 4)* 64);
            Colors[ColorsCount].b = GL_Color(((ColorsCount +2) % 4)* 64);

          VertexCount++;
          ColorsCount++;
        }
    }
    Vertices[Get_Vertex(0,0)] = (0.,0.,0.);
    Vertices[Get_Vertex(1,0)] = (1.,0.,0.);
    Vertices[Get_Vertex(0,1)] = (0.,1.,0.);
    Vertices[Get_Vertex(1,1)] = (1.,1.,0.);

// --------------------------------------------- CALCULATE INDICES ------------------------------------------------------------------------
    IndexCount =0;

    for_loop(Y, w - 1){
        for_loop(X , d - 1){
            Indices[IndexCount    ] =    X      + w *  Y ;     // 1
            Indices[IndexCount + 1] =   (X + 1) + w *  Y;      // 2
            Indices[IndexCount + 2] =    X      + w * (Y + 1); // 4
                                                               
            Indices[IndexCount + 3] =   (X + 1) + w * (Y + 1); // 3
            Indices[IndexCount + 4] =    X      + w * (Y + 1); // 4
            Indices[IndexCount + 5] =   (X + 1) + w * Y;       // 2

            IndexCount+=6;
        }
    }

// --------------------------------------------- CALCULATE NORMALS ---------------------------------------------------------------------   

    for_loop(Y, d  - 1){
        for_loop(X , w - 1){
            Normals[NormalCount]   = Vec3::GetNormal(Vertices[Get_Vertex(X,Y)],           // 1 
                                                     Vertices[Get_Vertex(X + 1,Y)],       // 2 
                                                     Vertices[Get_Vertex(X,Y + 1)]);      // 4 
                                     
            Normals[NormalCount + 1] = Vec3::GetNormal(Vertices[Get_Vertex(X + 1,Y + 1)], // 3
                                                       Vertices[Get_Vertex(X,Y + 1)],     // 4
                                                       Vertices[Get_Vertex(X + 1,Y)]);    // 2
            NormalCount += 2;   
//            Data[NormalCount].Normals     = Normals[NormalCount] ;
 //           Data[NormalCount + 1].Normals = Normals[NormalCount + 1];
        }
    }      

// ---------------------------------------------- Allocate Buffers ----------------------------------------------------------------------------   

   Vbo = Buffer(Vertices, Colors, Normals,  VertexCount, ColorsCount, NormalCount);
   Ibo = IndexBuffer(Indices,IndexCount);
}                                                                             
                                                                                                                                    
                                                                                                                                    
                                                                                                                                    
                                                                                                                                    
float Terrain::Lerp(float a, float b, float c)
{
    return (1.0 - c) * a + b * c;
}                                                                             
                                                                                                                                    
void Terrain::Render()
{

   glPushMatrix();
      glTranslatef(Position.x ,  Position.y , Position.z );

      Vbo.Bind();
          glBindBuffer(GL_ARRAY_BUFFER, Vbo.ID[2]);
          glNormalPointer(GL_FLOAT,0,(char *) NULL);
          glEnableClientState(GL_NORMAL_ARRAY);
          Ibo.Bind();
              glDrawElements(GL_TRIANGLES , IndexCount , GL_UNSIGNED_SHORT, nullptr);
          Ibo.Unbind();
      Vbo.Unbind();
  glPopMatrix();
}                                                                                                     
                                                                                                                          
float Terrain::SampleTerrain(float x, float z, Sphere *ball) 
{
    
    int ax = 0;
    int az = 0;

    int bx = 0;
    int bz = 0;

    float fracX = 0;
    float fracY = 0;

    float sx = 0;
    float sz = 0;

    float tl = 0;
    float tr = 0;
    Vec2 Top(0,0);


    float bl = 0;
    float br = 0;
    Vec2 Bottom(0,0);

    float Height = 0;


    x += (width * .5f); //Assume that grid's center is at the origin. 
    z += (depth * .5f);
    
    if(x < 0.0f || x > width * gridw ||  z < 0.0f ||  z > depth * gridd)  
        return -FLT_MAX;

    sx = x / (float)gridw; // NOTES:Translates Position to Grid Space.
    sz = z / (float)gridd; //

        ax = (int)sx  ;
        az = (int)sz  ;
        
        bx =  min(ax+1, width);
        bz =  min(az+1, depth);
        
        fracX = sx - ax;
        fracY = sz - az; 
        
        Top.x = Vertices[ax + az * width].y;   //tl  1    We're going to need these for linearily interpolate over a square
        Top.y = Vertices[bx + az * width].y;   //tr  2    {
                                               //      
        Bottom.x = Vertices[ax + bz*width].y;  //bl  3     
        Bottom.y = Vertices[bx + bz*width].y;  //br  4    }
   
    // 2 ---- 3
    //  | \   |
    //  |   \ |
    // 1 ---- 4       


        Height = Lerp(Lerp(Top.x, Top.y, fracX),
                 Lerp(Bottom.x, Bottom.y, fracX), fracY); // Lerp between the left .. right values  

   // if(Collider[ball->CollisionID]->Body.Position.y - (Normals[ax + az*width].y * ball->Radius)  > 0.0)  
   //     Collider[ball->CollisionID]->Body.Position +=  ((Normals[ax + az*width] * (ball->Radius))) ; 
      
    //   int px = (int)(x * 10000000) % (gridw* 10000000), pz = (int)(z* 10000000) % (gridd * 10000000) ;
    //  
    //  // if( x < z)
    //  {
    //     Normals[(ax + az) *width * 2].y = -20;
    //  }
    //  //else
    //  {
    //      Normals[(ax + az )* width * 2 + 1].y = 20;                                                                                                           //////////Normals[(((int)(x/ gridw)) + (width*2) * ((int)(z/ gridd)))+1] = 20;
    //  }
    //

    return  Height ;
  
    // tl ---- tr
    //  |      |
    //  |      |
    // bl ---- br

}                                                      
                                                                                       
Vec3 Terrain::CollisionDetection(CollisionSphere ball)
{
    Vec3 Pos = ball.Body.Position;
    Pos.x += (width * .5f); //Assume that grid's center is at the origin. 
    Pos.z += (depth * .5f);
    
    if(Pos.x < 0.0f || Pos.x > width * gridw ||  Pos.z < 0.0f ||  Pos.z > depth * gridd) return Vec3(-FLT_MAX,-FLT_MAX,-FLT_MAX);

    float sx = Pos.x / (float)gridw; // NOTES:Translates Position to Grid Space.
    float sz = Pos.z / (float)gridd; //
    
    int ax = (int)sx  ;
    int az = (int)sz  ;

    int bx = min(ax + 1, gridw);
    int bz = min(az + 1, gridd);

}                                                                     



                                                                                                        
//================================================================================================================================= 
//_________________________________________________________________________________________________________________________________ 
//================================================================================================================================= 
                                                                                                                                    
                                                                                                                                    
                                                                                                                                    
                                                                                                                                    
                                                                                                                                    
                                                                                                                                    
                                                                                                                                    
 Torus::Torus(int numc, int numt, float X, float Y, float Z, float scale)                                                           
{                                                                                                                                   
    Scale.x = scale;                                                                                                                
    Scale.y = scale;                                                                                                                
    Scale.z = scale;                                                                                                                
    Position.x = X;                                                                                                                 
    Position.y = Y;                                                                                                                 
    Position.z = Z;                                                                                                                 
        ObjectType = Torus_t;                                                                                                       
    List = glGenLists(1);                                                                                                           
   glNewList(List, GL_COMPILE);                                                                                                     
                                                                                                                                    
   int i, j, k;                                                                                                                     
   double s, t, x, y, z, twopi;                                                                                                     
                                                                                                                                    
   twopi = 2 * (double)M_PI;                                                                                                        
                                                                                                                                    
   for (i = 0; i < numc; i++) {                                                                                                     
      glBegin(GL_QUAD_STRIP);                                                                                                       
      for (j = 0; j <= numt; j++) {                                                                                                 
         for (k = 1; k >= 0; k--) {                                                                                                 
            s = (i + k) % numc + 0.5;                                                                                               
            t = j % numt;

            x = (1+.1*cos(s*twopi/numc))*cos(t*twopi/numt);
            y = (1+.1*cos(s*twopi/numc))*sin(t*twopi/numt);
            z = .1 * sin(s * twopi / numc);

            glColor3f(GL_Color(x* 255.0),GL_Color(y* 255.0),GL_Color(z * 255.0));
            glVertex3f(x ,y, z);
         }
      }
      glEnd();
   }
   glEndList();
}

 void Torus::Rotate(float x, float y, float z){
    Rotation.x+=x;
    Rotation.y+=y;
    Rotation.z+=z;
}
 void Torus::Set_Position(float x, float y, float z){
    Position.x=x;
    Position.y=y;
    Position.z=z;
}
 void Torus::Render(){

glPushMatrix();

  glScalef(Scale.x,Scale.y,Scale.z);
  glRotatef(Rotation.x, 1.0, 0.0, 0.0);
  glRotatef(Rotation.y, 0.0, 1.0, 0.0);
  glRotatef(Rotation.z, 0.0, 0.0, 1.0);

    glTranslatef(Position.x, 0.0f, 0.0f);
    glTranslatef(0.0f, Position.y, 0.0f);
    glTranslatef(0.0f, 0.0f, Position.z);
    glCallList(List);
glPopMatrix();

}





 void Mesh::Render(){

_GL(glPushMatrix());

_GL(  glScalef(Scale.x,Scale.y,Scale.z));
_GL(  glRotatef(Rotation.x, 1.0, 0.0, 0.0));
_GL(  glRotatef(Rotation.y, 0.0, 1.0, 0.0));
_GL(  glRotatef(Rotation.z, 0.0, 0.0, 1.0));

_GL(    glTranslatef(Position.x, 0.0f, 0.0f));
_GL(    glTranslatef(0.0f, Position.y, 0.0f));
 _GL(   glTranslatef(0.0f, 0.0f, Position.z));
 _GL(   glCallList(List));
_GL(glPopMatrix());

}
 Cube::Cube(Vec3 pos, float size)
{
    List = glGenLists(1);
    Position = pos;
    ObjectType = Cube_t;
   _GL( glNewList(List, GL_COMPILE));
       _GL(   glBegin(GL_QUADS));       
       _GL(    glColor3f(GL_Color(255.0 / size),GL_Color(255.0 / size),GL_Color(255.0 / size)));
            _GL(       glVertex3f(-1.0f * size, -1.0f * size, -1.0f * size));  
               _GL(    glVertex3f( 1.0f * size, -1.0f * size, -1.0f * size));  
              _GL(     glVertex3f( 1.0f * size, -1.0f * size,  1.0f * size));  
              _GL(     glVertex3f(-1.0f * size, -1.0f * size,  1.0f * size));  
                                                                        
              _GL(     glVertex3f(-1.0f * size, -1.0f * size,  1.0f * size));  
              _GL(     glVertex3f( 1.0f * size, -1.0f * size,  1.0f * size));  
              _GL(     glVertex3f( 1.0f * size,  1.0f * size,  1.0f * size));  
              _GL(     glVertex3f(-1.0f * size,  1.0f * size,  1.0f * size));  
                                                                        
             _GL(      glVertex3f(-1.0f * size, -1.0f * size, -1.0f * size));  
             _GL(      glVertex3f(-1.0f * size,  1.0f * size, -1.0f * size));  
             _GL(      glVertex3f( 1.0f * size,  1.0f * size, -1.0f * size));  
             _GL(      glVertex3f( 1.0f * size, -1.0f * size, -1.0f * size));  
                                                                        
            _GL(       glVertex3f( 1.0f * size, -1.0f * size, -1.0f * size));  
            _GL(       glVertex3f( 1.0f * size,  1.0f * size, -1.0f * size));  
            _GL(       glVertex3f( 1.0f * size,  1.0f * size,  1.0f * size));  
             _GL(      glVertex3f( 1.0f * size, -1.0f * size,  1.0f * size));  
                                                                        
             _GL(      glVertex3f(-1.0f * size, -1.0f * size, -1.0f * size));  
             _GL(      glVertex3f(-1.0f * size, -1.0f * size,  1.0f * size));  
              _GL(     glVertex3f(-1.0f * size,  1.0f * size,  1.0f * size));  
             _GL(      glVertex3f(-1.0f * size,  1.0f * size, -1.0f * size));  
       _GL(   glEnd());     
   _GL(   glEndList());
}
 void Cube::Render(){
    glPushMatrix();
   
    glScalef(Scale.x,Scale.y,Scale.z);
    glRotatef(Rotation.x, 1.0, 0.0, 0.0);
    glRotatef(Rotation.y, 0.0, 1.0, 0.0);
    glRotatef(Rotation.z, 0.0, 0.0, 1.0);
   
    glTranslatef(Position.x, 0.0f, 0.0f);
    glTranslatef(0.0f, Position.y, 0.0f);
    glTranslatef(0.0f, 0.0f, Position.z);
    glCallList(List);
    glPopMatrix();

}



