#include "Feu.hpp"


using namespace cgp;

float distance_2(vec2 xy, vec2 center)
{
	return std::sqrt((xy.x - center.x) * (xy.x - center.x) + (xy.y - center.y) * (xy.y - center.y));
}

Feu::Feu(cgp::vec3 _center, float _length, float _height, cgp::vec3& feu_attributes)
{
	center = _center;
	length = _length;
	height = _height;
	primitive_mesh = mesh_primitive_grid(center - vec3(length / 2, center.y, height / 2), center + vec3(length / 2, center.y, -height / 2),
		center + vec3(length / 2, center.y, height / 2), center + vec3(-length / 2, center.y, height / 2), 40, 40);
	apply_noise();
	
	mesh_to_draw.initialize(primitive_mesh);
	GLuint const shader = opengl_load_shader("shaders/fire/feu_sol_vert.glsl", "shaders/fire/feu_sol_frag.glsl");
	mesh_to_draw.texture = opengl_load_texture_image("assets/texture_flamme_throwing.jpg");
	mesh_to_draw.shader = shader;
	
	feu_attributes = vec3(length, height, 0);
}
void Feu::apply_noise(std::string type)
{
	if (type == "Perlin")
	{
		for (auto pos = primitive_mesh.position.begin(); pos < primitive_mesh.position.end(); pos++)
		{
			
			pos->y += noise_perlin(distance_2(vec2(pos->x, pos->z), vec2(center.x, center.z)));
			
		}
	}

	if (type == "Simplex")
	{
		for (auto pos = primitive_mesh.position.begin(); pos < primitive_mesh.position.end(); pos++)
		{
			pos->y += snoise2(pos->x, pos->z);

		}
	}
}
void Feu::draw_feu(scene_environment_camera_head& environment)
{

	draw(mesh_to_draw, environment);
}
