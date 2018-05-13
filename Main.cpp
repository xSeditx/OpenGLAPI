//                                                                                                                                                                        
//                          OPENGL 2.0 Abstraction API
//                               January 24 2018
//                              -----------------                                                                                                                                                        
//                                                                                                                                                                        
//                         OPEN_GL WINDOW MANAGEMENT LIB                                                                                                                     
//======================================================================================================================================================================


#include"window.h"
#include"3d_primitive.h"
#include"Shader.h"
#include "Renderer.h"

 
#define SCREENWIDTH 640
#define SCREENHEIGHT 480

// 3-component floating-point value.

float angle;float translate,scale =1;


bool InitGL__()
{
    //Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0.0, SCREENWIDTH, SCREENHEIGHT, 0.0, 1.0, -1.0 );

    //Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //Initialize clear color
    glClearColor( 0.f, 0.f, 0.f, 1.f );

    //Check for error
    GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        return false;
    }

    return true;
}
void RenderScene5()
{
	angle = angle + .1;
    _GL(glMatrixMode( GL_PROJECTION));
    _GL(glLoadIdentity());
    _GL(glMatrixMode( GL_MODELVIEW));
    _GL(glLoadIdentity());



   glTranslatef( SCREENWIDTH / 2.f, SCREENHEIGHT / 2.f, 1.f );
   // _GL(glTranslatef( 0, 0, -6.0f ));   // NEED TO FIGURE OUT WHY TRANLATE IS OFF.   // Translate back 6 units <- FUCK YOU TUTORIAL YOUR A LIAR!
    _GL(glMatrixMode( GL_MODELVIEW));
    _GL(glLoadIdentity());
   // _GL(glRotatef(angle, 1.0f, 1.0f, 1.0f ));   

if(SCREEN->KEY_BOARD.KEY_STATES[GLFW_KEY_UP])scale+=.01;
if(SCREEN->KEY_BOARD.KEY_STATES[GLFW_KEY_DOWN])scale-=.01;
        _GL(glEnable( GL_DEPTH_TEST ));
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
int main( int argc, char* args[] )
{

//Load_Shader(GL_FRAGMENT_SHADER ,FRAGMENT_SHADER_1 ,&id );

   glewExperimental = GL_TRUE;
        if (!glfwInit())return -1;
        Window Main(0,0,640, 480, "Hello World");

         
        GLenum GlewInitResult = glewInit() ;
        if ((GlewInitResult))
        {
        	    printf("GLEW ERROR: %s\n",glewGetErrorString(GlewInitResult));
                system("PAUSE");
                exit(EXIT_FAILURE);
        }
  
 
// For each function you need, grab the pointer
//PFNGLCREATEPROGRAMPROC glGenVertexArrays = NULL;
//glCreateProgram =  (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");

Print(glGetString(GL_VERSION));
Print(glGetString(GL_RENDERER));

Print(wglGetCurrentContext());

#if 1
GLfloat Vertices[] = 
{
        0,0,0,
        0,3,0,
        8,3,0,
        8,0,0
};

GLushort Indices[] =
{
    0,1,2,
    2,3,0
};
VertexArray vao = VertexArray();

 //_GL(glGenVertexArrays(1, &vao->ARRAY_ID));  
//*vao.ARRAY_ID = 0;

Buffer *vbo = new Buffer(Vertices,4 * 3, 3);
IndexBuffer Ibo(Indices, 6);

Matrix4 Ortho = Matrix4::Orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0);

// 
#endif

#if 0
      Shader SHADER("basic.vert", "basic.frag");
      SHADER.Enable();
#endif
	 // _GL(glGenFramebuffers(1, &SCREEN->FRAME_BUFFER.NAME));
	 // glfwGetFramebufferSize(SCREEN->glCONTEXT, &SCREEN->FRAME_BUFFER.WIDTH, &SCREEN->FRAME_BUFFER.HEIGHT); // Retrieves the size of the frame buffer and places it into the class
	  Matrix4 ortho = Matrix4::Orthographic(0.0f, 16.0f, 0.0f, 9.0, -1.0f, 1.0);
      

        while (GAME_LOOP())
        {

		
        GLCheckError();

        CLS();
		vao.Bind();
		Ibo.Bind();
			_GL(glDrawElements(GL_TRIANGLES, Ibo.COUNT, GL_UNSIGNED_SHORT, 0));
		Ibo.Unbind();
		vao.Unbind();
        SYNC();   
        }


	   	Main.DESTROY();
        glfwTerminate();
        return 0;
}



//
//
//
//
//void initializeGL()
//{
//	// Load shaders, link program for drawing sphere
//	m_sphereProgramID = LoadShaders("basic.vert", "basic.frag");
//	GLuint vertexPosition_modelspaceID = glGetAttribLocation(m_sphereProgramID, "vertexPosition_modelspace");
//
//	// load OpenGL resources needed by the sphere
//	// pass the vertex position id to it
//	sphere.init(vertexPosition_modelspaceID);
//}
//
//void paintGL() {
//	// use corresponding shader program, and set the transformation matrices
//	glUseProgram(m_sphereProgramID);
//	GLuint projMatrixID = glGetUniformLocation(m_sphereProgramID, "projMatrix");
//	GLuint mvMatrixID = glGetUniformLocation(m_sphereProgramID, "mvMatrix");
//	glUniformMatrix4fv(projMatrixID, 1, GL_FALSE, glm::value_ptr(m_projMatrix));
//	glUniformMatrix4fv(mvMatrixID, 1, GL_FALSE, glm::value_ptr(m_mvMatrix));
//	sphere.draw();
//}
//
//void cleanUp() {
//	sphere.cleanup();
//}