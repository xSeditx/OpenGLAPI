#include"Shader.h"
#include"Vector.h"
#include"Window.h"

static const char* vertex_shader_text =
"uniform mat4 MVP;\n"
"attribute vec3 vCol;\n"
"attribute vec2 vPos;\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
"    color = vCol;\n"
"}\n";


static const char* fragment_shader_text =
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_FragColor = vec4(color, 1.0);\n"
"}\n";


const char *VERTEX_SHADER_1 = 
"#version 120\n"
"void main()\n"
"{\n"
"gl_Position = gl_Vertexl\n"
"}\n";


const char *FRAGMENT_SHADER_1 = 
"#version 120\n"
"void main()\n"
"{\n"
"   gl_FragColor = vec4(1.0,0.0,0.0,1.0);\n"
"}\n ";


// Define the 8 vertices of a unit cube
VertexXYZColor g_Vertices[8] = {
    { float3(  1,  1,  1 ), float3( GL_Color(255),  GL_Color(0),  GL_Color(0) ) }, // 0
    { float3( -1,  1,  1 ), float3( GL_Color(0),  GL_Color(0),  GL_Color(255)) }, // 1
    { float3( -1, -1,  1 ), float3(GL_Color(0),  GL_Color(255),  GL_Color(0)) }, // 2

    { float3(  1, -1,  1 ), float3(GL_Color(255),  GL_Color(0),  GL_Color(255)) }, // 3
    { float3(  1, -1, -1 ), float3(GL_Color(255),  GL_Color(255),  GL_Color(0) ) }, // 4
    { float3( -1, -1, -1 ), float3(GL_Color(0),  GL_Color(255),  GL_Color(255)) }, // 5

    { float3( -1,  1, -1 ), float3( GL_Color(255),  GL_Color(255),  GL_Color(50) ) }, // 6
    { float3(  1,  1, -1 ), float3( GL_Color(0),  GL_Color(50),  GL_Color(255) ) }, // 7
};

GLuint g_Indices[24] = {
    0, 1, 2, 3,                 // Front face
    7, 4, 5, 6,                 // Back face
    6, 5, 2, 1,                 // Left face
    7, 0, 3, 4,                 // Right face
    7, 6, 1, 0,                 // Top face
    3, 2, 5, 4,                 // Bottom face
};