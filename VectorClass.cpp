#include "Vector.h"
#include "Window.h"


Vec3 XRotate_Object(int Object, float angle){
    _GL(glMatrixMode( GL_MODELVIEW));
    _GL(glLoadIdentity());
    _GL(glRotatef(angle, 1.0, 0, 0 ));  
}
Vec3 YRotate_Object(){

}
Vec3 ZRotate_Object(){

}