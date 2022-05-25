#pragma once

/** This file contains the custom function signature and structure associated the scene 
*  The (*) indicates elements that are specific to the use of the camera mode  */

#include "cgp/cgp.hpp"
//#include "environment_camera_head/environment_camera_head.hpp"
#include "chevalier.hpp"

// The element of the GUI that are not already stored in other structures
struct gui_parameters {
	bool display_frame = true;
	float speed = 10.0f;       // The velocity of the camera displacement
	float sensibility = 10.0f;
	bool display_wireframe  = false;
	bool display_terrain   = true;
	bool display_tree      = true;
	bool display_mushroom  = true;
	bool display_billboard = true;
};


// The structure of the custom scene
struct scene_structure {
	
	// ****************************** //
	// Elements and shapes of the scene
	// ****************************** //

	scene_environment_camera_head environment; // The specific scene environment that contains a "head camera" (*)
	//scene_environment_with_shader_deformation environment; // The specific scene environment associated to the deforming shader (*)
	
	cgp::mesh_drawable global_frame;    // The standard global frame
	cgp::mesh_drawable terrain;         // The terrain loaded from an external file

	cgp::timer_basic timer; // A basic timer for the camera animation
	cgp::timer_basic timer2;
	cgp::skybox_drawable skybox;

	gui_parameters gui;     // The standard GUI element storage
	cgp::inputs_interaction_parameters inputs; // Storage for inputs status (mouse, keyboard, window dimension)

	cgp::mesh_drawable road;
	cgp::mesh_drawable tree;
	cgp::mesh_drawable mushroom;
	cgp::mesh_drawable billboard;
	cgp::mesh_drawable cart;
	cgp::mesh_drawable straw;
	cgp::mesh_drawable rock1;
	cgp::mesh_drawable rock2;
	cgp::mesh_drawable rock3;
	cgp::mesh_drawable lake;
	cgp::mesh_drawable knight;
	Chevalier* chevalier;

	std::vector<cgp::vec3> tree_position;
	std::vector<cgp::vec3> mushroom_position;
	std::vector<cgp::vec3> billboard_position;
	std::vector<cgp::vec3> cart_position;
	std::vector<cgp::vec3> straw_position;
	std::vector<cgp::vec3> rock_position;
	std::vector<cgp::vec3> rock_position_2;
	std::vector<cgp::vec3> rock_position_3;
	

	
	// ****************************** //
	// Functions
	// ****************************** //
	
	// Function to call in the animation loop in main (*)
	//   This function replace the standard trackball behavior that must also be removed in the main (from mouse_move_callback)
	void update_camera(int key); 
	void mouse_camera(double mouse_pos_x, double mouse_pos_y, double new_x, double new_y);
	void mouse_camera2(cgp::vec2 prev, cgp::vec2 curr);

	void display_trees();
	void display_mushroom();
	void display_billboard();

	void initialize();  // Standard initialization to be called before the animation loop
	void display();     // The frame display to be called within the animation loop
	void display_gui(); // The display of the GUI, also called within the animation loop
};





