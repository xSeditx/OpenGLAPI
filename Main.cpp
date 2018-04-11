//                                                                                                                          
//                          OPENGL 2.0 Abstraction API
//                               January 24 2018
//                              -----------------                                                                           
//                                                                                                                          
//                         OPEN_GL WINDOW MANAGEMENT LIB                                                                    
//==========================================================================================================================
//
// THIS FILE IS JUST USED TO TEST THE SYSTEM AND IS SUBJECT TO CHANGE ON A DAILY BASIS.

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
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

int main( int argc, char* args[] )
{
    int FRAME = 0;

    Camera Cam;

    float MOVEX = 0,  MOVEY = 0, 
          OLDMX = 0,  OLDMY = 0,
          POSX  = 0,  POSY  = 0;

    const int NumObjects = 6;
    vector<Mesh> ObjectList;

    Window MainWindow(0,0,SCREENWIDTH, SCREENHEIGHT, "OpenGL 2.0");

    const GLubyte *extensions = glGetString( GL_EXTENSIONS );
    Print(extensions);

    Print( "OpenGL Version: "  ; Print(glGetString(GL_VERSION)));
    Print( "Renderer: "        ; Print(    glGetString(GL_RENDERER)));
    Print( "Current Context: " ; Print(wglGetCurrentContext()));
  
    for_loop(zcount, NumObjects){
         for_loop(ycount, NumObjects){
             for_loop(xcount, NumObjects){
                 Torus Temp =  Torus(8,25,(float)(xcount  * rand()%100), 
                                          (float)(ycount  * rand()%100),
                                          (float)(zcount  * rand()%100), 
                                                                      1);
                 ObjectList.push_back(Temp);
             }
                 Mesh Temps =  Sphere(Vec3((float)(rand()%100),
                                           (float)(rand()%100),
                                           (float)(rand()%100)),
                                                             RANDOM(5));
                 ObjectList.push_back(Temps);
         }

    }
  //  for_loop(count , 30){Mesh Temps =  Cube(Vec3((float)(rand()%100),(float)( rand()%100),(float)( rand()%100)),2);
  //                 ObjectList.push_back(Temps);
  //  }

   Ball Balls(Vec3(20,20,20), 10);

    LightSource Light = LightSource(Vec3(0, 0, 0),RGBf(.2,.2,.2),RGBf(.8,.8,.8),RGBf(1.,1.,1.));
 
 


    while (GAME_LOOP())
    {
    CLS(); 
        
// --------------------- Handle Input ---------------------------------------------
        if(SCREEN->KEY_BOARD.Key == GLFW_KEY_SPACE){}    
        if(SCREEN->KEY_BOARD.Key == GLFW_KEY_RIGHT)
        {
            Cam.MoveRight(.05);
        } 
        if(SCREEN->KEY_BOARD.Key == GLFW_KEY_LEFT)
        {
            Cam.MoveLeft(.05);
        }
        if(SCREEN->KEY_BOARD.Key == GLFW_KEY_DOWN)
        { 
                Cam.MoveForward(.1);
        }
        
        if(SCREEN->KEY_BOARD.Key == GLFW_KEY_UP) 
        {
                Cam.MoveBack(.1);
        }

 //--------------------- Get the MouseMovement ------------------------------------
        MOVEX = SCREEN->MOUSE.X - OLDMX;     OLDMX = SCREEN->MOUSE.X; 
        MOVEY = SCREEN->MOUSE.Y - OLDMY;     OLDMY = SCREEN->MOUSE.Y;
        Cam.Rotate(MOVEX,MOVEY);
        Cam.Update();
//---------------------------------------------------------------------------------

    //  Light.SetPosition(Cam.Position,Cam.Position);

      RenderGrid();
      Balls.Render();
     // Balls.ChangeVerts();
    //  glFlush();

   // for(Mesh &List: ObjectList)
   // {
   //       List.Render();
   //  }
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


