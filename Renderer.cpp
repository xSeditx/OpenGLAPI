#include"Renderer.h"
void GenVertexArrays(GLsizei n, GLuint *arrays);

//===================================================================================================================================================
//__________________________________ RENDERER CLASS _________________________________________________________________________________________________

void Renderer::Push(Matrix4 mat4){
        Transformation_Stack.push_back(mat4);
}

 Matrix4 Renderer::Pop(){
        Matrix4 ret = Transformation_Stack.back();
        Transformation_Stack.pop_back();
        return ret;
}





//===================================================================================================================================================
//__________________________________ IMAGE CLASS ____________________________________________________________________________________________

Image::~Image()
{ 
    glDeleteTextures(1, &ID);
    if(Data != nullptr)
               delete(Data);
}
Image::Image()
       : ID(0), 
         Data(nullptr),
         Width(0),
         Height(0)
{
    
    glEnable(GL_TEXTURE_2D);  
}
Image::Image(const char *filename)
    : ID(0)
{   
    glEnable(GL_TEXTURE_2D);
    Data = LoadBMP(filename);
  
    glGenTextures(1,&ID); 
    glBindTexture(GL_TEXTURE_2D, ID); // Or maybe GL_TEXTURE_BUFFER???
 // glActiveTexture(GL_TEXTURE0 + ID);
// Sampling mode for blending textals
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

// Texture Layout when sampling past texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);   
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
  
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_BGR, GL_UNSIGNED_BYTE, Data);
    glBindTexture(GL_TEXTURE_2D,0);
}
Image::Image(GLenum param, const char *filename)
    : ID(0)
{   
    glEnable(GL_TEXTURE_2D);
    Data = LoadBMP(filename);
    if (param == GL_TEXTURE_CUBE_MAP)
    {
        glGenTextures(1,&ID); 
        glBindTexture(GL_TEXTURE_CUBE_MAP, ID); 
//      glActiveTexture(GL_TEXTURE0 + ID);
//      Sampling mode for blending textals
        
        glTexParameteri(param, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(param, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        
//      Texture Layout when sampling past texture
        glTexParameteri(param, GL_TEXTURE_WRAP_S, GL_REPEAT);   
        glTexParameteri(param, GL_TEXTURE_WRAP_T, GL_REPEAT);   
        glTexParameteri(param, GL_GENERATE_MIPMAP, GL_TRUE);
        
        glTexImage2D(param, 0, GL_RGB, Width, Height, 0, GL_BGR, GL_UNSIGNED_BYTE, Data);
        glBindTexture(GL_TEXTURE_CUBE_MAP,0);
    }
}

void Image::Bind()
{
    glBindTexture(GL_TEXTURE_2D, ID);
}
void Image::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Image::SetWH(float width, float height)
{
    Width  = width;
    Height = height;
}
void Image::GenColorTexture(float W, float H)
{
    Width = W; Height = H;
    if(Width && Height == 0)
    {
        Print("Texture Size not Initialized");
        exit(0);
    }
       glGenTextures(1, &ID);
       glBindTexture(GL_TEXTURE_2D, ID);
           glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA , Width, Height, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);
           
           glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
           glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
void Image::GenDepthTexture(float W, float H)
{
    Width = W; Height = H;
    if(Width && Height == 0)
    {
        Print("Texture Size not Initialized");
        exit(0);
    }

    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
      
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
    //    glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
    
        glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, Width, Height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
}

GLubyte* Image::LoadBMP(const char *filename)
{
    FILE *File = fopen(filename,"rb");
    if(!File)
    {
        Print("Image Could Not Be Loaded");
        return 0;
    }

    if(fread(header,1,54,File)!=54)
    {
        Print("Not the Correct BMP format");
        return 0;
    }


    dataPos   = *(int*)&(header[0x0A]);
    ImageSize = *(int*)&(header[0x22]);
    Width     = *(int*)&(header[0x12]);
    Height    = *(int*)&(header[0x16]);

    ElementCount = ImageSize;
    if(ImageSize == 0) ImageSize = Width * Height * 3;
    if(dataPos   == 0) dataPos = 54;

    GLubyte *imagedata  = new GLubyte[ImageSize];

    fread(imagedata,1,ImageSize,File);
    fclose(File);

    return imagedata;
}

//===================================================================================================================================================
//__________________________________ VERTEX BUFFER CLASS ____________________________________________________________________________________________


VertexBuffer::~VertexBuffer()
{
    Print("Deleting VertexBuffer: " << ID);
    glDeleteBuffers(1, &ID);
}
VertexBuffer::VertexBuffer(Vec3 *Vertexdata,GLsizei vcount)
            : ElementCount(vcount),
              ID(0) 
{
    Data = new Vec3[vcount];
    Data = Vertexdata;

    glGenBuffers(1 , &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
        glBufferData(GL_ARRAY_BUFFER, ElementCount * sizeof(Vec3), Vertexdata, GL_DYNAMIC_DRAW) ; 
    glBindBuffer(GL_ARRAY_BUFFER,0);
}
void VertexBuffer::Bind()
{
    _GL(glBindBuffer(GL_ARRAY_BUFFER, ID));
        glVertexPointer( 3, GL_FLOAT, 0, (char *) NULL);
        glEnableClientState(GL_VERTEX_ARRAY);
}
void VertexBuffer::Unbind()
{
        glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER,0);
}

void VertexBuffer::Lock(GLenum access)
{
        Data = (Vec3 *)glMapBuffer(ID, access);
}
void VertexBuffer::Unlock()
{
        glUnmapBuffer(ID);
}
void VertexBuffer::Rebuild()
{    //glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexPositions), &fNewData[0]);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
        glBufferSubData(GL_ARRAY_BUFFER, 0,ElementCount * sizeof(Vec3), Data) ; 
    glBindBuffer(GL_ARRAY_BUFFER,0);
}

//==================================================================================================================================================
//__________________________________ INDEX BUFFER CLASS ____________________________________________________________________________________________


IndexBuffer::IndexBuffer(){} ; IndexBuffer::~IndexBuffer(){}
IndexBuffer::IndexBuffer(GLuint *data,GLsizei count)
    : ElementCount(count)
{
        Data = new GLuint[count];
        Data = data;

        _GL(glGenBuffers(1,&ID));
        _GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ID));
        _GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER,count * sizeof(GLuint),data,GL_STATIC_DRAW));
        _GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0));
}

