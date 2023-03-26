#version 330

in Data{
	float xMin;
	float xMax;
	float yMin;
	float yMax;
} DataIn;


out vec4 colour;

#define MAXIter 700
#define product(a, b) vec2(a.x*b.x - a.y*b.y, a.x*b.y + a.y*b.x)


vec2 fc(vec2 z, vec2 c)
{
	return product(z, z) + c;
}

int numberOfIterations()
{
	int iteration = 0;
	vec2 value = vec2(0.0, 0.0);

	vec2 pos = 2*vec2(gl_FragCoord.x/800 - 0.5 - (DataIn.xMax - DataIn.xMin), gl_FragCoord.y/800 - 0.5 - (DataIn.yMax - DataIn.yMin));

	
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
	return vec4(nIter/MAXIter, nIter/MAXIter, nIter/MAXIter, 1.0);
}


void main()
{
	colour = color();
}