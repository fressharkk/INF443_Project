#include "scene.hpp"

#include "terrain.hpp"

#include "road.hpp"

#include "cart.hpp"

#include "straw.hpp"

using namespace cgp;


void scene_structure::initialize()
{
	// Basic set-up
	// ***************************************** //

	skybox.initialize("assets/skybox/"); 
	skybox.transform.rotation = rotation_transform::from_axis_angle({ 1.0f ,0.0f, 0.0f}, 2.1f) ;

	global_frame.initialize(mesh_primitive_frame(), "Frame");
	environment.camera.axis = camera_spherical_coordinates_axis::z;
	environment.camera.look_at({ 15.0f,6.0f,6.0f }, { 0,0,0 });

	// Initialize the terrain
	int N_terrain_samples = 300;
	float terrain_length = 50;
	mesh const terrain_mesh = create_terrain_mesh(N_terrain_samples, terrain_length);
	terrain.initialize(terrain_mesh, "terrain");
	terrain.shading.phong.specular = 0.0f; // non-specular terrain material
	terrain.texture = opengl_load_texture_image("assets/texture-herbe.jpg", GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT);

	mesh const road_mesh = create_road_mesh(terrain_length);
	road.initialize(road_mesh, "road");
	road.shading.phong = {  0.3f,0.5f,0.2f }; // non-specular terrain material
	road.texture = opengl_load_texture_image("assets/road2.jpg", GL_CLAMP_TO_EDGE, GL_MIRRORED_REPEAT);

	// Update the current time
	timer.update();
	
	// mesh_load_file_obj: lit un fichier .obj et renvoie une structure mesh lui correspondant
	mesh cart_mesh = create_cart_mesh(terrain_length);
	cart.initialize(cart_mesh, "cart");
	cart.transform.scaling = 0.0005f;
	cart.transform.rotation = rotation_transform::from_axis_angle({ 1.0f ,1.0f, 1.0f}, 2.1f) ;
	cart.transform.translation = { -5.5f,0 , evaluate_terrain_height(-5.5f,0)+0.01f};
	cart_position = generate_positions_on_road(100, terrain_length);
	cart.texture = opengl_load_texture_image("assets/bois.jpg", GL_CLAMP_TO_EDGE, GL_MIRRORED_REPEAT);

	mesh straw_mesh = create_straw_mesh();
	straw.initialize(straw_mesh, "straw");
	straw.texture = opengl_load_texture_image("assets/straw.jpg", GL_CLAMP_TO_EDGE, GL_MIRRORED_REPEAT);

	
	// Initialize the grass of billboards
	billboard.initialize(mesh_primitive_quadrangle({ -0.5f,0,0 }, { 0.5f,0,0 }, { 0.5f,0,1 }, { -0.5f,0,1 }), "Quad");
	billboard.texture = opengl_load_texture_image("assets/tumbleweed.png");
	billboard.shading.phong = {  0.5f,0.1f,0.5f };
	billboard.transform.scaling = 0.6f;
	billboard_position = generate_positions_on_terrain(75, terrain_length);
}





void scene_structure::display()
{
	
	
	draw(skybox, environment); 

	// Basic elements of the scene
	environment.light = environment.camera.position();
	if (gui.display_frame)
		draw(global_frame, environment);

	// Display the other elements:

	if (gui.display_terrain) {
		draw(terrain, environment);
		if (gui.display_wireframe)
			draw_wireframe(terrain, environment);
	}

	if(gui.display_billboard) display_billboard();

	draw(road, environment);

	for (vec3 position : cart_position) {
		cart.transform.translation = position;
		float x= position[0];
		float y= position[1];
		float z= position[2]+0.112;

		vec3 position_2 = {x,y,z};
		straw.transform.translation = position_2;
		draw(cart, environment);
		draw(straw, environment);
	}

	

}




void scene_structure::display_billboard()
{
	// Find the rotation such that:
	//  the right-direction of the billboard is turned to match the right-direction of the camera => R*{1,0,0} = camera_right
	//  but the billboard remains oriented upward in the z direction => R*{0,0,1} = {0,0,1}
	vec3 camera_right = environment.camera.right();
	rotation_transform R = rotation_transform::between_vector({ 1,0,0 }, { 0,0,1 }, camera_right, { 0,0,1 });
	billboard.transform.rotation = R;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(false);

	vec3 const offset = { 0,0,0.02f };
	for (vec3 position : billboard_position) {
		billboard.transform.translation = position - offset;
		//draw(billboard, environment);
	}

	glDepthMask(true);
	glDisable(GL_BLEND);


	if (gui.display_wireframe) {
		for (vec3 position : billboard_position) {
			billboard.transform.translation = position - offset;
			//draw_wireframe(billboard, environment);
		}
	}
}




void scene_structure::display_gui()
{
	ImGui::Checkbox("Frame", &gui.display_frame);
	ImGui::Checkbox("Wireframe", &gui.display_wireframe);

	ImGui::Checkbox("terrain", &gui.display_terrain);
	ImGui::Checkbox("tree", &gui.display_tree);
	ImGui::Checkbox("mushroom", &gui.display_mushroom);
	ImGui::Checkbox("billboard", &gui.display_billboard);
}


