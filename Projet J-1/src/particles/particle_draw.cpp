#include "particles/particle_draw.hpp"

using namespace cgp;


Particules_Draw::Particules_Draw(std::string type,bool sortParticles, bool additiveBlending)
{
	use_additive_blending = additiveBlending;
	are_sorted_particles = sortParticles;
	if (type == "quad")
	{
		mesh q = mesh_primitive_quadrangle({ -0.5,-0.5,0}, { 0.5,-0.5,0 }, {0.5,0.5,0}, {-0.5,0.5,0});
		shape_part.initialize(q);
		shape_part.shader = opengl_load_shader("shaders/particles/particle_vert.glsl", "shaders/particles/particle_frag.glsl");
		//shape_part.transform.scaling = 0.1;
	}
	else if (type == "disc")
	{
		mesh q = mesh_primitive_disc(); 
		shape_part.initialize(q);
		shape_part.shader = opengl_load_shader("shaders/particles/particle_vert.glsl", "shaders/particles/particle_frag.glsl");
		//shape_part.transform.scaling = 0.1;
	}
}

void Particules_Draw::prepare_Drawing()
{

	glEnable(GL_BLEND);
	if (use_additive_blending)
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
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
	vec3 front_cam;
	vec3 right_cam; 
	mat4 T;
	bool up = true;
	if (environment.is_camera_head_used)
	{
		return;
		front_cam = environment.camera.front()* vec3(1, 0, 1);
		if (std::abs(dot(environment.camera.up(), vec3(0, 1, 0))) < 0.87)
			right_cam = environment.camera.up();
		else {
			right_cam = environment.camera.right(); up = false;
		}
		T = environment.projection.matrix() * environment.camera.matrix_view();
	}
	else
	{
		right_cam = environment.camera_fixe.right();
		front_cam = environment.camera_fixe.front() * vec3(1, 0, 1);
		T = environment.projection.matrix() * environment.camera_fixe.matrix_view();
	}
		
		
		if (norm(front_cam) < 0.0001)
			return;

		else front_cam = normalize(front_cam);


		if (std::abs(dot(right_cam, front_cam)) > 0.000001)
			return;

		std::cout << "FRONT " << front_cam << std::endl;
		std::cout << "UP/RIGHT" << up << "   " << right_cam << std::endl;
		
		rotation_transform R;
		if (environment.is_camera_head_used)
		{
			if (up)
				R = rotation_transform::between_vector({ 0,1,0 }, { 0,0,-1 }, right_cam, front_cam);
			else
				R = rotation_transform::between_vector({ 1,0,0 }, { 0,0,-1 }, right_cam, front_cam);
		}
			 
		else
			 R = rotation_transform::between_vector({ 1,0,0 }, { 0,0,1 }, right_cam, front_cam);

		if (R.data.x == 0 && R.data.y == 0 && R.data.z == 0 && R.data.w == 1)
			return;

		shape_part.transform.rotation = R;
	

	
	
	if (are_sorted_particles)
	{
		std::sort(particules.begin(), particules.end(), [T](Particle a, Particle b) {
			vec4 v1 = T * vec4(a.getPosition(), 1.); vec4 v2 = T * vec4(b.getPosition(), 1.);
			float za = v1.z / v1.w; float  zb = v2.z / v2.w; return za < zb;});
	}
	prepare_Drawing();
	for (auto part_it = particules.begin(); part_it != particules.end(); part_it++)
	{
		shape_part.transform.translation = part_it->getPosition();
		environment.update_particle_offsets(part_it->getTextureOffset1(), part_it->getTextureOffset2(), part_it->getNbRow(), part_it->getBlend());
		shape_part.texture = part_it->getTexture(); 
		float ratio = part_it->getElapsedTime() / part_it->getLifeTime();
		float diff  = part_it->getElapsedTime() - part_it->getLifeTime();
		float shape_coeff =   1;
		shape_part.transform.scaling = part_it->getScale();
		draw(shape_part, environment);
	}
	finish_Drawing();
}

void Particules_Draw::myDraw(std::vector<Particle> particules, mesh_drawable &m, scene_environment_camera_head &environment)
{
	//shape_part.shading.color = vec3(1, 0, 0);
	//shape_part.texture = shader_val;
	//glBindVertexArray(shape_part.vao);
	//glEnableVertexAttribArray(0);
	//glEnable(GL_BLEND);
	//glBlendEquation(GL_FUNC_ADD);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	//glDepthMask(false);
	////glDrawArrays(GL_TRIANGLE_STRIP, 0, 3*shape_part.number_triangles)
	//draw(shape_part, environment);
	//draw(shape_part, environment);
	//
	//glDepthMask(true);
	//glDisable(GL_BLEND);
	//glDisableVertexAttribArray(0);
	//glBindVertexArray(0);
}
