float _GRAVITY = 1.0;

#include"QuadTree.h"
#include"Collision.h"
#include"window.h"
#include"3d_primitive.h"

#include"Lights.h"
#include<thread>

#define BATCH 0

using namespace std;
 

//std::vector<Sphere> SphereList;

Terrain *GROUND;

bool View = false;
QT *Tree;


CollisionSphere *Selected; 

//==========================================================================================================================
//                                                    MAIN 
//__________________________________________________________________________________________________________________________
//==========================================================================================================================
void LeftClick(int x, int y)
{
   if(Selected == nullptr)
   {
       int distance = 0;
       Selected = MousePicker(*SCREEN->Cam, &distance);
        if(Selected != nullptr)
        {
            Selected->Body.Position = Vec3::RayCast(SCREEN->Cam->Position, SCREEN->Cam->Rotation, distance);
        }
   }
}

void LeftButtonUp(int x, int y)
{
    if(Selected != nullptr) Selected = nullptr;
}

void RightClick(int x, int y)
{
    Vec3 npos = SCREEN->Cam->Position;
    npos.y += 0;
    npos =   Vec3::RayCast(npos, SCREEN->Cam->Rotation, 80);
    
    Sphere *temp = new Sphere(npos, 2.f + RANDOM(20)  , 20);
    Sphere::s_SphereList.push_back(temp);
    
    Sphere::s_SphereList[Sphere::SphereCount - 1]->Set_Position( npos);
    
    Collider[Sphere::s_SphereList[Sphere::SphereCount - 1]->CollisionID]->SetPosition(Sphere::s_SphereList[Sphere::SphereCount - 1]->Position);
    Collider[Sphere::s_SphereList[Sphere::SphereCount - 1]->CollisionID]->Body.Force.x = cos(RADIANS(SCREEN->Cam->Rotation.y + 90)) * 20;   
    Collider[Sphere::s_SphereList[Sphere::SphereCount - 1]->CollisionID]->Body.Force.z = sin(RADIANS(SCREEN->Cam->Rotation.y + 90)) * 20;  
    Collider[Sphere::s_SphereList[Sphere::SphereCount - 1]->CollisionID]->Body.Force.y = cos(RADIANS(SCREEN->Cam->Rotation.x + 90)) * 20;

   // for(Sphere &List: SphereList)
   // {
   //     Collider[List.CollisionID]->SetPosition(Vec3((float)-(rand()%100 - 500),
   //                                                  (float)-(rand()%10),
   //                                                  (float)-(rand()%100 - 500)));
   // }
}
void Keydown  (GLushort Keycode, GLushort ScanCode, GLushort Modifier)
{
// --------------------- Handle Input ---------------------------------------------
        if(SCREEN->KEY_BOARD.Key == GLFW_KEY_SPACE)
        {
             GROUND->View = !GROUND->View;
             if (GROUND->View == true) 
             {
                 glPolygonMode(GL_FRONT_AND_BACK, GL_LINE );
             }
             else
             {
                 glPolygonMode(GL_FRONT_AND_BACK, GL_FILL );
             }
             Sleep(200);
        }
         
        if(SCREEN->KEY_BOARD.Key == GLFW_KEY_RIGHT)
        {
           // Cam->MoveRight(5);
            SCREEN->Cam->MoveRight(5);
        } 
        if(SCREEN->KEY_BOARD.Key == GLFW_KEY_LEFT)
        {
            //Cam->MoveLeft(5);
            SCREEN->Cam->MoveLeft(5);
        }
        if(SCREEN->KEY_BOARD.Key == GLFW_KEY_DOWN)
        { 
           // Cam->MoveForward(5);
            SCREEN->Cam->MoveForward(5);
        }
        if(SCREEN->KEY_BOARD.Key == GLFW_KEY_UP) 
        {
            // Cam->MoveBack(5);
            SCREEN->Cam->MoveBack(5);
        }
}
void MouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle)
{
    if(Selected != nullptr)
    {
        Selected->Body.Position = Vec3::RayCast(SCREEN->Cam->Position, SCREEN->Cam->Rotation, 100);
    }
}





int main( int argc, char* args[] )
{

    int FRAME = 0;
    Selected = nullptr;
 

    float OLDMX = 0,  OLDMY = 0;

    Window MainWindow(0,0,SCREENWIDTH, SCREENHEIGHT, "OpenGL 2.0");

    MainWindow.Callbacks.SetOnLButtonDown(LeftClick);
    MainWindow.Callbacks.SetOnLButtonUp(LeftButtonUp);
    MainWindow.Callbacks.SetOnRButtonDown(RightClick);
    MainWindow.Callbacks.SetOnKeyHold(Keydown);
    MainWindow.Callbacks.SetOnMouseMove(MouseMove);


    MainWindow.Cam = new Camera();
    MainWindow.Cam->Position = Vec3(0,200,0);


//--------Gathering information about OpenGL state and Display it -----------------------------------------------

    const GLubyte *extensions = glGetString( GL_EXTENSIONS );
    Print(extensions);
    Print( "OpenGL Version: "  ; Print(glGetString(GL_VERSION)));
    Print( "Renderer: "        ; Print(    glGetString(GL_RENDERER)));
    Print( "Current Context: " ; Print(wglGetCurrentContext()));

 //-------------------------------------------------------------------------------------------------------------
 // Set some state commands for OpenGL
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL );
    glIsEnabled(GL_LIGHTING);

