#pragma once


#define GLEW_STATIC

#pragma warning(disable: 4244)	
#pragma warning(disable: 4005)	
#pragma warning(disable: 4305)	

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Windows.h>
#include "vertex.h"

#define GetRandom( min, max )     ((rand() % (int)(((max) + 1) - (min))) + (min))  
#define RANDOM(x)                 ((rand() * (1.0 / (1.0 + RAND_MAX))) * (x))
#define RANDOM_RANGE(x)           (RANDOM(x * 2) - (x))
#define MIN(a,b)                  ((a<b) ? a : b)
#define MAX(a,b)                  ((a>b) ? a : b)
#define PICK_ONE(a,b)             ((RANDOM(1) > .5) ? a : b)
//const bool TRACE = true;
#define WaitKey                    system("PAUSE");

#define DEBUG
//#define TRACE
//#define FUNCTION_TRACE
//======================================================================================================================================================================
//_____________________________________________________________  MACROS  _______________________________________________________________________________________________

#define Print(x)                   std::cout << x << std::endl
#define LOG_CALLBACK(x)            std::cout << (x) << std::endl

/*************** DEBUG MACROS FOR DISPLAYING OPEN_GL ERRORS *****************************/
#define ASSERT(x) if(!(x)){system ("PAUSE");  exit(EXIT_FAILURE);}
//system("PAUSE");

#ifdef TRACE
      #define  _TRACE(x)  std::cout << #x << std::endl
#else
      #define _TRACE(x)
#endif

#ifdef FUNCTION_TRACE
      #define  f_TRACE(x)  std::cout << #x << std::endl
#else
      #define f_TRACE(x)
#endif


#ifdef DEBUG
#define _GL(x)           GLClearError();\
                                    (x);\
                              _TRACE(x);\
                   ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
      #define _GL(x)  x
#endif

#ifdef  DEBUG
    #define GLCall(x) GLClearError(); x; ASSERT(GLLogCall(...))
#else
    #define GLCall(x) x
#endif
/*******************************************************************************************/

#define GL_Color(c)      (c * (.0039215686627451))

//======================================================================================================================================================================
//__________________________________________________________ USEFUL DEFINES  ___________________________________________________________________________________________
#define MOUSE_LEFT       0
#define MOUSE_RIGHT      1
#define MOUSE_CENTER     2

#define SCREENWIDTH       640
#define SCREENHEIGHT      480

#define M_E           2.71828182845904523536
#define M_LOG2E       1.44269504088896340736
#define M_LOG10E      0.434294481903251827651
#define M_LN2         0.693147180559945309417
#define M_LN10        2.30258509299404568402
#define M_PI          3.14159265358979323846
#define M_PI_2        1.57079632679489661923
#define M_PI_4        0.785398163397448309616
#define M_1_PI        0.318309886183790671538
#define M_2_PI        0.636619772367581343076
#define M_2_SQRTPI1   0.12837916709551257390
#define M_SQRT2       1.41421356237309504880
#define M_SQRT1_2     0.707106781186547524401

#define RADIANS(x)   ((x) * (M_PI / 180)) 
#define for_loop(itr, count)          for(int(itr) = 0; itr < (count); itr++)

class  Window;
extern Window *SCREEN;

