
#include "cgp/cgp.hpp"

// Standard scene environment but replacing the common rotating camera with a camera_head
//  camera_head is a camera model that rotates around its own position - this appropriate to model free-flight.
struct scene_environment_camera_head {

	// Standard parameters (same as basic environment)
	cgp::vec3 background_color;
	cgp::camera_projection projection;
	cgp::vec3 light;  // stores the light position

	// Change the standard rotating camera to a "head camera" more appropriate to model free-flight (*)
	cgp::camera_head camera;
	cgp::camera_spherical_coordinates camera_fixe;

	bool is_camera_head_used = true;

	float t;         // The time is sent to the shader to compute a procedural deformation
	cgp::vec4 flame_attributes;
	cgp::vec3 feu_attributes;

	void update(float t); // function to be called in the scene display - update the time t and the light position
	void update_flame(cgp::vec4 flame_att);

	scene_environment_camera_head();
};

void opengl_uniform(GLuint shader, scene_environment_camera_head const& environment);