// Set some Physics constants. This needs to be changed later but is in a simple currently functioning state

    Mass::Set_Timestep(2.0f);
    Mass::Set_Gravity(.1);

    for_loop(count,  300)
    {
        Sphere *temp = new Sphere(Vec3(   20+rand()%WX / 2,   // X 100,-100,100),  
                                         -10,                 // Y
                                          20+ rand()%WZ / 2), // Z
                                          1 + RANDOM(1), 20); // Radius and SubDivisions
    }

// Create the Terrain and assign it to the global Terrain. This needs to be changed later.
    Terrain *Ground = new Terrain(WorldSizeX, WorldSizeZ, 
                                   GridSizeX, GridSizeZ); 
    Terrain::GROUND = Ground;

// Create then Initialize the QuadTree in the World.
    Tree = new QT(Vec2(WX / 2,WZ / 2),
                  Vec2(WX / 2,WZ / 2));

    Tree->Init();

#if BATCH
  Sphere::BatchBuild();
#endif


    while (GAME_LOOP())
    {
    CLS(); 
//--------------------- Get the MouseMovement ------------------------------------

        SCREEN->Cam->Rotate(-(SCREEN->MOUSE.X - OLDMX), SCREEN->MOUSE.Y - OLDMY);
        
        OLDMX = SCREEN->MOUSE.X; // MOUSE.MouseMove.X only works when the callback is being activated
        OLDMY = SCREEN->MOUSE.Y; // Must gather the true mousemovement here in this function 

        SCREEN->Cam->Update();                             // <---- CAMERA
        
        if(SCREEN->KEY_BOARD.Key == GLFW_KEY_SPACE)
        {
             Ground->View = !Ground->View;
             if (View == true) 
             {
                 glPolygonMode(GL_FRONT_AND_BACK, GL_LINE );
             }
             else
             {
                 glPolygonMode(GL_FRONT_AND_BACK, GL_FILL );
             }
             Sleep(200);
        }
         
        if(SCREEN->KEY_BOARD.Key == GLFW_KEY_RIGHT)
        {
            MainWindow.Cam->MoveRight(5);
        } 
        if(SCREEN->KEY_BOARD.Key == GLFW_KEY_LEFT)
        {
            MainWindow.Cam->MoveLeft(5);
        }
        if(SCREEN->KEY_BOARD.Key == GLFW_KEY_DOWN)
        { 
            MainWindow.Cam->MoveForward(5);
        }
        if(SCREEN->KEY_BOARD.Key == GLFW_KEY_UP) 
        {
            MainWindow.Cam->MoveBack(5);
        }

#if BATCH
        Sphere::Batch();
#else
        for(auto &List: Sphere::s_SphereList)
        {
            Collider[List->CollisionID]->Body.Velocity.y += Mass::Get_Gravity(); // Cheep gravity
            List->Update();
            List->Render();                            // <---- ACTION
        }
#endif

        Tree->Update(); // Rebuild the QuadTree

        Ground->Render();

        Print(SCREEN->FPS; Print(" : " << Sphere::SphereCount));
        SYNC();
    }

    delete(Tree);
    delete(Ground);

}

























       
//---------------------------------------------------------------------------------
      //  Print(SCREEN->KEY_BOARD.Key);
     //   Print(SCREEN->KEY_BOARD.Action);'



//if(SCREEN->MOUSE.Button[0]){
//        Vec3 npos = Cam->Position;
//npos.y += 0;
//npos =   Vec3::RayCast(npos, Cam->Rotation, 80);
//
//    Sphere *temp = new Sphere(npos, 2.f + RANDOM(20)  , 20);
//    SphereList.push_back(*temp);
//
//    SphereList[Sphere::SphereCount - 1].Set_Position( npos);
//
//    Collider[SphereList[Sphere::SphereCount - 1].CollisionID]->SetPosition(SphereList[Sphere::SphereCount - 1].Position);
//    Collider[SphereList[Sphere::SphereCount - 1].CollisionID]->Body.Force.x = cos(RADIANS(Cam->Rotation.y + 90)) * 20;   
//    Collider[SphereList[Sphere::SphereCount - 1].CollisionID]->Body.Force.z = sin(RADIANS(Cam->Rotation.y + 90)) * 20;  
//    Collider[SphereList[Sphere::SphereCount - 1].CollisionID]->Body.Force.y = cos(RADIANS(Cam->Rotation.x + 90)) * 20;
//}
//





//cx,cy,cz,
// 0, 0, 0
// 0, 1, 0

// GL_MODELVIEW  =  Mobject?to?world  ?  Mworld?to?camera
// LookAtpoint = LineOfSight + CameraPosition

//The defaults in OpenGL are: the eye at (0, 0, -1); the center at (0, 0, 0)
//and the up is given by the positive direction of the Oy axis (0, 1, 0).

//https://msdn.microsoft.com/en-us/library/y47ychfe.aspx?f=255&MSPPError=-2147217396


