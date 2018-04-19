
#include"Renderer.h"
#include"3D_Primitive.h"
#include "window.h"


#define BUFFER_OFFSET(i) ((char *)NULL + (i))

#define SphereList   Sphere::s_SphereList
std::vector<Sphere*> Sphere::s_SphereList;
unsigned int Sphere::SphereCount = 0;


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
   Print(CollisionID);

}

 void Sphere::Update ()
 {

   Collider[CollisionID]->Update(1.f);
   Set_Position(Collider[CollisionID]->Position);
   //Submit(Vertices);
}
 void Sphere::Render ()
 {

   glPushMatrix();

      glTranslatef(Position.x,  Position.y, Position.z);

      Vbo.Bind();
          glDrawArrays(GL_TRIANGLE_STRIP, 0, VertexCount);
      Vbo.Unbind();

  glPopMatrix();
}
 void Sphere::ChangeVert (int index, Vec3 newpos){
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

    Bounds->Position = pos;
    Bounds->Radius   = rad;
    Bounds->ParentID = p;

    return Bounds->ID;
}
      
//===============================================================================================================================================
//_______________________________________________________________________________________________________________________________________________________________
//==============================================================================================================================================================
 


















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






