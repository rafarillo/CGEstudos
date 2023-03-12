#version 330
layout (location = 0) in vec3 pos;

uniform float xMin;
uniform float xMax;

uniform float yMin;
uniform float yMax;


void main()
{
	gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);

}
