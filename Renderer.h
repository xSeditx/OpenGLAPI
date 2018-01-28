#include<vector>
#include"Vertex.h"
using namespace std;
class RenderTarget{
public:
//	BlendMode 	blendMode
// 	Blending mode. 
// 
//Transform 	transform
// 	Transform. 
// 
//const Texture * 	texture
// 	Texture. 
// 
//const Shader * 	shader
// 	Shader. 
//
//private:
};


class Renderer{



private:
    vector<Matrix4> Transformation_Stack;
    void push(Matrix4 mat4){
    }
    Matrix4 pop(){
        Matrix4 ret = Transformation_Stack.back();
            Transformation_Stack.pop_back();
        return ret;
    }
};



class Scene{
};