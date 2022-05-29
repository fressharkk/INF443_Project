#include "scene.hpp"

/** This file contains the custom implementation associated the scene 
*  The (*) indicates elements that are specific to the use of the camera mode and that should be handled if you want to use this effect in another scene. */

using namespace cgp;




// The main function implementing the Flying Mode
void scene_structure::update_camera()
{
	inputs_keyboard_parameters const& keyboard = inputs.keyboard;
	camera_head& camera = environment.camera;

	// The camera moves forward all the time
	//   We consider in this example a constant velocity, so the displacement is: velocity * dt * front-camera-vector
	float const dt = timer.update();
	vec3 const forward_displacement = gui.speed * 0.1f * dt * camera.front();
	//camera.position_camera += forward_displacement;

	// The camera rotates if we press on the arrow keys
	//  The rotation is only applied to the roll and pitch degrees of freedom.
	float const pitch = 0.5f; // speed of the pitch
	float const roll  = 0.7f; // speed of the roll
	if (keyboard.up)
		p->draw_p->are_sorted_particles = !p->draw_p->are_sorted_particles;
		//camera.manipulator_rotate_roll_pitch_yaw(0, -pitch * dt, 0); 
	if (keyboard.down)
		camera.manipulator_rotate_roll_pitch_yaw(0,  pitch * dt, 0); 
	if (keyboard.right)
		p->draw_p->use_additive_blending = !p->draw_p->use_additive_blending;
		//camera.manipulator_rotate_roll_pitch_yaw( roll * dt, 0, 0);
	if (keyboard.left)
	{
		p->addRandomParticle(timer.t, 100, vec3(0, 0, 0), vec3(0, 0, 1), 10, 1, 0.05);
	}
}

void scene_structure::initialize()
{
	// Default frame
	global_frame.initialize(mesh_primitive_frame(), "Frame");
	GLuint text = opengl_load_texture_image("assets/Particles_Texture/fire.png");
	std::cout << text << std::endl;
	ParticleTexture p_text = ParticleTexture(text, 8);
	// Load the terrain (display a debug message as the loading can take some time)
	std::cout << " \nLoad terrain file ..." << std::endl;
	//terrain.initialize(mesh_load_file_obj("assets/mountain.obj"), "Terrain");
	std::cout << " [OK] Terrain loaded\n" << std::endl;

	// Load the texture of the terrain
	std::cout << " \nLoad terrain texture ..." << std::endl;
	//terrain.texture = opengl_load_texture_image("assets/mountain.jpg");
	std::cout << " [OK] Texture loaded\n" << std::endl;
	

	// Initial placement of the camera
	environment.camera.position_camera = { 5, 5, 5.0f };
	environment.camera.manipulator_rotate_roll_pitch_yaw(0, 0, Pi / 2.0f);
	p = new Particle_Cloud(p_text,"quad");
	p->addRandomParticle(0, 100, vec3(0, 0, 0), vec3(0, 0, 1), 10, 0.2, 0.1);
	
	timer.start();
}



void scene_structure::display()
{	
	timer.update();

	// set the light position to the camera
	environment.light = environment.camera.position(); 

	// The standard frame
	if (gui.display_frame)
		draw(global_frame, environment);

	//draw(terrain, environment);
	p->update_all_particles(timer.t);
	p->drawParticles(environment);
	// Displaying the shape deformed by the shader
	
}



void scene_structure::display_gui()
{
	ImGui::Checkbox("Frame", &gui.display_frame);
	ImGui::SliderFloat("Speed", &gui.speed, 0.2f, 5.0f); // Set the camera velocity
}


