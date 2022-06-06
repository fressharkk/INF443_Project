#pragma once

#include "cgp/cgp.hpp"

// Standard scene environment but replacing the common rotating camera with a camera_head
//  camera_head is a camera model that rotates around its own position - this appropriate to model free-flight.
struct scene_environment_camera_head {
	
	bool use_water_camera = false;
	// Standard parameters (same as basic environment)
	cgp::vec3 background_color;
	cgp::camera_projection projection;
	cgp::vec3 light;  // stores the light position

	cgp::vec4 water_plane;
	cgp::vec3 fogColor =cgp::vec3(0.3,0.3,0.3);

	// Change the standard rotating camera to a "head camera" more appropriate to model free-flight (*)
	cgp::camera_head camera;
	cgp::camera_spherical_coordinates water_camera;
	cgp::camera_spherical_coordinates camera_fixe;

	cgp::vec3 part_gen_offset1 = cgp::vec3(0, 0, 1);
	cgp::vec3 part_gen_offset2 = cgp::vec3(0, 0, 1);

	bool is_camera_head_used = true;
	bool invert = false;
	float t;         // The time is sent to the shader to compute a procedural deformation
	cgp::vec4 flame_attributes;
	cgp::vec3 feu_attributes;

	void update(float t); // function to be called in the scene display - update the time t and the light position
	void update_flame(cgp::vec4 flame_att);
	void update_water_camera();
	void update_particle_offsets(cgp::vec2 offset1, cgp::vec2 offset2, int nbRows, float blend);
	scene_environment_camera_head();
};

void opengl_uniform(GLuint shader, scene_environment_camera_head const& environment);

