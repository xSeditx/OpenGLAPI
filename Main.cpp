//                                                                                                                                                                        
//                          OPENGL 2.0 Abstraction API
//                               January 24 2018
//                              -----------------                                                                                                                                                        
//                                                                                                                                                                        
//                         OPEN_GL WINDOW MANAGEMENT LIB                                                                                                                     
//======================================================================================================================================================================


#include"window.h"
#include"3d_primitive.h"
#include"glut.h"
#include"Shader.h"


// 3-component floating-point value.

float angle;float translate,scale =1;

void RenderScene5()
{
	angle = angle + .1;
    _GL(glMatrixMode( GL_MODELVIEW));
    _GL(glLoadIdentity());

    _GL(glEnable( GL_DEPTH_TEST ));

if(SCREEN->KEY_BOARD.KEY_STATES[GLFW_KEY_UP])scale+=.01;
if(SCREEN->KEY_BOARD.KEY_STATES[GLFW_KEY_DOWN])scale-=.01;

    _GL(glTranslatef( 0, 0, -6.0f ));   // NEED TO FIGURE OUT WHY TRANLATE IS OFF.   // Translate back 6 units <- FUCK YOU TUTORIAL YOUR A LIAR!
    _GL(glRotatef(angle, 1.0f, 1.0f, 1.0f )); 


  //  glTranslatef(0, 0, -translate );                     // Translate back 6 units
    glScalef(scale,scale,scale);
//	glRotatef(angle, 1.0f, 1.0f, 1.0f );        // Rotate on all 3 axis
 
    _GL(glEnableClientState( GL_COLOR_ARRAY ));
    _GL(glEnableClientState( GL_VERTEX_ARRAY ));
 
    _GL(glColorPointer ( 3, GL_FLOAT, sizeof(VertexXYZColor), &(g_Vertices[0].m_Color)) );
    _GL(glVertexPointer( 3, GL_FLOAT, sizeof(VertexXYZColor), &(g_Vertices[0].m_Pos  ) ));
 
    _GL(glDrawElements( GL_QUADS, 24, GL_UNSIGNED_INT, &g_Indices[0] ));
 
    _GL(glDisableClientState( GL_COLOR_ARRAY ));
    _GL(glDisableClientState( GL_VERTEX_ARRAY ));
}




void Print_Shader_Log(GLuint){

}




void Load_Shader(GLenum t,const char* code, GLuint *id)
{
	GLint  compiled_status =0;

	//*id= glCreateShader(t);
	*id = GLEW_GET_FUN(
		__glewCreateShader
		)
		(t);
	_GL(glShaderSource(*id, 1, &code,NULL));

	_GL(glCompileShader(*id));
	_GL(glGetShaderiv(*id, GL_COMPILE_STATUS, &compiled_status));
if(compiled_status!= GL_TRUE){
	//Print_Shader_Log(*id);
    _GL(glDeleteShader(*id));
	*id = 0;
}

}




int main(void)
{
//    GLuint id =  glCreateShader();
//Load_Shader(GL_FRAGMENT_SHADER ,FRAGMENT_SHADER_1 ,&id );

        if (!glfwInit())return -1;

Window Main(0,0,640, 480, "Hello World");

        GLenum GlewInitResult = glewInit() ;
        if ((GlewInitResult))
        {
        	    printf("GLEW ERROR: %s\n",glewGetErrorString(GlewInitResult));
                system("PAUSE");
                exit(EXIT_FAILURE);
        }
         
        //glDepthFunc(GL_ALWAYS);

        while (GAME_LOOP())
        {
            GLCheckError();
        CLS();
		RenderScene5();
        SYNC();   
        }


	   		Main.DESTROY();
        glfwTerminate();

        return 0;
}













/*

   // wxGLContext





int ARRAY[10];


main(){
for (int count = 0;count < 10;count++){
	ARRAY[count] = count;
}

FUNCTION(ARRAY);

}

void FUNCTION(int **AR){
	cout << *AR[5] << endl;
}
*/






//		glViewport(0,0,640,480);
//G//Luint Vert_Shader_Id = 0,
//	   Frag_Shader_Id = 0,
//	   Shader_Program_Id = 0;
 //
 //                 // GL_VERTEX_SHADER 0x8B31
////		Load_Shader(0x8B31, VERTEX_SHADER  , &Vert_Shader_Id);
//		          //GL_FRAGMENT_SHADER 0x8B30
//		Load_Shader(0x8B30,FRAGMENT_SHADER  , &Frag_Shader_Id);
//		Shader_Program_Id = glCreateProgram();
//		glAttachShader(Shader_Program_Id, Vert_Shader_Id);
//		glAttachShader(Shader_Program_Id, Frag_Shader_Id);
//		Print(Vert_Shader_Id);
//		Print(Frag_Shader_Id);
 //

//glClear(.0,.3,.8,1.0);


//https://www.3dgep.com/rendering-primitives-with-opengl/







// USE THIS TO MAKE A FPS Getter and Setters 
//glfwSwapBuffers(window);
//glfwSwapInterval(1);