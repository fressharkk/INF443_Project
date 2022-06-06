#version 330 core // OpenGL 3.3 shader

// Vertex shader - this code is executed for every vertex of the shape

// Inputs coming from VBOs
layout (location = 0) in vec3 position;  // vertex position in local space (x,y,z)
layout (location = 1) in vec3 normal;    // vertex normal in local space   (nx,ny,nz)
layout (location = 2) in vec3 color;     // vertex color      (r,g,b)
layout (location = 3) in vec2 uv;        // vertex uv-texture (u,v)

// Output variables sent to the fragment shader
out struct fragment_data
{
    vec3 position; // vertex position in world space
    vec3 normal;   // normal position in world space
    vec3 color;    // vertex color
    vec2 uv;       // vertex uv
	float visibility;
} fragment;

// Uniform variables expected to receive from the C++ program
uniform mat4 model;      // Model affine transform matrix associated to the current shape
uniform mat4 view;       // View matrix (rigid transform) of the camera
uniform mat4 projection; // Projection (perspective or orthogonal) matrix of the camera
uniform vec4 water_plane;

const float fog_density = 0.001;
const float gradient = 1.7;
void main()
{
    // The position of the vertex in the world space
	vec4 p = model * vec4(position, 1.0);

	gl_ClipDistance[0] = dot(p, water_plane);
	// The normal of the vertex in the world space
	vec4 n = model * vec4(normal, 0.0);

	// The projected position of the vertex in the normalized device coordinates:
	vec4 p_proj = projection * view * p;

	vec4 positionRelativeToCam = view * p;

	// Fill the parameters sent to the fragment shader
	fragment.position = p.xyz;
	fragment.normal   = n.xyz;
	fragment.color = color;
	fragment.uv = uv;

	float distance = length(positionRelativeToCam.xyz);
	fragment.visibility = exp(-pow((distance * fog_density), gradient));
	fragment.visibility = clamp(fragment.visibility, 0.0, 1.0);

	// gl_Position is a built-in variable which is the expected output of the vertex shader
	gl_Position = p_proj; // gl_Position is the projected vertex position (in normalized device coordinates)
}
