#pragma once

/** This file contains the custom function signature and structure associated the scene 
*  The (*) indicates elements that are specific to the use of the camera mode  */

#include "cgp/cgp.hpp"
#include "mySkybox/mySkybox.hpp"
#include "collisions/flame_collisions.hpp"
//#include "particles/particle_Emitter.hpp"

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
	bool start_scene = false;
	bool not_initialized = true;
	float gravEffect = -0.1;
	float scale = 3;
	float pps = 7;
	float speed2 = 1;
	float LifeLength = 3;
};

// The structure of the custom scene
struct scene_structure {
	
	///Terrain Height And Normal functions
	ParticleEmitter* fire_particules;
	ParticleEmitter* smoke_particules;
	float (*height_func)(float, float) = myTerrain::getHeight;
	cgp::vec3 (*normal_func)(float, float) = myTerrain::get_normal;


	void delete_init();

	/// INITIALIZE FUNCTIONS
	void main_initalize();
	void initialize_test();
	void initialize_skybox();
	void initialize_flames();
	void initialize_terrain_and_non_transparent_decoration();
	void initialize_dragon();
	void initialize_chevaliers();
	void init_chevaliers();
	void initialize_soldiers();
	void init_soldiers();
	void initialize_water();
	void initialize_cameras();
	void initialize_particule_generator();
	void initialize_billboards();
	void initialize_collisions();

	/// DISPLAY FUNCTIONS
	void display_my_skybox();
	void display_terrain_and_non_transparent_decoration();
	void update_and_display_soldiers();
	void update_and_display_chevaliers();
	void update_and_display_dragon();
	void update_and_display_particules();
	void update_and_display_flames();
	void to_render_reflection_FBO();
	void to_render_refraction_FBO();
	void main_display_loop();
	void checkCollisionsObjetsFixes();

	int nb_soldats = 5;
	int nb_chevaliers = 5;
	hierarchy_mesh_drawable low_tree;
	BillBoards* weeds;
	BillBoards* cactus;
	Rocks* rocks_1;
	Rocks* rocks_2;
	Rocks* rocks_3;
	Carts* carts;
	gridCut* gridCutCollisions;

	// ****************************** //
	// Elements and shapes of the scene
	// ****************************** //
	Dragon dragon = Dragon();
	myTerrain ter;
	mySkybox skyboxX;
	Water *water; 
	std::vector<Soldat*> soldats;
	std::vector<Chevalier*> chevaliers;
	Flamme *flamme1;
	Feu* fire;

	scene_environment_camera_head environment; // The specific scene environment that contains a "head camera" (*)
	//scene_environment_with_shader_deformation environment; // The specific scene environment associated to the deforming shader (*)
	
	cgp::mesh_drawable global_frame;    // The standard global frame
	cgp::mesh_drawable terrain;         // The terrain loaded from an external file

	cgp::timer_basic timer; // A basic timer for the camera animation
	cgp::timer_basic timer2;
	cgp::skybox_drawable skybox;
	cgp::skybox_drawable skybox2;

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

	std::vector<cgp::vec3> tree_position;
	std::vector<cgp::vec3> mushroom_position;
	std::vector<cgp::vec3> billboard_position;
	std::vector<cgp::vec3> cart_position;
	std::vector<cgp::vec3> straw_position;
	std::vector<cgp::vec3> rock_position;
	std::vector<cgp::vec3> rock_position_2;
	std::vector<cgp::vec3> rock_position_3;
	
	std::tuple<int, std::string> char_to_follow;

	void get_pointed_object(cgp::vec2 mouse_position, cgp::camera_base& camera);

	void init(); //FONCTION POUR INITIALISER LES PARAMETRES FACILES 

	// ****************************** //
	// Functions
	// ****************************** //
	
	// Function to call in the animation loop in main (*)
	//   This function replace the standard trackball behavior that must also be removed in the main (from mouse_move_callback)
	void update_camera(int key); 
	void mouse_camera(double mouse_pos_x, double mouse_pos_y, double new_x, double new_y);
	void mouse_camera2(cgp::vec2 prev, cgp::vec2 curr);
	fbo_screen_effect screen_effect;
	void follow_caracter_camera(bool is_enabled = false);
	void draw_remaining();
	void display_trees();
	void display_mushroom();
	void display_billboard();
	void display_test();
	void initialize();  // Standard initialization to be called before the animation loop
	void display();     // The frame display to be called within the animation loop
	void display_gui(); // The display of the GUI, also called within the animation loop

	void display_Water_FBO();
};





