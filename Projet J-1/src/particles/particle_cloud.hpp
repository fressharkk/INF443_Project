
#include "particle_draw.hpp"


class Particle_Cloud {
public:
	std::vector<Particle> particles;
	Particules_Draw* draw_p;
	GLuint textureID;
	int nb_Rows; 

	Particle_Cloud(ParticleTexture _texture, bool sortPart, bool additiveBlending, std::string type = "quad");
	void update_all_particles(float t);
	void addParticle(float current_time, cgp::vec3 center, cgp::vec3 velocity, float gravityComplient, float lifeLength, float rot, float scale);
	void addRandomParticle(float creation_time, int n, cgp::vec3 center_pos, cgp::vec3 main_vel, float lifeT, float radius, float gravEffect);
	void drawParticles(scene_environment_camera_head&environment);
};