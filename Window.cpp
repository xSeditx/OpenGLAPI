//======================================================================================================================================================================
//                                                                                                                                                                        
//                                                  OPENGL 2.0 Abstraction API
//                                                       January 24 2018
//                                                      -----------------                                                                                                                                                        
//                                                                                                                                                                        
//                                                                                                                                                                        
//                                                 OPEN_GL WINDOW MANAGEMENT LIB                                                                                                                     
//                                                                                                                                                                        
//                                                                                                                                                                        
//                                                                                                                                                                        
//======================================================================================================================================================================

#include"Window.h"

Window *SCREEN;  // Target window for my API




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                      /* Construct Window */                                                                                        //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Window::Window(int x,int y,int w,int h,char* title):X(x), Y(y), WIDTH(w), HEIGHT(h), TITLE(title)
{
	
//------------------------------------------------------- GLFW Window Hints	--------------------------------------------------------------------------------------------  
        glfwWindowHint(GLFW_SAMPLES              ,    4); // 4x antialiasing
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,    2); // Min and Max supported OpenGL versions
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,    0);
        glfwWindowHint(GLFW_RESIZABLE            , true);
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------	    
	    
        glCONTEXT  = glfwCreateWindow(w, h, title, NULL, NULL);  if  (!glCONTEXT){
                                                                 glfwTerminate   ();  // Kill if Creation Failed
                                                                 exit(EXIT_FAILURE);
                                                                 }
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------	    
        Set_Window_Focus       (this);
        Hwnd = GetActiveWindow ();
	
//---------------------------------------------------- SET WINDOW CONTEXT & CALLBACK FUNCTIONS -------------------------------------------------------------------------    
        glfwMakeContextCurrent (glCONTEXT);
		                                                                           // _____________ SETS __________________
        glfwSetErrorCallback       (Error_callback);                               // Callback when Error Encountered
        glfwSetKeyCallback         (glCONTEXT, KeyBoard_Callback);	               // Callback for KeyPress
        glfwSetDropCallback        (glCONTEXT, DropFile_callback);	               // Callback Allows Files to be dropped into the window and get the path read
        glfwSetMouseButtonCallback (glCONTEXT, Mouse_Callback);                    // Callback for Mouse Button Click
        glfwSetCursorPosCallback   (glCONTEXT, MouseMove_Callback);                // Callback to return Mouse Position			 
        glfwSetWindowPosCallback   (glCONTEXT, Window_Size_Callback);              // Callback to return Window Position
        glfwSetWindowSizeCallback  (glCONTEXT, Resize_Callback);                   // Callback when Window is Resized
        glfwSetWindowCloseCallback (glCONTEXT, Window_close_callback);             // Callback when Closed
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------	    


//DONT FORGET TO HANDLE GENERATING THE FUCKING FRAME BUFFER CORRECTLY
//        _GL(glGenFramebuffers(10,FRAME_BUFFER.NAME));
//        glfwGetFramebufferSize(glCONTEXT, FRAME_BUFFER.WIDTH, FRAME_BUFFER.HEIGHT); // Retrieves the size of the frame buffer and places it into the class
        FRAME_COUNT = 0;
        FPS         = 0;

        for(int count = 0; count < 350;count++)SCREEN->KEY_BOARD.KEY_STATES[count] = 0;	// NULLIFY the KEYBOARD ARRAY

}

//______________________________________________________________________________________________________________________________________________________________________
//                                                          CALLBACK FUNCTIONS
//______________________________________________________________________________________________________________________________________________________________________
void Window::Error_callback        (int error, const char* description)
{
        std::cout << "WINDOW ERROR CALLBACK: " << glewGetErrorString(error); // << std::end;
        fprintf(stderr, "Error: %s\n", description);
}
void Window::Resize_Callback       (GLFWwindow *HAND,int w,int h){
        SCREEN->HEIGHT = h;
        SCREEN->WIDTH  = w;
        _GL(glViewport(0,0, w,h));
}
void Window::Window_close_callback (GLFWwindow* window)
{
        if (glfwWindowShouldClose(SCREEN->glCONTEXT))
            glfwSetWindowShouldClose(window, GL_TRUE);
}
void Window::KeyBoard_Callback     (GLFWwindow *window, int key, int scancode, int action, int mods){ //GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT.
        
        _TRACE(Print("SETUP THE KEYBOARD ROUTINE"));

        SCREEN->KEY_BOARD.Key, 
        SCREEN->KEY_BOARD.Scancode,  
        SCREEN->KEY_BOARD.Action, 
        SCREEN->KEY_BOARD.Modifications;
        SCREEN->KEY_BOARD.KEY_STATES[key] = glfwGetKey(SCREEN->glCONTEXT,key);	

}
void Window::Mouse_Callback        (GLFWwindow *window, int button, int action, int mod){
        SCREEN->MOUSE.Button[button] = action != GLFW_RELEASE;
}
void Window::DropFile_callback     (GLFWwindow *window, int count, const char** paths)
{
        int i;
        for (i = 0;  i < count;  i++){
                Print("File the DropFILE callback to handle File:");  //handle_dropped_file(paths[i]);
                Print(*paths);}                                        
}
void Window::MouseMove_Callback    (GLFWwindow *window, double xpos, double ypos){
        SCREEN->MOUSE.X = xpos,
        SCREEN->MOUSE.Y = ypos;
}
void Window::Window_Size_Callback  (GLFWwindow *window, int x, int y)
{
        SCREEN->X = x; // Double check to ensure this is the height and width and not position
        SCREEN->Y = y;
}
	
