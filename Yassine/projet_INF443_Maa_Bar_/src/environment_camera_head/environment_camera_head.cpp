#include "environment_camera_head.hpp"

using namespace cgp;

scene_environment_camera_head::scene_environment_camera_head()
{
	background_color = { 1,1,1 };
	projection = camera_projection::perspective(50.0f * Pi / 180, 1.0f, 0.1f, 500.0f);
}

void opengl_uniform(GLuint shader, scene_environment_camera_head const& environment)
{
	// Basic uniform parameters
	opengl_uniform(shader, "projection", environment.projection.matrix());
	if (environment.is_camera_head_used)
		opengl_uniform(shader, "view", environment.camera.matrix_view());
	else
		opengl_uniform(shader, "view", environment.camera_fixe.matrix_view());

	opengl_uniform(shader, "light", environment.light, false);
	opengl_uniform(shader, "time", environment.t, false);
	opengl_uniform(shader, "flame_attributes", environment.flame_attributes, false);
	opengl_uniform(shader, "feu_attributes", environment.feu_attributes, false);
}

void scene_environment_camera_head::update(float current_time)
{
	t = current_time;          // set the current time
	if (is_camera_head_used)
		light = camera.position(); // replace the light at the camera position
	else
		light = camera_fixe.position();
}

void scene_environment_camera_head::update_flame(vec4 att)
{
	flame_attributes = att;
}