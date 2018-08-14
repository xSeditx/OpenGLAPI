#include "window.h"                                                                                                                 
#include "3D_Primitive.h"                                                                                                           
                                                                                                                                    
#define BUFFER_OFFSET(i) ((char *)NULL + (i))                                                                                       
                                                                                                                                    
#define SphereList   Sphere::s_SphereList  
std::vector<Sphere*> Sphere::s_SphereList;          


Terrain *Terrain::GROUND;                                                                                                                                  
unsigned int Sphere::SphereCount = 0;                                                                                               

std::vector<Vec3>   Sphere::B_Vertices;
std::vector<GLuint> Sphere::B_Indices;
std::vector<RGBf>   Sphere::B_Colors; 

bool Sphere::BatchMade;

VAOBuffer Sphere::BatchVAO;

class CollisionSphere; 

using namespace std;
                                                                                                                                    
 Sphere::Sphere(Vec3 pos, float radius, int sectors) 
    : Position (pos),
      VertexCount(0),
      ColorCount(0),
      Radius(radius)
      //(Shader("Basic.vert", "Basic.Frag"))
{
   BatchMade = false;

   float size = 20;
   int IndexCount =0;
   float  x=0,   y=0,   z=0;
   float x1=0,  y1=0,  z1=0;
   float x2=0,  y2=0,  z2=0;
   float x3=0,  y3=0,  z3=0;
   std::vector<GLuint> Ind;
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


               Ind.push_back(VertexCount); 
               Ind.push_back(VertexCount + 1); 
               Ind.push_back(VertexCount + 2);

               Ind.push_back(VertexCount + 1); 
               Ind.push_back(VertexCount + 3); 
               Ind.push_back(VertexCount + 2);

               Indices[IndexCount]   = VertexCount;
               Indices[IndexCount+1] = VertexCount + 1;
               Indices[IndexCount+2] = VertexCount + 2;

               Indices[IndexCount+3] = VertexCount + 1;
               Indices[IndexCount+4] = VertexCount + 3;
               Indices[IndexCount+5] = VertexCount + 2;


               VertexCount += 4;
               ColorCount  += 4;
               IndexCount += 6;
        }
   }

   VAO.Vertices = new VertexBuffer(Vertices, VertexCount);
   VAO.Indices  = new IndexBuffer(Indices, IndexCount);
   VAO.Colors   = new ColorBuffer(Colors, ColorCount);

   Mesh_ID = SphereCount++;
   CollisionID = MakeCollisionSphere(Position, Radius, Mesh_ID);

   SphereList.push_back(this);
}                                                                       
                                                                                                                                    
void Sphere::Update ()                                                                                                              
{                                                                                                                                  
    Collider[CollisionID]->Update();   
    Set_Position( Collider[CollisionID]->Body.Position);        
    Rotation.x -= (Collider[CollisionID]->Body.Velocity.z / (2 * M_PI * Radius)) * 360.0f;//(Collider[CollisionID]->Body.Velocity.z  / (2 * M_PI * Radius)) * M_PI /180; ;   //(Squared(Radius) * M_PI );              //atan2f(Position.z - (Position.z +  Collider[CollisionID]->Body.Velocity.z), 
    Rotation.z -= (Collider[CollisionID]->Body.Velocity.x / (2 * M_PI * Radius)) * 360.0f;//(Collider[CollisionID]->Body.Velocity.x  / (2 * M_PI * Radius)) * M_PI /180; ;   //(Squared(Radius) * M_PI );                                    //       Position.x + (Position.x +  Collider[CollisionID]->Body.Velocity.x));                                                                                                                            
}                                    
 
void Sphere::Render ()
{

  glPushMatrix();
      glTranslatef(Position.x,  Position.y, Position.z);
      glRotatef(Rotation.x, 1,0,0);
      glRotatef(Rotation.z, 0,0,1);
      glRotatef(Rotation.y, 0,1,0);
      VAO.Bind();
         glDrawArrays(GL_TRIANGLE_STRIP, 0, VertexCount);
        //glDrawElements(GL_TRIANGLES, VAO.Indices->ElementCount , GL_UNSIGNED_INT, nullptr);
      VAO.Unbind();
  glPopMatrix();
}                                                                                                     
                                                                                                                                    
void Sphere::ChangeVert (int index, Vec3 newpos)
{
    Vertices[index] = newpos;
}                                                                           
                                                                                                                                    
