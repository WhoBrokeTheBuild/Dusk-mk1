#version 430 core

uniform sampler2D uTexDay;
uniform sampler2D uTexNight;

uniform float uTimeOfDay;

in vec2 vTexCoord;

layout (location = 0) out vec4 oFragColor;

void main()
{	
	vec2 texCoord = vTexCoord;
	texCoord.y = 1.0f - vTexCoord.y;

	vec4 dayColor   = texture(uTexDay, texCoord);
	vec4 nightColor = texture(uTexNight, texCoord);

	oFragColor = mix(dayColor, nightColor, uTimeOfDay);

	return;
}