/*____________________________________________________________________________________________________________________________________________________________________*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


 /*========================================================= Set Sync Rate(FPS) of Window =============================================================================*/
void Window::SYNC(unsigned short rate){
        SyncRATE = 1000 / rate;
}

/*========================================================== Get Sync Rate(FPS) of Window =============================================================================*/
unsigned short Window::SYNC_RATE(){
        return SyncRATE;
}

/*================================================== Free the memory Allocated for the Window ========================================================================*/
void Window::DESTROY(){
        glfwDestroyWindow(glCONTEXT);
}

/*================================================== Return the current Window position as a Vec2 ====================================================================*/
Vec2 Window::GET_WINDOW_POSITION(){ 
        int X,Y;
        glfwGetWindowPos(SCREEN->glCONTEXT, &X, &Y);
        return Vec2((int)X,(int)Y);
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                    /* EXTERNAL API to MANAGE WINDOW CLASS*/                                                                        //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//======================================================================================================================================================================
//__________________________________________________________ Set Window To be API Target _______________________________________________________________________________
    inline bool Set_Window_Focus(Window *win){
            SCREEN = win;
            return true;
    }
//======================================================================================================================================================================
//__________________________________________________________ Swap front and back buffers _______________________________________________________________________________
	inline void SYNC(){
/*~~~~~~~~~~~~~~~~~~Get Frames Per Second~~~~~~~~~~~~~~~~~~~~*/
		
        if((glfwGetTime() - SCREEN->TIMER) >= 1)
            {
                        SCREEN->FPS = SCREEN->FRAME_COUNT;
                        SCREEN->FRAME_COUNT = 0;
            }
            SCREEN->TIMER = glfwGetTime();
            SCREEN->FRAME_COUNT++;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/		
            glfwPollEvents();
            int W,H;
            glfwGetFramebufferSize(SCREEN->glCONTEXT,&W,&H); //<---------- The pollevents here and in the GAME_LOOP function should be reviewed because even though its working I dont believe its being done correctly;
            glfwSwapBuffers(SCREEN->glCONTEXT);
    }

//======================================================================================================================================================================
//____________________________________________________________  Clear the back buffers  ________________________________________________________________________________
    inline void CLS(){
            _GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    }

//======================================================================================================================================================================
//______________________________________________________  EVENT HANDLER AND MESSAGE DISPATCHER  ________________________________________________________________________
    bool GAME_LOOP(){                                       /*----- May be overloaded -----*/
            glfwPollEvents();
            if (glfwWindowShouldClose(SCREEN->glCONTEXT))return false;
    return true;
    }                               
            
//======================================================================================================================================================================
//__________________________________________________________ CLIPBOARD GETTERS AND SETTERS _____________________________________________________________________________
    const char *GET_CLIPBOARD(){        /*clipboard Getter*/          
            Print("TEST GET CLIPBOARD FUNCTION");
            const char* text = glfwGetClipboardString(SCREEN->glCONTEXT);
            if(text) return text; else 
        return NULL;
    } 
                                    
    void  SET_CLIPBOARD  (char *text){  /*clipboard setter*/
		Print("TEST SET CLIPBOARD FUNCTION");
			glfwSetClipboardString(SCREEN->glCONTEXT,text);
	}

//======================================================================================================================================================================
//__________________________________________________________ Get Buffer Offser Pointer _________________________________________________________________________________
    inline GLvoid* BufferObjectPtr( unsigned int idx )
{
    return (GLvoid*)( ((char*)NULL) + idx );
}

// http://ptgmedia.pearsoncmg.com/images/chap2_0321336798/elementLinks/02fig03.gif // Date of link: 1/ 27/ 2018

//=================================================================================================================================================================== */
//____________________________________________________ Error Logger for Printing OpenGL Errors _________________________________________________________________________


bool GLLogCall(const char *function, const char *file, int line){
        GLenum error = glGetError();
        if(error != 0){
            printf("[OpenGL ERROR]: %s\n",glewGetErrorString(error));
            std::cout << "Error Number: " <<  error << std::endl;
            std::cout << "FILE: " << file << std::endl;
            std::cout << "LINE NUMBER: " << line << std::endl;
            std::cout << "FUNCTION: " << function << std::endl;
            return false;
        }
  return true;
}


void GLCheckError(){
   GLenum err;
   while((err = glGetError()) != GL_NO_ERROR)
   {
     std::cout<< "GLCHECKERROR" << err ;
   }

}

void GLClearError(){
     while((glGetError()) != GL_NO_ERROR);
}

//=================================================================================================================================================================== */
//_____________________________________________________________________________________________________________________________________________________________________





//=================================================================================================================================================================== */
//_____________________________________________________________________________________________________________________________________________________________________
  






