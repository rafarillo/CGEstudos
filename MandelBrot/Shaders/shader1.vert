#version 330
layout (location = 0) in vec3 pos;

out Data{
	float xMin;
	float xMax;
	float yMin;
	float yMax;
} DataOut;

void main()
{
	gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
}
