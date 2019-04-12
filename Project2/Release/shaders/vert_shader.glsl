#version 330 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 color;

//out vec3 outColor;

//uniform mat4 model;
//uniform mat4 view;
//uniform mat4 projection;

uniform mat4 MVP;

void main()
{
	gl_Position = MVP*vec4(vertex,1.0f);
	//outColor = color;
}
