float _GRAVITY = 1.0;


#include"Collision.h"
#include"window.h"
#include"3d_primitive.h"
#include"Shader.h"
#include"Renderer.h"
#include"Camera.h"
#include"Lights.h"
#include<thread>
 
 
vector<Sphere> SphereList;
Terrain  *GROUND;


bool View = false;

//==========================================================================================================================
//                                                    MAIN 
//__________________________________________________________________________________________________________________________
//==========================================================================================================================


int main( int argc, char* args[] )
{

    int FRAME = 0;

    Camera Cam;
    Cam.Position = Vec3(0,200,0);
    float OLDMX = 0,  OLDMY = 0;


    Window MainWindow(0,0,SCREENWIDTH, SCREENHEIGHT, "OpenGL 2.0");

    {//-----------------------------------------------------------------------
    const GLubyte *extensions = glGetString( GL_EXTENSIONS );
    Print(extensions);
    Print( "OpenGL Version: "  ; Print(glGetString(GL_VERSION)));
    Print( "Renderer: "        ; Print(    glGetString(GL_RENDERER)));
    Print( "Current Context: " ; Print(wglGetCurrentContext()));
    } //-- Just Information Scope --------------------------------------------


    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL );

    Mass::Set_Timestep(2.0f);
    Mass::Set_Gravity(.1);

   //   LightSource Light = LightSource(Vec3(10, 10, 10),
   //                               RGBf(.2,.2,.2),
   //                               RGBf(.8,.8,.8),
   //                               RGBf(1.,1.,1.));
   //

         Terrain *Ground = new Terrain(50,50,30,30);
         Terrain::GROUND = Ground;

    for_loop(count,  10){
                Sphere *temp = new Sphere(Vec3(rand()%30,
                                              -rand()%30,
                                               rand()%30),
                                      2 + RANDOM(10), 20);
        SphereList.push_back(*temp);
    }
   

    Vec3 A(10,20,30);
    Print(A * .10);

 //   system("PAUSE");
    while (GAME_LOOP())
    {
    CLS(); 
// --------------------- Handle Input ---------------------------------------------
        if(SCREEN->KEY_BOARD.Key == GLFW_KEY_SPACE)
        {
             View = !View;
             if (View == true)glPolygonMode(GL_FRONT_AND_BACK, GL_LINE );
             if (View == false)    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL );
             Sleep(200);
        }


        if(SCREEN->KEY_BOARD.Key == GLFW_KEY_RIGHT)
        {
            Cam.MoveRight(2);
        } 
        if(SCREEN->KEY_BOARD.Key == GLFW_KEY_LEFT)
        {
            Cam.MoveLeft(2);
        }
        if(SCREEN->KEY_BOARD.Key == GLFW_KEY_DOWN)
        { 
              Cam.MoveForward(5);
        }
        
        if(SCREEN->KEY_BOARD.Key == GLFW_KEY_UP) 
        {
                Cam.MoveBack(5);
        }

 //  Light.SetPosition(Cam.Position,Cam.Position);//  <---- LIGHTS
//--------------------- Get the MouseMovement ------------------------------------
        Cam.Rotate(-(SCREEN->MOUSE.X - OLDMX), 
                     SCREEN->MOUSE.Y - OLDMY);

        OLDMX = SCREEN->MOUSE.X; // MOUSE.MouseMove.X only works when the callback is being activated
        OLDMY = SCREEN->MOUSE.Y; // Must gather the true mousemovement here in this function 

        Cam.Update();                          // <---- CAMERA
