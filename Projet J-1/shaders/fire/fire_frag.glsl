#version 330 core

in struct fragment_data
{
    vec3 position;
    vec3 normal;
    vec3 color;
    vec2 uv;
    vec3 eye;
	float time;
	vec4 flame_attribute;
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
	float cone_height = fragment.flame_attribute.y;
	float beginning_time = fragment.flame_attribute.w;

	vec3 cone_pic_coord = vec3(0., 0., cone_height);
	vec2 uv_image = vec2(fragment.uv.x, fragment.uv.y);
	vec4 color_image_texture = texture(image_texture, uv_image);
	
	vec2 plan_p = vec2(fragment.position.x, fragment.position.y);
	float fire_speed = fragment.flame_attribute.z;
	float distance_to_center = fragment.position.x * fragment.position.x + fragment.position.y * fragment.position.y + (fragment.position.z-cone_height) * (fragment.position.z-cone_height);
	if (fragment.time - beginning_time > 0)
	{
	if (distance_to_center < fire_speed * fire_speed * ((fragment.time-beginning_time) * (fragment.time-beginning_time)))
		_alpha = 1.0;
	}
	else
	{
	_alpha = 0.0;
	}
	if (color_image_texture.rgb.x < 0.3)
		_alpha = 0.0;

	

	vec3 color_object = fragment.color * color * color_image_texture.rgb;
	//vec3 color_shading = (Ka + Kd * diffuse) * color_object; //+Ks * specular * vec3(1.0, 1.0, 1.0);
	vec3 color_shading = color_image_texture.rgb;



	FragColor = vec4(color_shading,_alpha);
}