void IndexBuffer::Bind()
{
        _GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID));
}
void IndexBuffer::Unbind()
{
        _GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0));
}
void IndexBuffer::Rebuild()
{    //glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexPositions), &fNewData[0]);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
        glBufferSubData(GL_ARRAY_BUFFER, 0,ElementCount * sizeof(GLuint), Data) ; 
    glBindBuffer(GL_ARRAY_BUFFER,0);
}        




//==================================================================================================================================================
//__________________________________ TEXTURE BUFFER CLASS __________________________________________________________________________________________
TextureBuffer::~TextureBuffer()
{
//    delete(Image);
//    glDeleteBuffers(1, &ID);   
}
TextureBuffer::TextureBuffer(Image &img, Vec2 *data,  GLsizei count)
             : ElementCount(count) 
{
    Data = new Vec2[count];
    Data = data;

    ImageData = img;
  
// This creates the UV Buffer
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vec2) * count , data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void TextureBuffer::Bind()
{
    ImageData.Bind();
      glBindBuffer(GL_ARRAY_BUFFER, ID);      
        glTexCoordPointer(2, GL_FLOAT, 0, (char *) NULL);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}
void TextureBuffer::Unbind()
{
    glDisableVertexAttribArray(TEXTURE_ATTRIB);
    glBindBuffer(GL_ARRAY_BUFFER,0);
}
 