void Sphere::Submit ()
{
// In DirectX MapBuffer Moves the Vertex Buffer to the CPU
// DX CODE: Vbo->Map(Buffer_ID, 0 , Map Write Discoard, 0 , &MappedResource<- returns the buffer);
// So I need OpenGL Map Buffer code;
// Vbo = Buffer(data, Colors, VertexCount, ColorCount);

//    int Vcount = 0,
//        Icount = 0,
//        Ccount = 0;
//
//        for_loop(V, VAO.Vertices->ElementCount)
//        {
//            B_Vertices.push_back(VAO.Vertices->Data[V] + S->Position);
//            B_Colors.push_back(VAO.Colors->Data[V]);
//            Vcount++; // Change this later to just add the total number of Elements all at once
//            Ccount++;
//        }
//
//        for_loop(I, VAO.Indices->ElementCount)
//        {
//            B_Indices.push_back(VAO.Indices->Data[I] + Icount);
//        }
//
//// Add the amount of Vertices to the Index number as each sphere is going to be offset by that amount
//        Icount += VAO.Vertices->ElementCount;
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


//--------------------------------- SPHERE BATCH RENDERING STUFF -----------------------------
void Sphere::Batch()
{
    int Vcount = 0,
        Icount = 0,
        Ccount = 0;

    if (!BatchMade)
    { // Update the Data if a new Sphere has been Spawned
        
    }

    for(auto &S: SphereList)
    {
        S->Update();
        Collider[S->CollisionID]->Body.Velocity.y += Mass::Get_Gravity(); // Cheep gravity

        for_loop(V, S->VAO.Vertices->ElementCount)
        {
            BatchVAO.Vertices->Data[Vcount] = (S->VAO.Vertices->Data[V] + S->Position);
            Vcount++; // Change this later to just add the total number of Elements all at once
        }
    }

    glPushMatrix();
    BatchVAO.Vertices->Rebuild();
    BatchVAO.Bind();
        glDrawElements(GL_TRIANGLES , BatchVAO.Indices->ElementCount , GL_UNSIGNED_INT, nullptr);
    BatchVAO.Unbind();
    glPopMatrix();
}
void Sphere::BatchBuild()
{

    BatchMade = true;
    B_Vertices.clear();
    B_Indices.clear();
    B_Colors.clear(); 

    int Vcount = 0,
        Icount = 0,
        Ccount = 0;

    for(auto &S: SphereList)
    {

        S->Update();
        Collider[S->CollisionID]->Body.Velocity.y += Mass::Get_Gravity(); // Cheep gravity

        for_loop(V, S->VAO.Vertices->ElementCount)
        {
            B_Vertices.push_back(S->VAO.Vertices->Data[V] + S->Position);
            B_Colors.push_back(S->VAO.Colors->Data[V]);
            Vcount++; // Change this later to just add the total number of Elements all at once
            Ccount++;
        }

        for_loop(I, S->VAO.Indices->ElementCount)
        {
            B_Indices.push_back(S->VAO.Indices->Data[I] + Icount);
        }
// Add the amount of Vertices to the Index number as each sphere is going to be offset by that amount
        Icount+=S->VAO.Vertices->ElementCount;
    }

    BatchVAO.Vertices    = new VertexBuffer(&B_Vertices[0], Vcount);
    BatchVAO.Colors      = new ColorBuffer(&B_Colors[0],    Ccount);
    BatchVAO.Indices     = new IndexBuffer(&B_Indices[0],   Icount);
}

//--------------------------------------------------------------------------------------------


//================================================================================================================================= 
//______________________________________ TERRAIN __________________________________________________________________________________ 
//================================================================================================================================= 


Terrain::~Terrain(){
//       delete[]( Vertices); 
//       delete[]( Colors  ); 
//       delete[]( Normals ); 
}                                                                                                        
void Terrain::Delete()
{
}
                                                                                                                                    
Terrain::Terrain(int w, int d, int gw, int gd)
       : Position(-(w * .5) ,0 ,-(d * .5)),
         width   (w), 
         depth   (d), 
         gridw   (gw), 
         gridd   (gd), 
         VertexCount(0.0f), 
         ColorsCount(0.0f),
         NormalCount(0.0f),
         IndexCount (0.0f)
{        

    Vec3 *Vertices     = new Vec3[ (w) * (d)];
    RGBf *Colors      = new Vec3[ (w) * (d)];
    Vec3 *Normals     = new Vec3[ (w - 1) * (d - 1) * 2];
    GLushort *Indices = new GLushort[(w * d * 3) * 2];

//    Data = new MetaData[(w) * (d)];

    Vec3 Origin;
    Origin.x = Position.x / 2;
    Origin.y = Position.y;
    Origin.z = Position.z / 2;

    float FinalHeight = 0;
//--------------------------------------------- CALCULATE VERTICES -------------------------------------------------------------------------
    float H1 = 1, H2 = 1, H3 = 1, H4 = 1;
    
    for_loop(Z, d )
    {
        for_loop(X , w)
        {
      //    if(X % 10 > 5 && Z % 10 > 5) H1  = (-20); else H1 = 0;//RANDOM(-20); else H1 = 0; //-= RANDOM(5) - 2.5;
      //    if(X % 10 > 2 && Z % 10 > 2) H2  = ( -5); else H2 = 0;//RANDOM( -5); else H2 = 0;   
      //    if(X % 10 > 3 && Z % 10 > 3) H3  = (-10); else H3 = 0;//RANDOM(-10); else H3 = 0;
            Vertices[VertexCount].x = X * gw;
            Vertices[VertexCount].y = H1 + H2 + H3 + H4; //X * Y / 2; //<-- Just debug so I know what Vertex it is
            Vertices[VertexCount].z = Z * gd;

            Colors[ColorsCount].r = GL_Color((ColorsCount % 4) * 64);
            Colors[ColorsCount].g = GL_Color(((ColorsCount +1) % 4)* 64);
            Colors[ColorsCount].b = GL_Color(((ColorsCount +2) % 4)* 64);

             VertexCount++;
             ColorsCount++;
        }
    }
// --------------------------------------------- CALCULATE INDICES ------------------------------------------------------------------------
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

   VAO.Vertices = new VertexBuffer(Vertices, VertexCount);
   VAO.Indices  = new IndexBuffer((GLuint*)Indices, IndexCount);
   VAO.Colors  = new ColorBuffer(Colors, ColorsCount);
   VAO.Normals = new NormalBuffer(Normals, NormalCount);
   delete[](Colors);
}                                                                             
                                                                                                                                    
                                                                                                                                    
float Terrain::Lerp(float a, float b, float c)
{
    return (1.0 - c) * a + b * c;
}                                                                             
                                                                                                                                    
void Terrain::Render()
{

    glPushMatrix();
        glTranslatef(Position.x ,  Position.y , Position.z );
        VAO.Bind();
            glDrawElements(GL_TRIANGLES , VAO.Indices->ElementCount , GL_UNSIGNED_SHORT, nullptr);
        VAO.Unbind();
    glPopMatrix();


    int NCount = 0, 
        VCount = 0,
        count  = 0;

    Vec3 pos,
         pos2;

    float t = 5;

    for_loop(Y, depth - 1)
    {
        for_loop(X , width - 1)
        {
        //===================================================================
            pos =  VAO.Vertices->Data[ Get_Vertex(X, Y)]     +                     // 1 
                   VAO.Vertices->Data[ Get_Vertex(X + 1, Y)] +                     // 2 
                   VAO.Vertices->Data[ Get_Vertex(X,Y + 1)];                       // 4 
            pos = pos / 3;                                               

        //====================================================================   
            pos2 =  VAO.Vertices->Data[ Get_Vertex(X + 1, Y + 1)] +                 // 3
                    VAO.Vertices->Data[ Get_Vertex(X    , Y + 1)] +                 // 4
                    VAO.Vertices->Data[ Get_Vertex(X + 1, Y)];                      // 2
            pos2 = pos2 / 3;

        //===========================================================================================
                glBegin(GL_LINES);
                    glColor3f(GL_Color(255),GL_Color(0),GL_Color(0));
                    glVertex3f( Position.x + pos.x,
                                Position.y + pos.y,
                                Position.z + pos.z);
                    glVertex3f( Position.x + pos.x +  VAO.Normals->Data[NCount].x * (t),
                                Position.y + pos.y +  VAO.Normals->Data[NCount].y * (t),
                                Position.z + pos.z +  VAO.Normals->Data[NCount].z * (t));
                 
                   glColor3f(GL_Color(0),GL_Color(255),GL_Color(0));
                   glVertex3f( Position.x + pos2.x,
                               Position.y + pos2.y,
                               Position.z + pos2.z);
                   glVertex3f( Position.x + pos2.x +  VAO.Normals->Data[NCount + 1].x * (t),
                               Position.y + pos2.y +  VAO.Normals->Data[NCount + 1].y * (t),
                               Position.z + pos2.z +  VAO.Normals->Data[NCount + 1].z * (t));
                 glEnd();
//===========================================================================================
         VCount++;
         NCount = VCount * 2;

        }
    }      
}                                                                                                     

Vec3 Terrain::TerrainNormal(float x, float y)
{
    return VAO.Normals->Data[int(((int)(x / (float)gridw) + (width - 1)* (int)(y / (float)gridd)) * 2)];     
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
    float bl = 0;
    float br = 0;
    float Height = 0;

    Vec2 Top(0,0);
    Vec2 Bottom(0,0);


    float Nx = x / (float)gridw,
          Ny = z / (float)gridd;

    int NX = (int)Nx,
        NY = (int)Ny;

 //Assume that grid's center is at the origin. 
    x += (width * .5f);
    z += (depth * .5f);
    
    if(x < 0.0f || x > width * gridw ||  z < 0.0f ||  z > depth * gridd)  
    {
        return -FLT_MAX;
    }

    sx = x / (float)gridw; // NOTES:Translates Position to Grid Space.
    sz = z / (float)gridd; //

    ax = (int)sx;
    az = (int)sz;
    
    bx =  min(ax+1, width);
    bz =  min(az+1, depth);
    
    fracX = sx - ax;
    fracY = sz - az; 
    
    Top.x = VAO.Vertices->Data[ax + az * width].y;   //tl  1    We're going to need these for linearily interpolate over a square
    Top.y = VAO.Vertices->Data[bx + az * width].y;   //tr  2    {
                                               //      
    Bottom.x = VAO.Vertices->Data[ax + bz*width].y;  //bl  3     
    Bottom.y = VAO.Vertices->Data[bx + bz*width].y;  //br  4    }
    
    Height = Lerp(Lerp(   Top.x,    Top.y, fracX), 
                  Lerp(Bottom.x, Bottom.y, fracX),
                                           fracY); // Lerp between the left .. right values  
    
//int modx = int(x * 100000) % (gridw * 100000) / 100000;
//int modz = int(z * 100000) % (gridd * 100000) / 100000;
    int modx = int(x) % (gridw);
    int modz = int(z) % (gridd);

    Vec3 Norms;
    if((modz+ modx) <  gridw)
    {
           Norms = VAO.Normals->Data[int((ax + (width - 1)* az) * 2) ];
    }
    else
    {
           Norms = VAO.Normals->Data[int((ax + (width - 1)* az) * 2)  + 1];
    }
    
// Preserve the Y Force, Find the Normal response Vector
    float y = Collider[ball->CollisionID]->Body.Force.y;

    if (Collider[ball->CollisionID]->Body.Position.y + Collider[ball->CollisionID]->Radius >=  Height)
    {
        Collider[ball->CollisionID]->Body.Force += Norms;
        Collider[ball->CollisionID]->Body.Force.y = y;
        Collider[ball->CollisionID]->Body.Position.y = Height - Collider[ball->CollisionID]->Radius;
    }
    return  Height ;
// tl ---- tr
//  |      |
//  |      |
// bl ---- br
//
// 2 ---- 3
//  | \   |
//  |   \ |
// 1 ---- 4       
}    
                                                                                       
Vec3 Terrain::CollisionDetection(CollisionSphere ball)
{
    Vec3 Pos = ball.Body.Position;

//Assume that grid's center is at the origin. 
    Pos.x += (width * .5f);
    Pos.z += (depth * .5f);
    
    if(Pos.x < 0.0f || Pos.x > width * gridw ||  Pos.z < 0.0f ||  Pos.z > depth * gridd)
    {
         return Vec3(-FLT_MAX,-FLT_MAX,-FLT_MAX);
    }

    float sx = Pos.x / (float)gridw; // NOTES:Translates Position to Grid Space.
    float sz = Pos.z / (float)gridd; //
    
    int ax = (int)sx;
    int az = (int)sz;

    int bx = min(ax + 1, gridw);
    int bz = min(az + 1, gridd);
  return Vec3(0,0,0);
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











//
//void GenerateSphere(int rings = 10, int sectors = 10, float fRadius =3.0f)
//{
//        float const R = 1. / (float)(rings - 1);
//        float const S = 1. / (float)(sectors - 1);
//        int r, s;
//
//        // Vertex pool
//        vector<Vec3> verts;
//        verts.resize(rings * sectors * 3);        
//        std::vector<Vec3>::iterator v = verts.begin();
//
//        std::vector<Vec3> VertexData;
//
//        for (r = 0; r < rings; r++) 
//        {
//            for (s = 0; s < sectors; s++) 
//            {
//                float const y = sinf((3.14159f/2.0f) + 3.14159f * r * R);
//                float const x = cosf(2 * 3.14159f * s * S) * sinf(3.14159f * r * R);
//                float const z = sinf(2 * 3.14159f * s * S) * sinf(3.14159f * r * R);
//                (*v).x = x * fRadius;
//                (*v).y = y * fRadius;
//                (*v).z = z * fRadius;
//                v++;
//                VertexData.push_back(Vec3(x,y,z));
//            }
//        }
//
//
//
//        // Form triangles        
//        for (r = 0; r < rings - 1; r++) 
//        {
//            for (s = 0; s < sectors - 1; s++)
//            {
//                m.tris.push_back({ verts[r * sectors + s], verts[r * sectors + (s + 1)], verts[(r + 1) * sectors + (s + 1)], 0.0f, 0.0f, 0.0f, FG_YELLOW, PIXEL_SOLID });
//                m.tris.push_back({ verts[r * sectors + s], verts[(r + 1) * sectors + (s + 1)], verts[(r + 1) * sectors + s], 0.0f, 0.0f, 0.0f, FG_YELLOW, PIXEL_SOLID });
//            }
//        }
//}