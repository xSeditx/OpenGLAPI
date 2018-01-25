#include <GLFW/glfw3.h>
#include"window.h"

int main(void)
{
        if (!glfwInit())return -1;

	    Window Main(0,0,640, 480, "Hello World");

		//GLuint VertexArrayID;
 
static const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};





        while (GAME_LOOP())
        {
CLS();
		  // Print(SCREEN->FPS);
		  // Print(SCREEN->MOUSE.Button.LEFT);
           if(SCREEN->MOUSE.Button.RIGHT == true)SCREEN->MOUSE.SHOW();
		   if(SCREEN->MOUSE.Button.LEFT  == true)SCREEN->MOUSE.HIDE();
		 //'Print((glfwGetTimer() - SCREEN->TIMER));
SYNC();   
        }
	    
        glfwTerminate();
		Main.DESTROY();
        return 0;
}










