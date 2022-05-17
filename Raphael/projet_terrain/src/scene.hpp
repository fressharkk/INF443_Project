#pragma once

#include "cgp/cgp.hpp"

// The element of the GUI that are not already stored in other structures
struct gui_parameters {
	bool display_frame      = true;
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

	cgp::mesh_drawable global_frame;          // The standard global frame
	cgp::scene_environment_basic_camera_spherical_coords environment; // Standard environment controler
	cgp::inputs_interaction_parameters inputs; // Storage for inputs status (mouse, keyboard, window dimension)

	gui_parameters gui;                       // Standard GUI element storage
	
	cgp::mesh_drawable terrain;
	cgp::mesh_drawable road;
	// Timer used for the animation
	cgp::timer_basic timer;

	cgp::skybox_drawable skybox;

	cgp::mesh_drawable tree;
	cgp::mesh_drawable mushroom;
	cgp::mesh_drawable billboard;
	cgp::mesh_drawable cart;
	cgp::mesh_drawable straw;

	std::vector<cgp::vec3> tree_position;
	std::vector<cgp::vec3> mushroom_position;
	std::vector<cgp::vec3> billboard_position;
	std::vector<cgp::vec3> cart_position;
	std::vector<cgp::vec3> straw_position;

	void display_trees();
	void display_mushroom();
	void display_billboard();


	// ****************************** //
	// Functions
	// ****************************** //

	void initialize();  // Standard initialization to be called before the animation loop
	void display();     // The frame display to be called within the animation loop
	void display_gui(); // The display of the GUI, also called within the animation loop


};





