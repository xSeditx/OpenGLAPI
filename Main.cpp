//                                                                                                                          
//                          OPENGL 2.0 Abstraction API
//                               January 24 2018
//                              -----------------                                                                           
//                                                                                                                          
//                         OPEN_GL WINDOW MANAGEMENT LIB                                                                    
//==========================================================================================================================
//
// THIS FILE IS JUST USED TO TEST THE SYSTEM AND IS SUBJECT TO CHANGE ON A DAILY BASIS.

#include"Collision.h"
#include"window.h"
#include"3d_primitive.h"
#include"Shader.h"
#include"Renderer.h"
#include"Camera.h"
#include"Lights.h"

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

    float MOVEX = 0,  MOVEY = 0, 
          OLDMX = 0,  OLDMY = 0,
          POSX  = 0,  POSY  = 0;

    const int NumObjects = 6;
    vector<Mesh> ObjectList;
    vector<Ball> BallList;

    Window MainWindow(0,0,SCREENWIDTH, SCREENHEIGHT, "OpenGL 2.0");

    const GLubyte *extensions = glGetString( GL_EXTENSIONS );
    Print(extensions);

    Print( "OpenGL Version: "  ; Print(glGetString(GL_VERSION)));
    Print( "Renderer: "        ; Print(    glGetString(GL_RENDERER)));
    Print( "Current Context: " ; Print(wglGetCurrentContext()));

    for_loop(count,400){
                                 Ball *temp = new Ball(Vec3(rand()%30,
                                               -rand()%30,
                                               rand()%30),
                                               10, 20);
        BallList.push_back(*temp);
           
                 Mesh Temps =  Sphere(Vec3((float)-(rand()%100),
                                           (float)-(rand()%100),
                                           (float)-(rand()%100)),
                                                             10);
                 ObjectList.push_back(Temps);
    }

    LightSource Light = LightSource(Vec3(0, 0, 0),
                                    RGBf(.2,.2,.2),
                                    RGBf(.8,.8,.8),
                                    RGBf(1.,1.,1.));

    while (GAME_LOOP())
    {
    CLS(); 
        
// --------------------- Handle Input ---------------------------------------------
        if(SCREEN->KEY_BOARD.Key == GLFW_KEY_SPACE)
        {
                    for(Ball &List:BallList)List.Update();
                 //    BallList[rand()%100].Set_Position( Vec3(0,0,0));
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

        Cam.Rotate(MOVEX,MOVEY);
        Cam.Update();                                // <---- CAMERA
//---------------------------------------------------------------------------------


        BallList[0].Set_Position( Vec3::RayCast(Cam.Position, Cam.Rotation, 100));
        Collider[BallList[0].CollisionID]->SetPosition(BallList[0].Position);

        RenderGrid();

        for(Ball &List:BallList){



           Collider[List.CollisionID]->Force.y = 4.82;
           List.Update();
           List.Render();                            // <---- ACTION
        }

        if(SCREEN->MOUSE.IsButtonPressed(0) == true)
        {
            Print("MOUSE");

             for(Ball &List: BallList){
              //  Collider[List.CollisionID]->SetPosition(Vec3(0,0,0));
             Collider[List.CollisionID]->SetPosition(Vec3((float)-(rand()%4),
                                                          (float)-(rand()%6000),
                                                          (float)-(rand()%4)));
             }
        }



      Print(SCREEN->FPS);
      SYNC();
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


