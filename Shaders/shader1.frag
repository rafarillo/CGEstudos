#version 330
precision highp float;

in Data{
	float xMin;
	float xMax;
	float yMin;
	float yMax;
} DataIn;


out vec4 colour;

#define MAXIter 500
#define product(a, b) vec2(a.x*b.x - a.y*b.y, a.x*b.y + a.y*b.x)


vec2 fc(vec2 z, vec2 c)
{
	return product(z, z) + c;
}

int numberOfIterations()
{
	int iteration = 0;
	vec2 value = vec2(0.0, 0.0);

	vec2 pos = vec2(gl_FragCoord.x * (DataIn.xMax - DataIn.xMin)/800 + DataIn.xMin, gl_FragCoord.y * (DataIn.yMax - DataIn.yMin)/800 + DataIn.yMin);

	
	while(length(fc(value, pos.xy)) <= 4.0 && iteration < MAXIter)
	{
		value = fc(value, pos.xy);
		iteration++;
	}
	return iteration;
}

vec4 color()
{
	int nIter = numberOfIterations();
	if(nIter == MAXIter) nIter = 0;
	return vec4(0, float(nIter)/float(MAXIter), 0, 1.0);
}


void main()
{
	colour = color();
}