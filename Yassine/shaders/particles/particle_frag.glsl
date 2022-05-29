#version 330 core  // OpenGL 3.3 shader

// Fragment shader - this code is executed for every pixel/fragment that belongs to a displayed shape

// Inputs coming from tehe vertex shader
in struct fragment_data
{ 
    vec2 uv;      // current uv-texture on the fragment
    vec2 textureCoords1;
	vec2 textureCoords2;
	float blend;

} fragment;

// Output of the fragment shader - output color
layout(location=0) out vec4 FragColor;

// Texture image
uniform sampler2D image_texture;

// Uniform values - must be send from the C++ code
uniform vec3 light; // position of the light

// Shape color
uniform vec3 color;   // Uniform color of the object
uniform float alpha;  // alpha coefficient

// Phong shading
uniform float Ka;     // Ambient coefficient
uniform float Kd;     // Diffuse coefficient
uniform float Ks;     // Specular coefficient
uniform float specular_exp; // Specular exponent

uniform mat4 view;       // View matrix (rigid transform) of the camera - to compute the camera position

void main()
{
	vec4 colour1 = texture(image_texture, fragment.textureCoords1);
	vec4 colour2 = texture(image_texture, fragment.textureCoords2);

	FragColor = mix(colour1, colour2, fragment.blend);
}