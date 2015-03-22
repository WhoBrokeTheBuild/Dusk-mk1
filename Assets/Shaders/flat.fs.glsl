#version 430 core

in vec4 iColor;

layout (location = 0) out vec4 oColor;

void main()
{
	oColor = iColor;
}