//==================================================================================================================================================
//__________________________________ COLOR BUFFER CLASS ____________________________________________________________________________________________
ColorBuffer::~ColorBuffer()
{
        glDeleteBuffers(1, &ID);
}
//ColorBuffer::ColorBuffer(Vec4 *ColorData, GLsizei count)
//           : ElementCount(count),
//             ID(0)
//{
//    Data = new Vec4[count];
//    Data = ColorData;
//
//    glGenBuffers(1 , &ID);
//    glBindBuffer(GL_ARRAY_BUFFER, ID);
//        glBufferData(GL_ARRAY_BUFFER, ElementCount * sizeof(Vec4), ColorData, GL_STATIC_DRAW) ; 
//    glBindBuffer(GL_ARRAY_BUFFER,0);// Unbind BUFFER_ID since its now bound to the ID;
//}
ColorBuffer::ColorBuffer(Vec3 *ColorData, GLsizei count)
           : ElementCount(count),
             ID(0)
{
    Data = new Vec3[count];
    Data = ColorData;
    glGenBuffers(1 , &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
        glBufferData(GL_ARRAY_BUFFER,ElementCount * sizeof(Vec3), ColorData, GL_STATIC_DRAW) ; 
    glBindBuffer(GL_ARRAY_BUFFER,0);// Unbind BUFFER_ID since its now bound to the ID;
}
void ColorBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);// GL_ARRAY_BUFFER
        glColorPointer( 3, GL_FLOAT, 0, (char *) NULL);
            glEnableClientState(GL_COLOR_ARRAY);
}
void ColorBuffer::Unbind(){
            glDisableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER,0);
} 
 

//==================================================================================================================================================
//__________________________________ NORMAL BUFFER CLASS ___________________________________________________________________________________________

NormalBuffer::~NormalBuffer()
{
    glDeleteBuffers(1, &ID);
}
NormalBuffer::NormalBuffer(Vec3 *NormalData, GLsizei count)
            : ElementCount(count),
              ID(0)
{
    Data = new Vec3[count];
    Data = NormalData;
    glGenBuffers(1 , &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
        glBufferData(GL_ARRAY_BUFFER, ElementCount * sizeof(Vec3), NormalData, GL_STATIC_DRAW) ; 
    glBindBuffer(GL_ARRAY_BUFFER,0); 
}
void NormalBuffer::Bind()
                
{
    glBindBuffer(GL_ARRAY_BUFFER, ID); // 
        glNormalPointer(GL_FLOAT, 0, (void *) NULL);
            glEnableClientState(GL_NORMAL_ARRAY);
}
void NormalBuffer::Unbind()
{
        glDisableClientState(GL_NORMAL_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER,0);
}








VAOBuffer::VAOBuffer()
{
        Vertices = nullptr;
        Normals  = nullptr;
        Textures = nullptr;
        Indices  = nullptr;
        Colors   = nullptr;
}

void VAOBuffer::Attach(VertexBuffer  *vertices)
{
    Vertices = vertices;
}
void VAOBuffer::Attach(IndexBuffer   *indices)
{

    Indices = indices;
}
void VAOBuffer::Attach(NormalBuffer  *normals)
{
    Normals = normals;
}
void VAOBuffer::Attach(TextureBuffer *texture)
{
    Textures = texture;
}
void VAOBuffer::Attach(ColorBuffer   *colors)
{
    Colors = colors;
}

void VAOBuffer::Bind()
{
          if(Colors)      Colors->Bind();
      if(Vertices)  Vertices->Bind();
      if(Indices)    Indices->Bind();
      if(Normals)    Normals->Bind();
      if(Textures)  Textures->Bind();

}
void VAOBuffer::Unbind()
{
          if(Colors)      Colors->Unbind();
      if(Vertices)  Vertices->Unbind();
      if(Indices)    Indices->Unbind();
      if(Normals)    Normals->Unbind();
      if(Textures)  Textures->Unbind();

}