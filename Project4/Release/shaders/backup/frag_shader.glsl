#version 330 core

in vec3 outColor;

out vec3 FragColor;

void main()
{
	float lin = 1.0/gl_FragCoord.w;
	float depth = (lin - 0.5)/(16.0 - 0.5);
	FragColor = vec3(1.0f, 0.0f, 0.0f); //vec3(outColor);
}
