#pragma once

#include <GLFW/glfw3.h>
#include <iostream>
#include<Windows.h>

//======================================================================================================================================================================
//_____________________________________________________________  MACROS  _______________________________________________________________________________________________

#define Print(x)   std::cout << x << std::endl


//======================================================================================================================================================================
//__________________________________________________________ USEFUL DEFINES  ___________________________________________________________________________________________
#define MOUSE_LEFT       0
#define MOUSE_RIGHT      1
#define MOUSE_CENTER     2

class  Window;
extern Window *SCREEN;
typedef RECT Rect;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                            WINDOW CLASS                                                                                                                            
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Window{
public:
	Window(){}~Window(){}
	Window(int,int,int,int,char*);

	
    int     X,     Y,
	    WIDTH,HEIGHT;
	

	HWND            Hwnd;
	char           *TITLE;
	GLFWwindow     *glCONTEXT;

	unsigned  long  TIMER;
	unsigned   int  FRAME_COUNT;
	unsigned   int  FPS;

	struct{
		int *WIDTH,
			*HEIGHT;
	}FRAME_BUFFER;


	struct {
	
	        struct {
		        bool  LEFT,
			          RIGHT,
			          CENTER;
	            }Button;
	             
		int	 Action,
			 Modifications;
		int  X,
			 Y;
		inline void HIDE(){glfwSetInputMode(SCREEN->glCONTEXT, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);}
		inline void SHOW(){Print("WTFFFFF");}//glfwSetInputMode(SCREEN->glCONTEXT, GLFW_CURSOR, GLFW_CURSOR_NORMAL);} // SOMETHING IS WRONG> WHY WONT THE MOUSE COME BACK ON AND SHOW?
	}MOUSE;

	struct{
		 int Key, 
			 Scancode,  
			 Action, 
			 Modifications;
		int KEY_STATES[350];
		
	}KEY_BOARD;

private:
	unsigned short SyncRATE;

public:
		      void DESTROY           ();
	          void SYNC              (unsigned short);
	unsigned short SYNC_RATE         ();

private:	

static void Resize_Callback          (GLFWwindow*,int,int);
static void Error_callback           (int, const char*);
static void Window_close_callback    (GLFWwindow *);
static void KeyBoard_Callback        (GLFWwindow *, int, int, int, int);
static void Mouse_Callback           (GLFWwindow *, int, int, int);
static void MouseMove_Callback       (GLFWwindow *, double, double);
static void DropFile_callback        (GLFWwindow *, int, const char**);

};





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                          HELPER FUNCTIONS                                                                                                                            
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




extern inline bool Set_Window_Focus  (Window *);
extern inline void SYNC();
extern inline void CLS();
extern        bool GAME_LOOP();

extern const  char *GET_CLIPBOARD();
extern        void  SET_CLIPBOARD(char*);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                                                                  
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                                                                   
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//void glVertexPointer(GLint 	size,GLenum	type,	GLsizei	stride,	const GLvoid *VERTEX_ptr);
