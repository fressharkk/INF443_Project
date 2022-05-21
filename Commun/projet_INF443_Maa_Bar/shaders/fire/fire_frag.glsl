#version 330 core

in struct fragment_data
{
    vec3 position;
    vec3 normal;
    vec3 color;
    vec2 uv;
    vec3 eye;
	float time;
} fragment;

layout(location = 0) out vec4 FragColor;

uniform sampler2D image_texture;

uniform vec3 light = vec3(1.0, 1.0, 1.0);

uniform vec3 color = vec3(1.0, 1.0, 1.0); // Unifor color of the object
uniform float alpha = 1.0f; // alpha coefficient
uniform float Ka = 0.4; // Ambient coefficient
uniform float Kd = 0.8; // Diffuse coefficient
uniform float Ks = 0.4f;// Specular coefficient
uniform float specular_exp = 64.0; // Specular exponent

uniform bool use_texture = true;
uniform bool texture_inverse_y = false;


uniform mat4 view;       // View matrix (rigid transform) of the camera - to compute the camera position


void main()
{
	float _alpha = 1-alpha;
	vec3 cone_pic_coord = vec3(0., 0., 15.);
	vec2 uv_image = vec2(fragment.uv.x, fragment.uv.y);
	vec4 color_image_texture = texture(image_texture, uv_image);
	
	vec2 plan_p = vec2(fragment.position.x, fragment.position.y);
	float fire_speed = 1;
	float distance_to_center = fragment.position.x * fragment.position.x + fragment.position.y * fragment.position.y + (fragment.position.z-15) * (fragment.position.z-15);
	if (distance_to_center < fire_speed * fire_speed * (fragment.time * fragment.time))
		_alpha = 1.0;

	if (color_image_texture.rgb.x < 0.3)
		_alpha = 0.0;

	

	vec3 color_object = fragment.color * color * color_image_texture.rgb;
	//vec3 color_shading = (Ka + Kd * diffuse) * color_object; //+Ks * specular * vec3(1.0, 1.0, 1.0);
	vec3 color_shading = color_image_texture.rgb;



	FragColor = vec4(color_shading,_alpha);
}