// *******Credit for Verctor classes and Matrix Code goes to Cherno and were written for his Sparky Game Engine.


#include "Vertex.h"
#include "Window.h"
//=====================================================================================================================================
//_____________________________________________________________________________________________________________________________________


Vec2::Vec2(){x = 0.0f;y=0.0f;}

Vec2::Vec2(const float& x,const float& y){this->x=x;this->y=y;}

Vec2& Vec2::add(const Vec2& other){
	x += other.x; y += other.y;
	return *this;
}

Vec2& Vec2::subtract(const Vec2& other){
	x -= other.x; y -= other.y;
	return *this;
}

Vec2& Vec2::divide(const Vec2& other){
	x /= other.x; y /= other.y;
	return *this;
}

Vec2& Vec2::multiply(const Vec2& other){
	x *= other.x; y *= other.y;
	return *this;
}


Vec2 operator +(Vec2 left, const Vec2& right){return left.add(right);}
Vec2 operator -(Vec2 left, const Vec2& right){return left.subtract(right);}
Vec2 operator /(Vec2 left, const Vec2& right){return left.divide(right);}
Vec2 operator *(Vec2 left, const Vec2& right){return left.multiply(right);}
//_____________________________________________________________________________________________________________________________________
Vec2& Vec2::operator +=(const Vec2& other){return add(other);}
Vec2& Vec2::operator -=(const Vec2& other){return subtract(other);}
Vec2& Vec2::operator *=(const Vec2& other){return multiply(other);}
Vec2& Vec2::operator /=(const Vec2& other){return divide(other);}
//_____________________________________________________________________________________________________________________________________

//_____________________________________________________________________________________________________________________________________
bool Vec2::operator ==(const Vec2& other){return x == other.x && y == other.y;}
bool Vec2::operator !=(const Vec2& other){return !(*this == other);}
//_____________________________________________________________________________________________________________________________________

std::ostream& operator<<(std::ostream& stream,const Vec2& vector){
	stream << "vec2: (" << vector.x <<") vec2: ("<< vector.y<<")";
	return stream;
}



//=====================================================================================================================================
//_____________________________________________________________________________________________________________________________________

Vec3::Vec3()
{
x = 0.0f;
y = 0.0f;
z = 0.0f;
}

Vec3::Vec3(const float& x,const float& y,const float& z)
{
this->x=x;
this->y=y;
this->z=z;
}

Vec3& Vec3::add(const Vec3& other)
{
	x += other.x; y += other.y;x += other.z;
	return *this;
}

Vec3& Vec3::subtract(const Vec3& other)
{
	x -= other.x; y -= other.y;z -= other.z;
	return *this;
}

Vec3& Vec3::divide(const Vec3& other)
{
	x /= other.x; y /= other.y;z /= other.z;
	return *this;
}

Vec3& Vec3::multiply(const Vec3& other)
{
	x *= other.x; y *= other.y;z *= other.z;
	return *this;
}


Vec3 operator +(Vec3 left, const Vec3& right)
{
	return left.add(right);
}

	Vec3 operator -(Vec3 left, const Vec3& right)
{
	return left.subtract(right);
}

	Vec3 operator /(Vec3 left, const Vec3& right)
{
	return left.divide(right);
}

	Vec3 operator *(Vec3 left, const Vec3& right)
{
	return left.multiply(right);
}
//_____________________________________________________________________________________________________________________________________
Vec3& Vec3::operator +=(const Vec3& other){return add(other);}
Vec3& Vec3::operator -=(const Vec3& other){return subtract(other);}
Vec3& Vec3::operator *=(const Vec3& other){return multiply(other);}
Vec3& Vec3::operator /=(const Vec3& other){return divide(other);}
//_____________________________________________________________________________________________________________________________________

bool Vec3::operator ==(const Vec3& other)
{
return x == other.x && y == other.y && z == other.z;
}

bool Vec3::operator !=(const Vec3& other)
{
return !(*this == other);
}
//_____________________________________________________________________________________________________________________________________



