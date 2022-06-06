#include "particle_cloud.hpp"

using namespace cgp;

Particle_Cloud::Particle_Cloud(ParticleTexture _t, bool sortPart, bool additiveBlending, std::string type)
{
	draw_p = new Particules_Draw(type, sortPart, additiveBlending);
	textureID = _t.getTextureID();
	nb_Rows = _t.getNbRows();
}

void Particle_Cloud::update_all_particles(float t)
{
	for (auto part_it = particles.begin(); part_it < particles.end(); part_it++)
	{
		bool alive = part_it->update_particle(t);
		if (!alive)
			particles.erase(part_it);
		
	}

}

void Particle_Cloud::addParticle(float current_time, cgp::vec3 center, cgp::vec3 velocity, float gravityComplient, float lifeLength, float rot, float scale)
{
	particles.push_back(Particle(current_time, textureID, nb_Rows, center, velocity, gravityComplient, lifeLength, rot, scale));
}

void Particle_Cloud::drawParticles(scene_environment_camera_head &environment)
{
	draw_p->draw_Particles(particles, environment);
}

void Particle_Cloud::addRandomParticle(float creation_time, int n, cgp::vec3 center_pos, vec3 main_vel, float lifeT, float radius, float gravEffect)
{
	
	for (int i = 0; i < n; i++)
	{
		float speed_error = norm(main_vel) * rand_interval(0.8,1);
		float lifeTime = lifeT * rand_interval(0.8,1);
		float x_dir_val = rand_interval(0.4, 1);
		float eps1 = rand_interval(-1,1);
		float eps2 =  rand_interval(-1,1);
		float x_pert = 2 * (rand_interval() - 0.5) * radius;
		float z_pert = 2 * (rand_interval() - 0.5) * radius;
		vec3 real_speed = speed_error * vec3(x_dir_val*eps1, 1, eps2 * std::sqrt(1 - x_dir_val * x_dir_val));
		particles.push_back(Particle(creation_time, textureID, nb_Rows, center_pos + vec3(x_pert, 0, z_pert), real_speed, gravEffect, lifeTime, 0, 1));
	} 
}
