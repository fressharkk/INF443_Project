#include "particle_cloud.hpp"

using namespace cgp;

Particle_Cloud::Particle_Cloud(ParticleTexture _t, std::string type)
{
	draw_p = new Particules_Draw(type);
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

void Particle_Cloud::drawParticles(scene_environment_camera_head &environment)
{
	draw_p->draw_Particles(particles, environment);
}

void Particle_Cloud::addRandomParticle(float creation_time, int n, cgp::vec3 center_pos, vec3 main_vel, float lifeT, float radius, float gravEffect)
{
	
	for (int i = 0; i < n; i++)
	{
		float speed_error = norm(main_vel) * rand_interval();
		float lifeTime = lifeT * rand_interval();
		float x_dir_val = rand_interval();
		float eps1 = rand_interval(-1,1);
		float eps2 =  rand_interval(-1,1);
		float x_pert = 2 * (rand_interval() - 0.5) * radius;
		float y_pert = 2 * (rand_interval() - 0.5) * radius;
		vec3 real_speed = speed_error * vec3(x_dir_val*eps1, eps2 * std::sqrt(1 - x_dir_val * x_dir_val),1);
		particles.push_back(Particle(creation_time, textureID, nb_Rows, center_pos + vec3(x_pert, y_pert, 0), real_speed, gravEffect, lifeTime, 0, 1));
	} 
}
