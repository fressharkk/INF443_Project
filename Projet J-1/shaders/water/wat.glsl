#version 330 core 

in struct fragment_data
{
	vec3 position; // position in the world space
	vec3 normal;   // normal in the world space
	vec3 color;    // current color on the fragment
	vec2 uv;       // current uv-texture on the fragment*
	float visibility;
	vec4 p_proj;
	vec3 cameraRPosition;
	vec3 fromLightVector;
} fragment;

// Output of the fragment shader - output color
layout(location = 0) out vec4 FragColor;

uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;
uniform sampler2D dudv_texture;
uniform sampler2D normal_map_texture;
uniform float wave_speed;
uniform sampler2D depthTexture;
const float distortionStrength = 0.02;

const float reflectivity = 0.6;
const float shine = 20.0;

void main(void)
{
	vec2 ndc = ((fragment.p_proj.xy) / fragment.p_proj.w);
	ndc = (ndc / 2.0) + 0.5;

	vec2 distortion1 = (texture(dudv_texture, vec2(fragment.uv.x + wave_speed, fragment.uv.y))).rg * 0.1;
	distortion1 = fragment.uv + vec2(distortion1.x, distortion1.y + wave_speed);
	vec2 total_distortion = (texture(dudv_texture, distortion1).rg * 2.0 - 1.0)* distortionStrength; 

	vec2 refractC = clamp(ndc + total_distortion, 0.001, 0.999);
	vec2 reflectC = vec2(ndc.x, - ndc.y) + total_distortion;
	reflectC.x = clamp(reflectC.x, 0.001, 0.999);
	reflectC.y = clamp(reflectC.y, -0.999, -0.001);
	vec4 refractColor = texture(refractionTexture, refractC);
	vec4 reflectColor = texture(reflectionTexture, reflectC);

	vec4 normalMapColor = texture(normal_map_texture, distortion1);
	vec3 normal = vec3(normalMapColor.r * 2.0 - 1.0, 3*normalMapColor.b, normalMapColor.g * 2.0 - 1.0);
	normal = normalize(normal);
	
	float near = 0.1;
	float far = 500.;
	float depth = texture(depthTexture, refractC).r;
	float floorDistance = 2.0 * near * far / (far + near - (2.0 * depth - 1.0) * (far - near));

	depth = gl_FragCoord.z;

	float waterDistance = 2.0 * near * far / (far + near - (2.0 * depth - 1.0) * (far - near));

	float waterDepth = floorDistance - waterDistance;

	vec3 viewV = normalize(fragment.cameraRPosition);
	float fact = dot(viewV, vec3(0,1,0));
	fact = pow(fact, 2.0);


	vec4 near_final = mix(reflectColor, refractColor, fact);
	
	

	vec3 reflectedLight = reflect(normalize(fragment.fromLightVector), normal);
	float specular = max(dot(reflectedLight, viewV), 0.0);
	specular = pow(specular, shine);
	vec3 specularHighlights = vec3(1.0, 1.0,0.96) * specular * reflectivity; // To replace by sun color

	FragColor = mix(near_final, vec4(0, 0.3, 0.5, 1), 0.2) + vec4(specularHighlights,0.0);

}