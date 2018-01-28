#pragma once
#include "Vertex.h"
#include "Window.h"

extern const char *vertex_shader_text;
extern const char *fragment_shader_text;

extern VertexXYZColor g_Vertices[8];
extern GLuint g_Indices[24];

extern const char *VERTEX_SHADER_1;
extern const char *FRAGMENT_SHADER_1;




class Shader{

private:
       GLuint m_ShaderID;
       const char* m_Vertpath;
       const char* m_Fragpath;
       
       public:
        Shader(const char* vertPath, const char* fragPath);
        ~Shader();
       
       void Enable() const;
       void Disable() const;
       
private:
       GLuint load();
};
