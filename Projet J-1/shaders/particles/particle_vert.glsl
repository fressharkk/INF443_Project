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
    vec2 uv; 
	vec2 textureCoords1;
	vec2 textureCoords2;
	float blend;

} fragment;

// Uniform variables expected to receive from the C++ program
uniform mat4 model;      // Model affine transform matrix associated to the current shape
uniform mat4 view;       // View matrix (rigid transform) of the camera
uniform mat4 projection; // Projection (perspective or orthogonal) matrix of the camera

uniform vec3 textureOffset1; //Contains texOffset1 + nb rows
uniform vec3 textureOffset2; //Contains texOffset + blending info
uniform vec4 water_plane;

void main()
{

    // The position of the vertex in the world space
	vec4 p = model * vec4(position, 1.0);
	gl_ClipDistance[0] = dot(p, water_plane);
	// The normal of the vertex in the world space
	vec4 n = model * vec4(normal, 0.0);

	// The projected position of the vertex in the normalized device coordinates:
	vec4 p_proj = projection * view * p;

	fragment.uv = uv;

	vec2 to_send = uv;
	to_send.y = 1.0 - to_send.y;
	to_send /= textureOffset1.z;
	vec2 t1 = vec2(textureOffset1.x, textureOffset1.y);
	vec2 t2 = vec2(textureOffset1.x, textureOffset2.y);
	fragment.blend = textureOffset2.z;
	fragment.textureCoords1 = to_send + t1;
	fragment.textureCoords2 = to_send + t2;
	fragment.uv = uv;

	// gl_Position is a built-in variable which is the expected output of the vertex shader
	gl_Position = p_proj; // gl_Position is the projected vertex position (in normalized device coordinates)
}