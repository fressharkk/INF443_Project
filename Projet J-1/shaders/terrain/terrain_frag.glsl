#version 330 core  // OpenGL 3.3 shader

// Fragment shader - this code is executed for every pixel/fragment that belongs to a displayed shape

// Inputs coming from tehe vertex shader
in struct fragment_data
{ 
    vec3 position; // position in the world space
    vec3 normal;   // normal in the world space
    vec3 color;    // current color on the fragment
    vec2 uv;       // current uv-texture on the fragment*
	float visibility;
} fragment;

// Output of the fragment shader - output color
layout(location=0) out vec4 FragColor;

// Texture image
uniform sampler2D background_texture;
uniform sampler2D road_texture;
uniform sampler2D mud_texture;
uniform sampler2D dirt_texture;
uniform sampler2D burnt_texture;
uniform sampler2D blend_map;
uniform sampler2D is_burnt_texture;

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

uniform vec3 skyColor;
uniform mat4 view;       // View matrix (rigid transform) of the camera - to compute the camera position

void main()
{
	vec4 how_burnt = texture(is_burnt_texture, (fragment.position.xz + vec2(100, 100)) / 200);
	vec4 blendMapColor = texture(blend_map, (fragment.position.xz+vec2(100,100))/200);
	float backTextureAmount = 1 - (blendMapColor.r + blendMapColor.g + blendMapColor.b);
	vec2 tiledCoords = fragment.uv;

	vec4 backgroundTextureColor = vec4(0, 0, 0, 0);
	
	vec4 backgroundTextureColor1 = texture(burnt_texture, tiledCoords) * backTextureAmount;
	vec4 backgroundTextureColor2 = texture(background_texture, tiledCoords) * backTextureAmount;

	backgroundTextureColor = mix(backgroundTextureColor2, backgroundTextureColor1, how_burnt.r);

	vec4 roadTextureColor = texture(road_texture, tiledCoords) * blendMapColor.b;
	vec4 mudTextureColor = texture(mud_texture, tiledCoords) * blendMapColor.r;
	vec4 dirtTextureColor1 = texture(dirt_texture, tiledCoords) * blendMapColor.g;
	vec4 dirtTextureColor = mix(dirtTextureColor1, backgroundTextureColor1, how_burnt.r / 2);
	vec4 color_image_texture = backgroundTextureColor+roadTextureColor + mudTextureColor + dirtTextureColor;
	// Compute the position of the center of the camera
	mat3 O = transpose(mat3(view));                   // get the orientation matrix
	vec3 last_col = vec3(view*vec4(0.0, 0.0, 0.0, 1.0)); // get the last column
	vec3 camera_position = -O*last_col;

	// Re-normalize the normals (interpolated on the triangle)
	vec3 N = normalize(fragment.normal);

	// Inverse the normal if it is viewed from its back
	//  (note: doesn't work on Mac)
	if (gl_FrontFacing == false) {  
		N = -N;
	}

	// Phong coefficient (diffuse, specular)
	// ************************* //

	// Unit direction toward the light
	vec3 L = normalize(light-fragment.position);

	// Diffuse coefficient
	float diffuse = max(dot(N,L),0.0);

	// Specular coefficient
	float specular = 0.0;
	if(diffuse>0.0){
		vec3 R = reflect(-L,N); // symetric of light-direction with respect to the normal
		vec3 V = normalize(camera_position-fragment.position);
		specular = pow( max(dot(R,V),0.0), specular_exp );
	}

	

	// Compute the base color of the object based on: vertex color, uniform color, and texture
	vec3 color_object  = fragment.color * color * color_image_texture.rgb;

	// Compute the final shaded color using Phong model
	vec3 color_shading = (Ka + Kd * diffuse) * color_object + Ks * specular * vec3(1.0, 1.0, 1.0);
	
	// Output color, with the alpha component
	vec4 col = vec4(color_shading, alpha*color_image_texture.a);
	FragColor = mix(vec4(skyColor, 1.0), col, fragment.visibility);
	
}