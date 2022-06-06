
#include "particles.hpp"
#include <vector>
#include <string>
#include <algorithm>

class Particules_Draw
{
public:
	cgp::mesh_drawable shape_part;
	bool use_additive_blending = true;
	bool are_sorted_particles = false;
	GLint shader_val;
	Particules_Draw(std::string type, bool sortParticles, bool additiveBlending);
	void prepare_Drawing();
	void finish_Drawing();
	void draw_Particles(std::vector<Particle> particules, scene_environment_camera_head &environment);
	void myDraw(std::vector<Particle> particule, cgp::mesh_drawable &m, scene_environment_camera_head& environment);
	
};