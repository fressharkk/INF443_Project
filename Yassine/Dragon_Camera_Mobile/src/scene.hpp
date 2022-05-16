#pragma once

/** This file contains the custom function signature and structure associated the scene 
*  The (*) indicates elements that are specific to the use of the camera mode  */

#include "cgp/cgp.hpp"
#include "environment_camera_head/environment_camera_head.hpp"


// The element of the GUI that are not already stored in other structures
struct gui_parameters {
	bool display_frame = true;
	float speed = 10.0f;       // The velocity of the camera displacement
	float sensibility = 10.0f;
};


// The structure of the custom scene
struct scene_structure {
	
	// ****************************** //
	// Elements and shapes of the scene
	// ****************************** //

	scene_environment_camera_head environment; // The specific scene environment that contains a "head camera" (*)
	
	cgp::mesh_drawable global_frame;    // The standard global frame
	cgp::mesh_drawable terrain;         // The terrain loaded from an external file

	cgp::timer_basic timer; // A basic timer for the camera animation
	cgp::timer_basic timer2;
	cgp::skybox_drawable skybox;

	gui_parameters gui;     // The standard GUI element storage
	cgp::inputs_interaction_parameters inputs; // Storage for inputs status (mouse, keyboard, window dimension)
	cgp::hierarchy_mesh_drawable hierarchy;
	

	
	// ****************************** //
	// Functions
	// ****************************** //
	
	// Function to call in the animation loop in main (*)
	//   This function replace the standard trackball behavior that must also be removed in the main (from mouse_move_callback)
	void make_dragon();
	void update_camera(int key); 
	void mouse_camera(double mouse_pos_x, double mouse_pos_y, double new_x, double new_y);
	void mouse_camera2(cgp::vec2 prev, cgp::vec2 curr);
	void initialize();  // Standard initialization to be called before the animation loop
	void display();     // The frame display to be called within the animation loop
	void display_gui(); // The display of the GUI, also called within the animation loop
};





