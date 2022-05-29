#include "particles/particle_draw.hpp"

using namespace cgp;


Particules_Draw::Particules_Draw(std::string type)
{
	if (type == "quad")
	{
		mesh q = mesh_primitive_quadrangle({ -0.5,0,-0.5 }, { 0.5,0,-0.5 }, {0.5,0,0.5}, {-0.5,0,0.5});
		shape_part.initialize(q);
		shape_part.shader = opengl_load_shader("shaders/particles/particle_vert.glsl", "shaders/particles/particle_frag.glsl");
		shape_part.transform.scaling = 0.1;
	}
}

void Particules_Draw::prepare_Drawing()
{

	glEnable(GL_BLEND);
	if (use_additive_blending)
		glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_ALPHA);
	else
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDepthMask(false);
}

void Particules_Draw::finish_Drawing()
{
	glDepthMask(true);
	glDisable(GL_BLEND);
}

void Particules_Draw::draw_Particles(std::vector<Particle> particules, scene_environment_camera_head &environment)
{
	prepare_Drawing();
	vec3 const front = normalize(environment.camera.front() * vec3 { 1, 1, 0 }); 
	vec3 const right = environment.camera.right();
	rotation_transform R = rotation_transform::between_vector({ 1,0,0 }, { 0,1,0 }, right, front);
	shape_part.transform.rotation = R;
	mat4 T = environment.projection.matrix() * environment.camera.matrix_view();
	if (are_sorted_particles)
		std::sort(particules.begin(), particules.end(), [T](Particle a, Particle b) { 
		vec4 v1 = T * vec4(a.getPosition(), 1.); vec4 v2 = T * vec4(b.getPosition(), 1.);
		float za = v1.z / v1.w; float  zb = v2.z / v2.w;
		return za<zb; });

	for (auto part_it = particules.begin(); part_it != particules.end(); part_it++)
	{
		shape_part.transform.translation = part_it->getPosition();
		environment.update_particle_offsets(part_it->getTextureOffset1(), part_it->getTextureOffset2(), part_it->getNbRow(), part_it->getBlend());
		shape_part.texture = part_it->getTexture();
		draw(shape_part, environment);
	}
	finish_Drawing();
}