//---------------------------------------------------------------------------------

        Vec3 npos = Cam.Position;
        npos.y += 0;
        npos =   Vec3::RayCast(npos, Cam.Rotation, 80);
        
        

 //     RenderGrid();
      Ground->Render();
        for(Sphere &List:SphereList){

          Collider[List.CollisionID]->Body.Velocity.y +=Mass::Get_Gravity(); // Cheep gravity
           List.Update();
           List.Render();                            // <---- ACTION
        }

        if(SCREEN->MOUSE.IsButtonPressed(1) == true)
        {
             
             for(Sphere &List: SphereList){
             Collider[List.CollisionID]->SetPosition(Vec3((float)-(rand()%10 - 500),
                                                          (float)-(rand()%10),
                                                          (float)-(rand()%10 - 500)));
             }
        }
        if(SCREEN->MOUSE.IsButtonPressed(0) == true)
        {
            Sphere *temp = new Sphere(npos, 2.f + RANDOM(10)  , 20);
            SphereList.push_back(*temp);

            SphereList[Sphere::SphereCount - 1].Set_Position( npos);

            Collider[SphereList[Sphere::SphereCount - 1].CollisionID]->SetPosition(SphereList[Sphere::SphereCount - 1].Position);
            Collider[SphereList[Sphere::SphereCount - 1].CollisionID]->Body.Force.x = cos(RADIANS(Cam.Rotation.y + 90)) * 20;   
            Collider[SphereList[Sphere::SphereCount - 1].CollisionID]->Body.Force.z = sin(RADIANS(Cam.Rotation.y + 90)) * 20;  
            Collider[SphereList[Sphere::SphereCount - 1].CollisionID]->Body.Force.y = cos(RADIANS(Cam.Rotation.x + 90)) * 20;
            Sleep(200);
        }





        int NormalCount = 0, VertexCount=0;
        int count = 0;
        Vec3 pos,pos2;

        float t = 5;
    for_loop(Y, Ground->depth  - 1){
        for_loop(X , Ground->width - 1){
        //===================================================================
            pos = Ground->Vertices[Ground->Get_Vertex(X,Y)]     +                    // 1 
                  Ground->Vertices[Ground->Get_Vertex(X + 1,Y)] +                    // 2 
                  Ground->Vertices[Ground->Get_Vertex(X,Y + 1)];         // 4 
            pos = pos / 3;                                               

        //====================================================================   
            pos2 = Ground->Vertices[Ground->Get_Vertex(X + 1,Y + 1)] +   // 3
                   Ground->Vertices[Ground->Get_Vertex(X  ,Y + 1)]     +   // 4
                   Ground->Vertices[Ground->Get_Vertex(X + 1,Y)];                    // 2
            pos2 = pos2 / 3;


         //===========================================================================================
                glBegin(GL_LINES);
                    glColor3f(GL_Color(255),GL_Color(0),GL_Color(0));
                    glVertex3f(Ground->Position.x + pos.x,
                               Ground->Position.y + pos.y,
                               Ground->Position.z + pos.z);
                    glVertex3f(Ground->Position.x + pos.x + Ground->Normals[NormalCount].x * (t),
                               Ground->Position.y + pos.y + Ground->Normals[NormalCount].y * (t),
                               Ground->Position.z + pos.z + Ground->Normals[NormalCount].z * (t));
                 
                  glColor3f(GL_Color(0),GL_Color(255),GL_Color(0));
                   glVertex3f(Ground->Position.x + pos2.x,
                              Ground->Position.y + pos2.y,
                              Ground->Position.z + pos2.z);
                   glVertex3f(Ground->Position.x + pos2.x + Ground->Normals[NormalCount + 1].x * (t),
                              Ground->Position.y + pos2.y + Ground->Normals[NormalCount + 1].y * (t),
                              Ground->Position.z + pos2.z + Ground->Normals[NormalCount + 1].z * (t));
                 glEnd();
          //===========================================================================================
           
            VertexCount++;
            NormalCount = VertexCount * 2;

        }
    }      

 
        Vec3 VectorA = Collider[0]->Body.Position, VectorB = Collider[1]->Body.Position;
        VectorA.Normalize();
        VectorB.Normalize();

     //   Print( DEGREES(acos(Vec3::DotProduct(VectorA, VectorB))));
        Print(SCREEN->FPS; Print(" : " << Sphere::SphereCount));
      SYNC();
    }

    delete(Ground);

 }







        //            for(int count = 0; count < Ground->VertexCount ; count +=1)
           
       //  glBegin(GL_LINES);
       //
       //  glVertex3f(Ground->Position.x + Ground->Vertices[count].x,
       //             Ground->Position.y + Ground->Vertices[count].y,
       //             Ground->Position.z + Ground->Vertices[count].z);
       //  glVertex3f(Ground->Position.x + Ground->Vertices[count].x + Ground->Normals[count].x * 10,
       //             Ground->Position.y + Ground->Vertices[count].y + Ground->Normals[count].y * 10,
       //             Ground->Position.z + Ground->Vertices[count].z + Ground->Normals[count].z * 10);
       // glEnd();

//cx,cy,cz,
// 0, 0, 0
// 0, 1, 0

// GL_MODELVIEW  =  Mobject?to?world  ?  Mworld?to?camera
// LookAtpoint = LineOfSight + CameraPosition

//The defaults in OpenGL are: the eye at (0, 0, -1); the center at (0, 0, 0)
//and the up is given by the positive direction of the Oy axis (0, 1, 0).

//https://msdn.microsoft.com/en-us/library/y47ychfe.aspx?f=255&MSPPError=-2147217396


