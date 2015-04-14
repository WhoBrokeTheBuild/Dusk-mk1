#version 430 core

layout (location = 0) in vec3 iVertexPosition;
layout (location = 1) in vec3 iVertexNormal;
layout (location = 2) in vec2 iVertexTexCoord;

uniform mat4 uModelView;
uniform mat4 uModelViewProj;

out vec3 vNormal;
out vec2 vTexCoord;

void main()
{
    vNormal = normalize(mat3(uModelView) * iVertexNormal);
    vTexCoord = iVertexTexCoord;

	gl_Position = uModelViewProj * vec4(iVertexPosition, 1.0f);
}
