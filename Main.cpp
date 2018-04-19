#include"Collision.h"
#include"window.h"
#include"3d_primitive.h"
#include"Shader.h"
#include"Renderer.h"
#include"Camera.h"
#include"Lights.h"
#include<thread>
 

bool TERMINATE = false;
vector<Sphere> SphereList;

 void Physics_Thread();


 int MousePicker(float x, float y)
 {
     return 1;
 }


void RenderGrid(){
            glPushMatrix();
   for(int i = -500; i <= 500; i+=5)
   {
 
       glBegin(GL_LINES);
       glVertex3f(-500, 0, i);
       glVertex3f( 500, 0, i);
       glVertex3f(i, 0, -500);
       glVertex3f(i, 0,  500);
       glEnd();
   }
           glPopMatrix();
}
//==========================================================================================================================
//                                                    MAIN 
//__________________________________________________________________________________________________________________________
//==========================================================================================================================


int main( int argc, char* args[] )
{

    int FRAME = 0;

    Camera Cam;
    Cam.Position = Vec3(200,200,200);
    float MOVEX = 0,  MOVEY = 0, 
          OLDMX = 0,  OLDMY = 0,
          POSX  = 0,  POSY  = 0;

    Window MainWindow(0,0,SCREENWIDTH, SCREENHEIGHT, "OpenGL 2.0");

    {
    const GLubyte *extensions = glGetString( GL_EXTENSIONS );
    Print(extensions);
    Print( "OpenGL Version: "  ; Print(glGetString(GL_VERSION)));
    Print( "Renderer: "        ; Print(    glGetString(GL_RENDERER)));
    Print( "Current Context: " ; Print(wglGetCurrentContext()));
    } // Just Information Scope

 for_loop(count,  10){
             Sphere *temp = new Sphere(Vec3(rand()%30,
                                           -rand()%30,
                                           rand()%30),
                                         2 + RANDOM(10), 20);
     SphereList.push_back(*temp);
  }

    LightSource Light = LightSource(Vec3(0, 0, 0),
                                    RGBf(.2,.2,.2),
                                    RGBf(.8,.8,.8),
                                    RGBf(1.,1.,1.));

 
//  FUTRE USE, TESTED POSITIVELY other Then User controlled Ball Glitches on its position
//    std::thread Phythread(Physics_Thread);
 

    while (GAME_LOOP())
    {
    CLS(); 
// --------------------- Handle Input ---------------------------------------------
        if(SCREEN->KEY_BOARD.Key == GLFW_KEY_SPACE)
        {
                    for(Sphere &List:SphereList)List.Update();
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
              Cam.MoveForward(2);
        }
        
        if(SCREEN->KEY_BOARD.Key == GLFW_KEY_UP) 
        {
                Cam.MoveBack(2);
        }

//   Light.SetPosition(Cam.Position,Cam.Position);//  <---- LIGHTS
//--------------------- Get the MouseMovement ------------------------------------
        MOVEX = SCREEN->MOUSE.X - OLDMX;     OLDMX = SCREEN->MOUSE.X; // MOUSE.MouseMove.X only works when the callback is being activated
        MOVEY = SCREEN->MOUSE.Y - OLDMY;     OLDMY = SCREEN->MOUSE.Y; // Must gather the true mousemovement here in this function 

        Cam.Rotate(-MOVEX,MOVEY);
        Cam.Update();                          // <---- CAMERA
//---------------------------------------------------------------------------------

        Vec3 npos = Cam.Position;
        npos.y -= 20;
        npos =   Vec3::RayCast(npos, Cam.Rotation, 100);
        

    //  glPushMatrix();
    //  glMatrix
    //  glPopMatrix();
    //


      RenderGrid();

        for(Sphere &List:SphereList){

          Collider[List.CollisionID]->Velocity.y += 4.82; // Cheep gravity
           List.Update();
           List.Render();                            // <---- ACTION
        }

        if(SCREEN->MOUSE.IsButtonPressed(1) == true)
        {
             
             for(Sphere &List: SphereList){
             Collider[List.CollisionID]->SetPosition(Vec3((float)-(rand()%10),
                                                          (float)-(rand()%10),
                                                          (float)-(rand()%10)));
             }
        }
        
        if(SCREEN->MOUSE.IsButtonPressed(0) == true)
        {
                Sphere *temp = new Sphere(Cam.Position, 2.f + (float)RANDOM(10), 20);
            SphereList.push_back(*temp);


           SphereList[Sphere::SphereCount - 1].Set_Position( npos);
           Collider[SphereList[Sphere::SphereCount - 1].CollisionID]->SetPosition(SphereList[Sphere::SphereCount - 1].Position);

            Collider[SphereList[Sphere::SphereCount - 1].CollisionID]->Force.x = cos(RADIANS(Cam.Rotation.y + 90)) * 200;   
            Collider[SphereList[Sphere::SphereCount - 1].CollisionID]->Force.z = sin(RADIANS(Cam.Rotation.y + 90)) * 200;  
            Collider[SphereList[Sphere::SphereCount - 1].CollisionID]->Force.y = cos(RADIANS(Cam.Rotation.x + 90)) * 20;
        Sleep(150);
        }

 

   
      //  Print(SCREEN->MOUSE.X);
     // Print(SCREEN->FPS);
     //   world.update(.01);
      SYNC();
    }

    TERMINATE = true;
    
    //Phythread.join();
 }










 // Tested, Worked well other then Glitching on the User Control
 
 void Physics_Thread()
 {
     while(TERMINATE == false){
         for(Sphere &List:SphereList){
            Collider[List.CollisionID]->Force.y = 4.82;
            List.Update();
         }
     }
 }





//cx,cy,cz,
// 0, 0, 0
// 0, 1, 0

// GL_MODELVIEW  =  Mobject?to?world  ?  Mworld?to?camera
// LookAtpoint = LineOfSight + CameraPosition

//The defaults in OpenGL are: the eye at (0, 0, -1); the center at (0, 0, 0)
//and the up is given by the positive direction of the Oy axis (0, 1, 0).

//https://msdn.microsoft.com/en-us/library/y47ychfe.aspx?f=255&MSPPError=-2147217396


