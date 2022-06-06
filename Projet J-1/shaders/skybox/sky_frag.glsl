#version 330 core

in struct fragment_data
{
	vec3 position;
} fragment;

layout(location = 0) out vec4 FragColor;

uniform samplerCube image_texture;
uniform samplerCube image_texture2;
uniform float blend;
uniform vec3 fogColour;
const float lowerLimit = 0.0;
const float upperLimit = 2.0;
void main()
{
	vec4 colour1 = texture(image_texture, fragment.position);
	vec4 colour2 = texture(image_texture2, fragment.position);
	float factor = (fragment.position.y - lowerLimit) / (upperLimit - lowerLimit);
	factor = clamp(factor, 0.0, 1.0);

	vec4 colour = mix(colour1, colour2, blend);
	FragColor = mix(vec4(fogColour, 1.0), colour, factor);
}
