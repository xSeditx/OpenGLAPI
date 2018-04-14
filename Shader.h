#pragma once
#include "Vertex.h"
#include "Window.h"

extern const char *vertex_shader_text;
extern const char *fragment_shader_text;

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

GLint GetUniformLocation(GLchar *);

void SetUniform1f  ( GLchar *name, float value);
void SetUniform1Int  ( GLchar *name,   int value);

void SetUniform2f  ( GLchar *name,  Vec2 &vector);
void SetUniform3f  ( GLchar *name,  Vec3 &vector);
void SetUniform4f  ( GLchar *name,  Vec4 &vector);

void SetUniformMat4( GLchar *name,  Matrix4 &matrix);

       
private:
       GLuint Load();
};

extern void Load_Shader(GLenum t,const char* code, GLuint *id);