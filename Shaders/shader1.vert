#version 330
layout (location = 0) in vec3 pos;
precision highp float;

uniform float xMin;
uniform float xMax;

uniform float yMin;
uniform float yMax;

out Data{
	float xMin;
	float xMax;
	float yMin;
	float yMax;
} DataOut;

void main()
{
	DataOut.xMin = xMin;
	DataOut.xMax = xMax;
	DataOut.yMin = yMin;
	DataOut.yMax = yMax;
	gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
}