typedef RECT Rect;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                            WINDOW CLASS                                                                                                                            
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Window{
public:
    Window(){}
    ~Window(){glfwTerminate();}
    Window(int,int,int,int,char*);
	
    int     X,     Y,
        WIDTH,HEIGHT;
	

    HWND            Hwnd;       // HWND
    char           *TITLE;
    GLFWwindow     *glCONTEXT;   

    unsigned  long  TIMER;
    unsigned   int  FRAME_COUNT;
    unsigned   int  FPS;

    struct FrameBuffer{
        int WIDTH,
            HEIGHT;
       GLuint NAME;
    }FRAME_BUFFER;

    struct MouseProperties{
        bool Button[5];      
         int Action,
             Modifications;
        int  X,
             Y;
        int OldX,Oldy;
        int MouseMoveX, 
            MouseMoveY;
        inline bool IsButtonPressed (int button){return Button[button];}
        inline void HIDE(){glfwSetInputMode(SCREEN->glCONTEXT, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);}
        inline void SHOW(){glfwSetInputMode(SCREEN->glCONTEXT, GLFW_CURSOR, GLFW_CURSOR_NORMAL);} 
    }MOUSE;


    struct Key_Board{
         int Key, 
             Scancode,  
             Action, 
             Modifications;
        bool KEY_STATES[350];
      inline bool IsKeyPressed        (int keycode)                              { return KEY_STATES[keycode];}		
    }KEY_BOARD;

private:
    unsigned short SyncRATE;
    int           FrameRate;
public:
               int GetFPS(){ return FrameRate;}

              void DESTROY             ();
              void SYNC                (unsigned short);
    unsigned short SYNC_RATE           ();
              Vec2 GET_WINDOW_POSITION ();
       inline void SET_WINDOW_POSITION (GLFWwindow *,int x, int y)                {   glfwSetWindowPos(SCREEN->glCONTEXT, x, y);   }
       inline void SHOW()                                                         {   glfwShowWindow(this->glCONTEXT);             }
       inline void HIDE()                                                         {   glfwHideWindow(this->glCONTEXT);             }


private:	


static void Error_callback           (         int,    const char*);
static void Resize_Callback          (GLFWwindow *window,int,int);
static void Window_close_callback    (GLFWwindow *window);
static void KeyBoard_Callback        (GLFWwindow *window,    int,    int, int, int);
static void Mouse_Callback           (GLFWwindow *window,    int,    int, int);
static void MouseMove_Callback       (GLFWwindow *window, double, double);
static void DropFile_callback        (GLFWwindow *window,    int, const char**);
static void Window_Size_Callback     (GLFWwindow *window,    int,    int);




};
 

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                          HELPER FUNCTIONS                                                                                                                            
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void SYNC();
extern void CLS();
extern void CLS(unsigned long color);
extern bool GAME_LOOP();
extern bool Set_Window_Focus  (Window *);

extern const  char *GET_CLIPBOARD();
extern        void  SET_CLIPBOARD(char*);

extern GLvoid* BufferObjectPtr( unsigned int idx);

extern void GLClearError();
extern void GLCheckError();
extern bool GLLogCall(const char *function, const char *file, int line);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                                                                  
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
extern void *GetAnyGLFuncAddress(const char *name);
extern float WrapAngle(float angle);
// SCREEN RAYCASTER TO GET THE MOUSE XY Position in 3D SPACE
//    http://antongerdelan.net/opengl/raycasting.html








//
////In a header somewhere.

//PFNGLUSEPROGRAMPROC glUseProgram;
//
////In an initialization routine
//glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");


//PFNGLUSEPROGRAMPROC EXT_compiled_vertex_array;
//GL_ARB_vertex_buffer_object();
//    multi draw arrays
// ARB   pixel buffer object
//  ARB  draw buffers
//  GL EXT draw range elements
//
//  glBindBufferARB();

//#define GL_ARRAY_BUFFER_ARB 0x8892
//#define GL_STATIC_DRAW_ARB 0x88E4
//typedef void (APIENTRY * PFNGLBINDBUFFERARBPROC) (GLenum target, GLuint buffer);
//typedef void (APIENTRY * PFNGLDELETEBUFFERSARBPROC) (GLsizei n, const GLuint *buffers);
//typedef void (APIENTRY * PFNGLGENBUFFERSARBPROC) (GLsizei n, GLuint *buffers);
//typedef void (APIENTRY * PFNGLBUFFERDATAARBPROC) (GLenum target, int size, const GLvoid *data, GLenum usage);
// 
//// VBO Extension Function Pointers
//PFNGLGENBUFFERSARBPROC glGenBuffersARB = NULL;                  // VBO Name Generation Procedure
//PFNGLBINDBUFFERARBPROC glBindBufferARB = NULL;                  // VBO Bind Procedure
//PFNGLBUFFERDATAARBPROC glBufferDataARB = NULL;                  // VBO Data Loading Procedure
//PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB = NULL;                // VBO Deletion Procedure