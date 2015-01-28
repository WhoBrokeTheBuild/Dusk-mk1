#version 430 core

uniform sampler2D uTexDiffuse;

uniform vec3  uGlobalAmbient;
uniform vec3  uLightColor;
uniform vec3  uLightDirection;

in vec3 vNormal;
in vec2 vTexCoord;

layout (location = 0) out vec4 oFragColor;

void main()
{
	vec2 texCoord = vTexCoord;
	texCoord.y = 1.0f - vTexCoord.y;

	float diffuse = max(0.0, dot(vNormal, uLightDirection));

	vec3 scatteredLight = uGlobalAmbient + uLightColor * diffuse;

	vec4 color = texture(uTexDiffuse, texCoord);

	oFragColor.rgb = min(scatteredLight * color.rgb, vec3(1.0f));
	oFragColor.a = color.a;
}