std::ostream& operator<<(std::ostream& stream,const Vec3& vector)
{
	stream << "Vec3:X (" << vector.x <<") Vec3:Y ("<< vector.y<<") Vec3:Z ("<< vector.z << ")";
		return stream;
}



//=====================================================================================================================================
//_____________________________________________________________________________________________________________________________________


Vec4::Vec4()
{
x = 0.0f;
y = 0.0f;
z = 0.0f;
w = 0.0f;
}

Vec4::Vec4(const float& x,const float& y,const float& z,const float& w)
{
this->x=x;
this->y=y;
this->z=z;
this->w=w;
}

Vec4& Vec4::add(const Vec4& other)
{
	x += other.x; y += other.y;z += other.z;w += other.w;
	return *this;
}

Vec4& Vec4::subtract(const Vec4& other)
{
	x -= other.x; y -= other.y;z -= other.z;w -= other.w;
	return *this;
}

Vec4& Vec4::divide(const Vec4& other)
{
	x /= other.x; y /= other.y;z /= other.z;w /= other.w;
	return *this;
}

Vec4& Vec4::multiply(const Vec4& other)
{
	x *= other.x; y *= other.y;z *= other.z;w *= other.w;
	return *this;
}


Vec4 operator +(Vec4 left, const Vec4& right)
{
	return left.add(right);
}

Vec4 operator -(Vec4 left, const Vec4& right)
{
	return left.subtract(right);
}

Vec4 operator /(Vec4 left, const Vec4& right)
{
	return left.divide(right);
}

Vec4 operator *(Vec4 left, const Vec4& right)
{
	return left.multiply(right);
}
//_____________________________________________________________________________________________________________________________________
Vec4& Vec4::operator +=(const Vec4& other){return add(other);}
Vec4& Vec4::operator -=(const Vec4& other){return subtract(other);}
Vec4& Vec4::operator *=(const Vec4& other){return multiply(other);}
Vec4& Vec4::operator /=(const Vec4& other){return divide(other);}
//_____________________________________________________________________________________________________________________________________



//_____________________________________________________________________________________________________________________________________

bool Vec4::operator ==(const Vec4& other)
{
return x == other.x && y == other.y && z == other.z && w == other.w;
}

bool Vec4::operator !=(const Vec4& other)
{
return !(*this == other);
}
//_____________________________________________________________________________________________________________________________________



std::ostream& operator<<(std::ostream& stream,const Vec4& vector)
{
	stream << "Vec4:X (" << vector.x <<") Vec4:Y ("<< vector.y<<") Vec4:Z ("<< vector.z << ") Vec4:W (" << vector.w << ")";
	return stream;
}



//_____________________________________________________________________________________________________________________________________

//__________Matrix Initializations_____________________________________________________________________________________________________

Matrix4::Matrix4()
{
    for(int i=0;i<4;i++)
		           elements[i]=0.0f;
}

Matrix4::Matrix4(float diagonal)
{
  for(int i=0;i < 4*4; i++)
		           elements[i]=0.0f;

  elements[0 + 0 * 4] = 1.0f;
  elements[1 + 1 * 4] = 1.0f;
  elements[2 + 2 * 4] = 1.0f;
  elements[3 + 3 * 4] = 1.0f;
}

 Matrix4 Matrix4::Identity()
{  
	return Matrix4(1.0f);
}

//_____________________________________________________________________________________________________________________________________

Matrix4& Matrix4::Multiply(const Matrix4& other)
{
  float sum = 0.0f;
  for (int y = 0;y < 4;y++){
	   for (int x= 0;x < 4;x++){
		    for (int e = 0;e < 4;e++){
				 sum += elements[x + e * 4] * other.elements[e+y*4];
			}
			elements[x + y * 4] = sum;
	   }
  }
//memcpy(elements, data, 4 * 4 * sizeof(float));
return *this;
}




	
//_____________________________________________________________________________________________________________________________________
//__________Operator Overloads_________________________________________________________________________________________________________

Matrix4 operator*(Matrix4 left,Matrix4& right)
{
	return left.Multiply(right);
}

