#include "cgp/cgp.hpp"

// Standard scene environment but replacing the common rotating camera with a camera_head
//  camera_head is a camera model that rotates around its own position - this appropriate to model free-flight.
struct scene_environment_camera_head : cgp::scene_environment_basic {

	// Standard parameters (same as basic environment)
	cgp::vec3 background_color;
	cgp::camera_projection projection;
	cgp::vec3 light;  // stores the light position

	// Change the standard rotating camera to a "head camera" more appropriate to model free-flight (*)
	cgp::camera_head camera;

	cgp::vec3 part_gen_offset1 = cgp::vec3(0,0,1);
	cgp::vec3 part_gen_offset2 = cgp::vec3(0,0,1);

	scene_environment_camera_head();
	void update_particle_offsets(cgp::vec2 offset1, cgp::vec2 offset2, int nbRows, float blend);
};

void opengl_uniform(GLuint shader, scene_environment_camera_head const& environment);