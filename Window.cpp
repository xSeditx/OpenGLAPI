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
        glfwSetWindowCloseCallback (glCONTEXT, Window_close_callback);             // Callback when Closed
        glfwSetWindowSizeCallback  (glCONTEXT, Resize_Callback);                   // Callback when Resized
        glfwSetKeyCallback	       (glCONTEXT, KeyBoard_Callback);	               // Callback for KeyPress
        glfwSetMouseButtonCallback (glCONTEXT, Mouse_Callback);                    // Callback for Mouse Button Click
		glfwSetDropCallback        (glCONTEXT, DropFile_callback);	               // Callback Allows Files to be dropped into the window and get the path read
        glfwSetCursorPosCallback   (glCONTEXT, MouseMove_Callback);			 

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------	    
//FIX THIS FRAME BUFFER CODE ITS BROKEN and CAUSING AN ACCESS VIOLATION
//glfwGetFramebufferSize(glCONTEXT, *FRAME_BUFFER.WIDTH, FRAME_BUFFER.HEIGHT); // Retrieves the size of the frame buffer and places it into the class
			FRAME_COUNT = 0;
			FPS         = 0;

            for(int count = 0; count < 350;count++)SCREEN->KEY_BOARD.KEY_STATES[count] = 0;	// NULLIFY the KEYBOARD ARRAY

}

//______________________________________________________________________________________________________________________________________________________________________
//                                                          CALLBACK FUNCTIONS
//______________________________________________________________________________________________________________________________________________________________________
void Window::Error_callback        (int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}
void Window::Resize_Callback       (GLFWwindow *HAND,int w,int h){
    // Get new window size
    RECT rect;
    int W, H;

	glfwMakeContextCurrent (HAND);
	HWND   Hwnd = GetActiveWindow ();

    GetClientRect(Hwnd, &rect);
    W = rect.right;
    H = rect.bottom;

    glClearColor(0.0, 0.0, 0.0, 0.0);  //Set the cleared screen colour to black
    glViewport(0, 0, W, H);   //This sets up the viewport so that the coordinates (0, 0) are at the top left of the window

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);  //Back to the modelview so we can draw stuff 
    glLoadIdentity();

    glRotatef     (   180,   1.0f, 0, 0);
    glTranslatef  ( -1.0f,  -1.0f, 0);
    glScalef      (2.0f/W, 2.0f/H, 1);
    glTranslatef  (  2.0f,   2.0f, 0);
}
void Window::Window_close_callback (GLFWwindow* window)
{
	if (glfwWindowShouldClose(SCREEN->glCONTEXT))
        glfwSetWindowShouldClose(window, GL_TRUE);
}
void Window::KeyBoard_Callback     (GLFWwindow *window, int key, int scancode, int action, int mods){ //GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT.
	    Print("SETUP THE KEYBOARD ROUTINE");

		SCREEN->KEY_BOARD.Key, 
		SCREEN->KEY_BOARD.Scancode,  
		SCREEN->KEY_BOARD.Action, 
		SCREEN->KEY_BOARD.Modifications;

		//for(int count = 0; count < 350;count++)
			SCREEN->KEY_BOARD.KEY_STATES[key] = glfwGetKey(SCREEN->glCONTEXT,key);	

}
void Window::Mouse_Callback        (GLFWwindow *window, int button, int action, int mod){

       // Print("WARNING: LEFT MOUSE == 0, MUST CREATE FLAG TO SHOW BUTTONS CURRENTLY BEING PUSHED");
		//SCREEN->MOUSE.Button = button; // WARNING: LEFT MOUSE == 0, MUST CREATE FLAG TO SHOW BUTTONS CURRENTLY BEING PUSHED
		SCREEN->MOUSE.Action = action;
		SCREEN->MOUSE.Modifications = mod;
		Print(button);
		int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
        if (state == GLFW_PRESS){
			switch(button){
			        case MOUSE_LEFT:
			        	SCREEN->MOUSE.Button.LEFT   = true;
			        break;
			        case MOUSE_RIGHT:
			        	SCREEN->MOUSE.Button.RIGHT  = true;
			        break;
			        case MOUSE_CENTER:
			        	SCREEN->MOUSE.Button.CENTER = true;
			        break;
			}
		}else{             //GLFW_RELEASE
				    SCREEN->MOUSE.Button.LEFT   = false;
				    SCREEN->MOUSE.Button.RIGHT  = false;
				    SCREEN->MOUSE.Button.CENTER = false;
		}

}
void Window::DropFile_callback     (GLFWwindow *window, int count, const char** paths)
{
    int i;
    for (i = 0;  i < count;  i++)
        Print("File the DropFILE callback to handle File:");  //handle_dropped_file(paths[i]);
	    Print(*paths);                                        
}
void Window::MouseMove_Callback    (GLFWwindow *window, double xpos, double ypos){
	  SCREEN->MOUSE.X = xpos,
	  SCREEN->MOUSE.Y = ypos;
}
 	
/*____________________________________________________________________________________________________________________________________________________________________*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


 /*========================================================= Set Sync Rate of Window =================================================================================*/
void Window::SYNC(unsigned short rate){
	SyncRATE = 1000 / rate;
}
/*========================================================== Get Sync Rate of Window =================================================================================*/
unsigned short Window::SYNC_RATE(){
	return SyncRATE;
}

/*================================================== Free the memory Allocated for the Window ========================================================================*/
void Window::DESTROY(){
	glfwDestroyWindow(glCONTEXT);

}
/*====================================================================================================================================================================*/




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
	// if ( (glfwGetTime() - SCREEN->TIMER) < SCREEN->SYNC_RATE())Print("Sync Rate To Fast: Fix the Sync Function");

/*~~~~~~~~~~~~~~~~~~Get Frames Per Second~~~~~~~~~~~~~~~~~~~~*/
		
		if((glfwGetTime() - SCREEN->TIMER) >= 1)
			{
				    SCREEN->FPS = SCREEN->FRAME_COUNT;
				    SCREEN->FRAME_COUNT = 0;
			}
		    SCREEN->TIMER = glfwGetTime();
			SCREEN->FRAME_COUNT++;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/		

            glfwSwapBuffers(SCREEN->glCONTEXT);
            glfwPollEvents();
    }
//======================================================================================================================================================================
//____________________________________________________________  Clear the back buffers  ________________________________________________________________________________

	inline void CLS(){
	        glClear(GL_COLOR_BUFFER_BIT);
    }
//======================================================================================================================================================================
//______________________________________________________  EVENT HANDLER AND MESSAGE DISPATCHER  ________________________________________________________________________
   
	 bool GAME_LOOP(){
	        if (glfwWindowShouldClose(SCREEN->glCONTEXT))return false;
    return true;
    }

//======================================================================================================================================================================
//__________________________________________________________ CLIPBOARD GETTERS AND SETTERS _____________________________________________________________________________

	  const char *GET_CLIPBOARD            (){
		Print("TEST GET CLIPBOARD FUNCTION");
			const char* text = glfwGetClipboardString(SCREEN->glCONTEXT);
			if(text) return text; else 
			return NULL;
	}
            void  SET_CLIPBOARD  (char *text){
			  Print("TEST SET CLIPBOARD FUNCTION");
			glfwSetClipboardString(SCREEN->glCONTEXT,text);
	}

/*=================================================================================================================================================================== */
/*=================================================================================================================================================================== */
/*=================================================================================================================================================================== */
	
