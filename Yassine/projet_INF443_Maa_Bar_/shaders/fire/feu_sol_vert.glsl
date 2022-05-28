#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 color;
layout(location = 3) in vec2 uv;

out struct fragment_data
{
	vec3 position;
	vec3 normal;
	vec3 color;
	vec2 uv;
	vec3 eye;
	float time;
	vec3 feu_attribute;

} fragment;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float time;
uniform vec3 feu_attributes;

float rand(float n) { return fract(sin(n) * 43758.5453123); }

void main()
{

	vec3 p = position.xyz;
	float length = feu_attributes.x;
	float height = feu_attributes.y;
	p.x = p.x + 0.1 * length * 2 * (rand(p.x * time) - 0.5);
	p.y = p.y + 0.4 * 2 * (rand(p.y * time) - 0.5);
	p.z = p.z + 0.1 * height * 2 * (rand(p.z * time) - 0.5);
	


	fragment.position = p;
	fragment.normal = normal;
	fragment.color = color;
	fragment.uv = uv;
	fragment.uv.x = mod((fragment.uv.x - time), 0.95);
	fragment.uv.y = mod(fragment.uv.y + 0.01 * sin(10 * time), 1);
	fragment.eye = vec3(inverse(view) * vec4(0, 0, 0, 1.0));
	fragment.time = time;
	fragment.feu_attribute = feu_attributes;

	gl_Position = projection * view * model * vec4(p, 1.0);

}