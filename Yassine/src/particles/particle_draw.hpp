
#include "particles.hpp"
#include <vector>
#include <string>
#include <algorithm>

class Particules_Draw
{
public:
	cgp::mesh_drawable shape_part;
	bool use_additive_blending = false;
	bool are_sorted_particles = true;

	Particules_Draw(std::string type);
	void prepare_Drawing();
	void finish_Drawing();
	void draw_Particles(std::vector<Particle> particules, scene_environment_camera_head &environment);
	
};