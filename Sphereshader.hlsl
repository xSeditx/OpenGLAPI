float4 main() : SV_TARGET
{
	return float4(1.0f, 1.0f, 1.0f, 1.0f);
}




//sphereShader.frag
#version 120


void main() {
	// Output color = color of the texture at the specified UV
	gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}


#version 120
// Input vertex data, different for all executions of this shader.
attribute vec3 vertexPosition_modelspace;

// Output data ; will be interpolated for each fragment.
varying vec2 UV;

uniform mat4 projMatrix;
uniform mat4 mvMatrix;

void main()
{
	gl_Position = projMatrix * mvMatrix * vec4(vertexPosition_modelspace, 1);
}