Matrix4& Matrix4::operator *=(const Matrix4& other){
return Multiply(other);
}

//____________________________________________________________________________________________________________________________________
//____________Matrixes________________________________________________________________________________________________________________

 Matrix4 Matrix4::Orthographic(float Left,float Right,float Top,float Bottom,float Near, float Far)
 {
 	Matrix4 result(1.0f);
 
 	result.elements[0 + 0 * 4] = 2.0f/ (Right - Left);
 	result.elements[1 + 1 * 4] = 2.0f/ (Top - Bottom);
 	result.elements[2 + 2 * 4] = 2.0f/ (Near - Far);
 
 	result.elements[0 + 3 * 4] = (Left + Right) / (Left - Right);
 	result.elements[1 + 3 * 4] = (Bottom - Top) / (Bottom - Top);
 	result.elements[2 + 3 * 4] = (Far - Near) / (Far - Near);
 
 	return result;
 }

 Matrix4 Matrix4::Perspective(float FOV,float Aspect_Ratio,float Near,float Far)
 {
 	Matrix4 result(1.0f);
 
 	float q = 1.0f / (float)tan((.5 * (3.14159 / 180.0f))*FOV);
 	float a = q / Aspect_Ratio;
 
 	float b = (Near + Far) / (Near - Far);
 	float c = (2.0f * Near * Far) / (Near - Far);
 
 	result.elements[0 + 0 * 4] = a;
 	result.elements[1 + 1 * 4] = q;
 	result.elements[2 + 2 * 4] = b;
 
 	result.elements[3 + 2 * 4] = -1.0f;
     result.elements[2 + 3 * 4] = c;
 
 	return result;
 }	   
 
 Matrix4 Matrix4::Rotation(float Angle,const Vec3& Axis)
 {
 	Matrix4 result(1.0f);
 
 	float r = (float)(Angle  * (3.14159 / 180.0f));
 	float c = cos(r);
 	float s = sin(r);
 	float omc = 1.0f - c;
 
 	float x = Axis.x;
 	float y = Axis.y;
 	float z = Axis.z;
 
 	result.elements[0 + 0 * 4] = x  * omc + c;
 	result.elements[1 + 0 * 4] = y * x * omc + z * s;
 	result.elements[2 + 0 * 4] = x * z * omc - y * s; 	
 
 	result.elements[0 + 1 * 4] = x * y * omc - z * s;
 	result.elements[1 + 1 * 4] = y * omc + c;
 	result.elements[2 + 1 * 4] = y * z * omc + x * s;
 
 	result.elements[0 + 2 * 4] = x * z * omc + y * s;
 	result.elements[1 + 2 * 4] = y * z * omc + x * s;
 	result.elements[2 + 2 * 4] = z * omc + c; 
 
 	return result;
 }
 
 Matrix4 Matrix4::Translation(const Vec3& Translation)
 {
 	Matrix4 result(1.0f);
 
 	result.elements[0 + 3 * 4] = Translation.x;
 	result.elements[1 + 3 * 4] = Translation.y;
 	result.elements[2 + 3 * 4] = Translation.z;
 
 	return result;
 }

 Matrix4 Matrix4::Scale(const Vec3& Scale)
 {
 	Matrix4 result(1.0f);
 
 	result.elements[0 + 0 * 4] = Scale.x;
 	result.elements[1 + 1 * 4] = Scale.y;
 	result.elements[2 + 2 * 4] = Scale.z;
 
 	return result;
 
 }
 

//=====================================================================================================================================
//_____________________________________________________________________________________________________________________________________


Vec3 XRotate_Object(int Object, float angle){
    _GL(glMatrixMode( GL_MODELVIEW));
    _GL(glLoadIdentity());
    _GL(glRotatef(angle, 1.0, 0, 0 ));  
}
Vec3 YRotate_Object(){
	return Vec3(0.0, 0.0, 0.0);
}
Vec3 ZRotate_Object(){
	return Vec3(0.0, 0.0, 0.0);
}