#include "scene.hpp"

#include "terrain.hpp"

#include "road.hpp"

#include "cart.hpp"

#include "straw.hpp"

#include "rock.hpp"

#include "lake.hpp"

using namespace cgp;


// The main function implementing the Flying Mode
void scene_structure::update_camera(int key)
{
	inputs_keyboard_parameters const& keyboard = inputs.keyboard;
	camera_head& camera = environment.camera;

	// The camera moves forward all the time
	//   We consider in this example a constant velocity, so the displacement is: velocity * dt * front-camera-vector
	float const dt = timer.update();
	vec3 const forward_displacement = gui.speed * 0.1f * dt * camera.front();

	vec3 orientation = camera.front();
	double speed_dep = 5*gui.speed * 0.1f * dt;

	// The camera rotates if we press on the arrow keys
	//  The rotation is only applied to the roll and pitch degrees of freedom.
	float const pitch = 0.5f; // speed of the pitch
	float const roll  = 0.7f; // speed of the roll
	if (keyboard.up || key == 87)
		camera.position_camera += speed_dep * orientation;

	if (keyboard.down || key == 83 )
		camera.position_camera -= speed_dep * orientation;
	if (keyboard.right || key == 68)
	{
		if (std::abs(orientation[0]) < 0.000001)
			orientation[0] = 0.000001;
		double ratio = orientation[2] / orientation[0];
		camera.position_camera += speed_dep * vec3(-ratio / std::sqrt(1 + ratio*ratio), 0, -1. / std::sqrt(1 + ratio*ratio));
	}
		
	if (keyboard.left || key == 65)
	{
		if (std::abs(orientation[0]) < 0.000001)
			orientation[0] = 0.000001;
		double ratio = orientation[2] / orientation[0];
		camera.position_camera -= speed_dep * vec3(-ratio / std::sqrt(1 + ratio * ratio), 0, -1. / std::sqrt(1 + ratio * ratio));
	}
	
	if (key == 90)
		camera.position_camera += speed_dep * vec3(0, 1, 0);
	if (key == 88)
		camera.position_camera -= speed_dep * vec3(0, 1, 0);
}

void scene_structure::mouse_camera(double mouse_pos_x, double mouse_pos_y, double new_x, double new_y)
{

	camera_head& camera = environment.camera;
	double x_dir = (double)mouse_pos_x - new_x;
	double y_dir = (double)mouse_pos_y - new_y;
	camera.manipulator_rotate_roll_pitch_yaw(0, gui.sensibility*y_dir/3000. , gui.sensibility*x_dir/1000.);


}

void scene_structure::mouse_camera2(vec2 prev, vec2 curr)
{
	camera_head& camera = environment.camera;
	camera.manipulator_rotate_roll_pitch_yaw(0, -gui.sensibility * (curr[1] - prev[1])/10., gui.sensibility * (curr[0] - prev[0])/2.);
}

void scene_structure::initialize()
{
	GLuint const shader_deformation = opengl_load_shader("shaders/deformation/vert.glsl", "shaders/deformation/frag.glsl");

	// Default frame
	global_frame.initialize(mesh_primitive_frame(), "Frame");
	skybox.initialize("assets/skybox/");
	//skybox.transform.rotation = rotation_transform::from_axis_angle({ 1.0f ,0.0f, 0.0f}, 2.1f) ;

	// Initialize the terrain
	int N_terrain_samples = 100;
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

	//std::vector<mesh> rocks;
	//for (int i =0, i<50, ++i){
	//}
	mesh rock_mesh = rock_with_texture(0.5f, {-4,0,0}, 8, 8);
	rock.initialize(rock_mesh, "rock");
	rock_position = generate_positions_on_terrain(57, terrain_length);
	rock.texture = opengl_load_texture_image("assets/rock_2.jpg", GL_CLAMP_TO_EDGE, GL_MIRRORED_REPEAT);

	mesh lake_mesh = create_lake_mesh(100, terrain_length);
	lake.initialize(lake_mesh, "lake");
	lake.shader = shader_deformation;
	lake.texture = opengl_load_texture_image("assets/water.jpg", GL_CLAMP_TO_EDGE, GL_MIRRORED_REPEAT);

	
	// Initialize the grass of billboards
	billboard.initialize(mesh_primitive_quadrangle({ -0.5f,0,0 }, { 0.5f,0,0 }, { 0.5f,0,1 }, { -0.5f,0,1 }), "Quad");
	billboard.texture = opengl_load_texture_image("assets/tumbleweed.png");
	billboard.shading.phong = {  0.5f,0.1f,0.5f };
	billboard.transform.scaling = 0.6f;
	billboard_position = generate_positions_on_terrain(75, terrain_length);

	// Initial placement of the camera
	environment.camera.position_camera = { 1.f, 0.f, 10.0f };
	environment.camera.manipulator_rotate_roll_pitch_yaw(1, 0,0);
}



void scene_structure::display()
{	
	// set the light position to the camera
	environment.light = environment.camera.position(); 

	// The standard frame
	if (gui.display_frame)
		draw(global_frame, environment);
	timer2.update();
	float t = timer2.t;

	
	// Displaying the shape deformed by the shader
	draw(skybox, environment);
	draw(terrain, environment);
	draw(road, environment);
	environment.update(t);  
	draw(lake, environment);

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

	for (vec3 position : rock_position) {
		float x= position[0];
		float y= position[1];
		float z= position[2]-0.6;
		z = evaluate_terrain_height (x,y);
		vec3 position_2 = {x,y,z};
		rock.transform.translation = position_2;
		float a = rand_interval(0,3)/3;
		//rock.transform.scaling = a;
		draw(rock, environment);
	}

}



void scene_structure::display_gui()
{
	ImGui::Checkbox("Frame", &gui.display_frame);
	ImGui::SliderFloat("Speed", &gui.speed, 1.f, 50.f); // Set the camera velocity
	ImGui::SliderFloat("Sensibility", &gui.sensibility, 1.f, 50.f);

	ImGui::Checkbox("terrain", &gui.display_terrain);
	ImGui::Checkbox("tree", &gui.display_tree);
	ImGui::Checkbox("mushroom", &gui.display_mushroom);
	ImGui::Checkbox("billboard", &gui.display_billboard);
}


