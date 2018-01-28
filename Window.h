#pragma once


#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Windows.h>

#include "vector.h"

const bool _DEBUG_TRACE = true;

#define DEBUG
//#define TRACE

//======================================================================================================================================================================
//_____________________________________________________________  MACROS  _______________________________________________________________________________________________

#define Print(x)                   std::cout << x << std::endl
#define LOG_CALLBACK(x)            std::cout << x << std::endl

/*************** DEBUG MACROS FOR DISPLAYING OPEN_GL ERRORS *****************************/
#define ASSERT(x) if(!(x)){ system("PAUSE"); exit(EXIT_FAILURE);}


#ifdef TRACE
      #define  _TRACE(x) if(_DEBUG_TRACE) x
#else
      #define _TRACE(x)
#endif

 

#ifdef DEBUG
#define _GL(x)   GLClearError();\
                   x;\
                   ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
      #define _GL(x)  x
#endif


//#define DEBUG
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

class Window;
extern Window *SCREEN;

typedef RECT Rect;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                            WINDOW CLASS                                                                                                                            
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Window{
public:
    Window(){}
    ~Window(){ glfwTerminate();}
    Window(int,int,int,int,char*);

	
    int     X,     Y,
        WIDTH,HEIGHT;
	

    HWND            Hwnd;
    char           *TITLE;
    GLFWwindow     *glCONTEXT;

    unsigned  long  TIMER;
    unsigned   int  FRAME_COUNT;
    unsigned   int  FPS;

    struct FrameBuffer{
        int *WIDTH,
            *HEIGHT;
       GLuint *NAME;
    }FRAME_BUFFER;


    struct MouseProperties{
        bool Button[5];      
         int Action,
             Modifications;
        int  X,
             Y;
// Need to change this	    inline bool IsButtonPressed (int button){   return Button[keycode];}
        inline void HIDE(){glfwSetInputMode(SCREEN->glCONTEXT, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);}
        inline void SHOW(){glfwSetInputMode(SCREEN->glCONTEXT, GLFW_CURSOR, GLFW_CURSOR_NORMAL);} 
    }MOUSE;


    struct Key_Board{
         int Key, 
             Scancode,  
             Action, 
             Modifications;
         int KEY_STATES[350];
      inline bool IsKeyPressed        (int keycode)                              {   return KEY_STATES[keycode];}		
    }KEY_BOARD;

private:
    unsigned short SyncRATE;

public:
	           
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





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                         NOTES/TODO/DEPRECIATED CODE/ETC.......                                                                                                  
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//void glVertexPointer(GLint 	size,GLenum	type,	GLsizei	stride,	const GLvoid *VERTEX_ptr);

//GLubyte *a =  gluErrorString()
//	GLenum WINAPI glGetError
