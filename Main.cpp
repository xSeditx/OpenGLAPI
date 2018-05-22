float _GRAVITY = 1.0;

#include"QuadTree.h"
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
Camera *Cam;
bool View = false;
QT *Tree;


//==========================================================================================================================
//                                                    MAIN 
//__________________________________________________________________________________________________________________________
//==========================================================================================================================
void MClick(int x, int y)
{

    Print("Callback for the mouse Button" << x);

        Vec3 npos = Cam->Position;
        npos.y += 0;
        npos =   Vec3::RayCast(npos, Cam->Rotation, 80);

            Sphere *temp = new Sphere(npos, 2.f + RANDOM(20)  , 20);
            SphereList.push_back(*temp);

            SphereList[Sphere::SphereCount - 1].Set_Position( npos);

            Collider[SphereList[Sphere::SphereCount - 1].CollisionID]->SetPosition(SphereList[Sphere::SphereCount - 1].Position);
            Collider[SphereList[Sphere::SphereCount - 1].CollisionID]->Body.Force.x = cos(RADIANS(Cam->Rotation.y + 90)) * 20;   
            Collider[SphereList[Sphere::SphereCount - 1].CollisionID]->Body.Force.z = sin(RADIANS(Cam->Rotation.y + 90)) * 20;  
            Collider[SphereList[Sphere::SphereCount - 1].CollisionID]->Body.Force.y = cos(RADIANS(Cam->Rotation.x + 90)) * 20;


}
void RightClick(int x, int y)
{
    for(Sphere &List: SphereList)
    {
        Collider[List.CollisionID]->SetPosition(Vec3((float)-(rand()%100 - 500),
                                                     (float)-(rand()%10),
                                                     (float)-(rand()%100 - 500)));
    }
}
void Keydown  (GLushort Keycode, GLushort ScanCode, GLushort Modifier)
{
// --------------------- Handle Input ---------------------------------------------
        if(SCREEN->KEY_BOARD.Key == GLFW_KEY_SPACE)
        {
             View = !View;
             if (View == true) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE );
             if (View == false)    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL );
             Sleep(200);
        }


        if(SCREEN->KEY_BOARD.Key == GLFW_KEY_RIGHT)
        {
            Cam->MoveRight(5);
        } 
        if(SCREEN->KEY_BOARD.Key == GLFW_KEY_LEFT)
        {
            Cam->MoveLeft(5);
        }
        if(SCREEN->KEY_BOARD.Key == GLFW_KEY_DOWN)
        { 
            Cam->MoveForward(5);
        }
        if(SCREEN->KEY_BOARD.Key == GLFW_KEY_UP) 
        {
             Cam->MoveBack(5);
        }

}






int main( int argc, char* args[] )
{

    int FRAME = 0;

    Cam = new Camera;
    Cam->Position = Vec3(0,200,0);
    float OLDMX = 0,  OLDMY = 0;
    Window MainWindow(0,0,SCREENWIDTH, SCREENHEIGHT, "OpenGL 2.0");

    MainWindow.Callbacks.SetOnLButtonDown(MClick);
    MainWindow.Callbacks.SetOnRButtonDown(RightClick);
    MainWindow.Callbacks.SetOnKeyHold(Keydown);

//-----------------------------------------------------------------------
    const GLubyte *extensions = glGetString( GL_EXTENSIONS );
    Print(extensions);
    Print( "OpenGL Version: "  ; Print(glGetString(GL_VERSION)));
    Print( "Renderer: "        ; Print(    glGetString(GL_RENDERER)));
    Print( "Current Context: " ; Print(wglGetCurrentContext()));
 //-- Just Information Scope --------------------------------------------
    

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL );

    Mass::Set_Timestep(2.0f);
    Mass::Set_Gravity(.1);
    glIsEnabled(GL_LIGHTING);

    for_loop(count,  100){
                Sphere *temp = new Sphere(Vec3(               20+rand()%WX / 2,   // X 100,-100,100),  
                                                                -10,   // Y
                                                               20+ rand()%WZ / 2),  // Z
                                      1 + RANDOM(1), 20);  // Radius and SubDivisions
        SphereList.push_back(*temp);
    }

    Terrain *Ground = new Terrain(WorldSizeX, WorldSizeZ, GridSizeX, GridSizeZ); 
    Terrain::GROUND = Ground;

    Tree = new QT(Vec2(WX / 2,WZ / 2),
                  Vec2(WX / 2,WZ / 2));
    Tree->Init();



    while (GAME_LOOP())
    {
    CLS(); 
//--------------------- Get the MouseMovement ------------------------------------

        Cam->Rotate(-(SCREEN->MOUSE.X - OLDMX), SCREEN->MOUSE.Y - OLDMY);
        
        OLDMX = SCREEN->MOUSE.X; // MOUSE.MouseMove.X only works when the callback is being activated
        OLDMY = SCREEN->MOUSE.Y; // Must gather the true mousemovement here in this function 
        
        Cam->Update();                             // <---- CAMERA
        
      
//---------------------------------------------------------------------------------

        for(Sphere &List:SphereList)
        {
                Collider[List.CollisionID]->Body.Velocity.y += Mass::Get_Gravity(); // Cheep gravity
                List.Update();
                List.Render();                            // <---- ACTION
        }

        Tree->Update();

        Ground->Render();
 
        Print(SCREEN->FPS; Print(" : " << Sphere::SphereCount));
        SYNC();
    }

    delete(Ground);
}





//cx,cy,cz,
// 0, 0, 0
// 0, 1, 0

// GL_MODELVIEW  =  Mobject?to?world  ?  Mworld?to?camera
// LookAtpoint = LineOfSight + CameraPosition

//The defaults in OpenGL are: the eye at (0, 0, -1); the center at (0, 0, 0)
//and the up is given by the positive direction of the Oy axis (0, 1, 0).

//https://msdn.microsoft.com/en-us/library/y47ychfe.aspx?f=255&MSPPError=-2147217396


