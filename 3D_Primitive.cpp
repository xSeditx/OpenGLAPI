#include "window.h"
#include "3D_Primitive.h"

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
//______________________________________ TERRAIN _____________________________________________________________________________________________________________
//==============================================================================================================================================================
 
Terrain::Terrain(int w, int d, int gw, int gd)
       :Position( 0 ,0 ,0),
        width   (w), 
        depth   (d), 
        gridw   (gw), 
        gridd   (gd), 
        VertexCount(0), 
        ColorsCount(0)
{

   // Heights  = new float[w * d];
    Vertices = new Vec3[(w + 1) * (d + 1)];
    Colors   = new Vec3[(w + 1) * (d + 1)];
    float H1 = 0, H2 = 0, H3 = 0;
    float FinalHeight =0;

    for_loop(Y, d ){
        for_loop(X , w){
            if(X % 2 == 0) H1 = (30); else H1 = 0;
           // if(X % 5 == 0) H2 = RANDOM(10);    
           // if(X % 2 == 0) H3 = RANDOM(10);


            //Heights[X + w * Y] = H1 + H2 + H3;//RANDOM(10);
            Vertices[VertexCount].x = X * gw;
            Vertices[VertexCount].y =H1 ;//* H2 * H3 / 10;//X * Y / 2; //<-- Just debug so I know what Vertex it is
            Vertices[VertexCount].z = Y * gd;

//           Colors[ColorsCount].r = GL_Color((X * gridw) * 255);
//           Colors[ColorsCount].g = GL_Color(Heights[X + w * Y] * 255);
//           Colors[ColorsCount].b = GL_Color((Y * gridd) * 255);

            Colors[ColorsCount].r = GL_Color((ColorsCount % 4) * 64);
            Colors[ColorsCount].g = GL_Color(((ColorsCount +1) % 4)* 64);
            Colors[ColorsCount].b = GL_Color(((ColorsCount +2) % 4)* 64);

          VertexCount++;
          ColorsCount++;
        }
    }

    IndexCount =0;
    Indices = new GLushort[w * d * 4];

    for_loop(Y, gd - 1){
        for_loop(X , gw - 1){
            Indices[IndexCount+2] =    X + w * Y ;
            Indices[IndexCount+3] =   (X + 1) + w * Y;
            Indices[IndexCount+1] =    X  + w * (Y + 1);
            Indices[IndexCount]   =   (X + 1) + w * (Y + 1);
           IndexCount+=4;
        }
    }

   Vbo = Buffer(Vertices, Colors, VertexCount, ColorsCount);
   Ibo = IndexBuffer(Indices,IndexCount);
}

float Terrain::Lerp(float a, float b, float c)
{
    return (1.0 - c) * a + b * c;
}

void Terrain::Render()
{

   glPushMatrix();
      glTranslatef(Position.x,  Position.y, Position.z);

      Vbo.Bind();
        //  glDrawArrays(GL_QUADS, 0, VertexCount);
      Ibo.Bind();
   glDrawElements(GL_QUADS , IndexCount , GL_UNSIGNED_SHORT, nullptr);
      Ibo.Unbind();
         Vbo.Unbind();
  glPopMatrix();
}



float Terrain::SampleTerrain(float x, float z) 
{
    
    x += width * 0.5f; //Assume that grid's center is at the origin. 
    z += depth * 0.5f;
    
    if(x < 0.0f || x > width * gridw ||  z < 0.0f ||  z > depth * gridd)  
        return -FLT_MAX;
    
    float sx = x / (float)gridw; // NOTES:Translates Position to Grid Space.
    float sy = z / (float)gridd; //
    
    int ax = (int)sx;
    int ay = (int)sy;
    
    int bx = min(ax+1, gridw);
    int by = min(ay+1, gridd);
    
    float fracX = sx - ax;
    float fracY = sy - ay; 
    
    //We're going to need these for linearily interpolate over a square
    
    float tl = Vertices[ax + ay*width].y;
    float tr = Vertices[bx + ay*width].y;

    float bl = Vertices[ax + by*width].y;
    float br = Vertices[bx + by*width].y;

    float lrt = Lerp(tl, tr, fracX); // Lerp between square top values
    float lrb = Lerp(bl, br, fracX); // Lerp between square low values
        
    return Lerp(lrt, lrb, fracY); // Lerp between the left .. right values  
  
    // tl ---- tr
    //  |      |
    //  |      |
    // bl ---- br

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














 //// MAGETS Sphere
//
//
//
//
//RawMesh::RawMesh(f32 w, f32 h, f32 d, u32 rings, u32 verticesPerRing) {
//
//    RawMesh mesh;
//
//    Math::vec3 position = {0.0f, h*0.5f, 0.0f};
//    Math::vec2 texCoord = {0.5f, 1.0f};
//    Math::vec3 normal = position.normalized();
//
//    auto addVertex = [&]() {
//        mesh.mVertices.push_back(position);
//        mesh.mTextureCoordinates.push_back(texCoord);
//        mesh.mNormals.push_back(normal);
//    };
//
//    addVertex();
//
//    for(s32 i = 1; i < rings; i++) {
//        f32 irad = Math::Sin((f32)i / (f32)(rings - 1) * 180.0f);
//        f32 v = -(f32)i / (f32)(rings - 1);
//        for(s32 j = 0; j < verticesPerRing; j++) {
//            f32 u = (f32)j / (f32)verticesPerRing - 1;
//            f32 vx = Math::Cos((f32)j / (f32)(verticesPerRing - 1) * 360.0f) * irad* w * 0.5f;
//            f32 vy = Math::Cos((f32)i / (f32)(rings - 1) * 180.0f) * h * 0.5f;
//            f32 vz = Math::Sin((f32)j / (f32)(verticesPerRing - 1) * 360.0f) * irad * d * 0.5f;
//
//            position = {vx, vy, vz};
//            texCoord = {u, v};
//            normal = position.normalized();
//            addVertex();
//        }
//    }
//
//    position = {0.0f, -h*0.5f, 0.0f};
//    texCoord = {0.5f, 0.0f};
//    normal = position.normalized();
//    addVertex();
//
//    for(s32 j = 0; j < verticesPerRing - 1; j++) {
//        mesh.mTriangles.emplace_back(0, 1 + j, 1 + j + 1);
//    }
//
//    for(s32 i = 0; i < rings - 2; i++) {
//        for(s32 j = 0; j < verticesPerRing - 1; j++) {
//
//            u32 a = i * verticesPerRing + 1 + j;
//            u32 b = i * verticesPerRing + 1 + j + 1;
//            u32 c = (i + 1) * verticesPerRing + 1 + j + 1;
//            u32 d = (i + 1) * verticesPerRing + 1 + j;
//            
//            //a --- b
//            //|     |
//            //|     |
//            //d --- c
//
//            mesh.mTriangles.emplace_back(d, c, b);
//            mesh.mTriangles.emplace_back(d, b, a);
//        }
//    }
//
//    mesh.estimateTangentspace();
//    return mesh;
//}