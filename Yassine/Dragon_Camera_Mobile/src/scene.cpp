#include "scene.hpp"

/** This file contains the custom implementation associated the scene 
*  The (*) indicates elements that are specific to the use of the camera mode and that should be handled if you want to use this effect in another scene. */

using namespace cgp;


void scene_structure::make_dragon()
{
	mesh_drawable dragon;
	mesh_drawable r_wing_end;
	mesh_drawable r_wing_mid;
	mesh_drawable l_wing_end;
	mesh_drawable l_wing_mid;
	mesh_drawable body;
	mesh_drawable front_left_leg;
	mesh_drawable front_right_leg;
	mesh_drawable back_left_leg;
	mesh_drawable back_right_leg;
	mesh_drawable feets;
	mesh_drawable tail;
	mesh_drawable head;
	mesh_drawable cornes;
	mesh_drawable inner_head;
	mesh_drawable main_body;
	mesh_drawable voile_rwing;
	mesh_drawable voile_lwing;
	mesh_drawable body_rwing;
	mesh_drawable body_lwing;
	mesh_drawable pique_rwing;
	mesh_drawable pique_lwing;
	mesh_drawable piques_dos;
	mesh_drawable griffes_pied_avant_gauche;
	mesh_drawable griffes_pied_avant_droit;
	mesh_drawable griffes_pied_arriere_gauche;
	mesh_drawable griffes_pied_arriere_droit;
	mesh_drawable eyes;
	mesh_drawable neck_head;
	mesh_drawable neck_low;

	auto texture2 = opengl_load_texture_image("C:/Users/Yassine/Desktop/Projet INF443/Blender_Dragon/dragon_texture_2.jpg");
	auto texture = opengl_load_texture_image("C:/Users/Yassine/Desktop/Projet INF443/Blender_Dragon/dragon_texture.png");
	neck_head.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/Projet INF443/Blender_Dragon/neck_dragon_head.obj"), "Neck Head");
	neck_low.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/Projet INF443/Blender_Dragon/neck_dragon_low.obj"), "Neck Low");
	cornes.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/Projet INF443/Blender_Dragon/Cornes_Dragon.obj"), "Cornes");
	cornes.texture = texture;
	front_right_leg.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/Projet INF443/Blender_Dragon/jambe_avant_droite.obj"), "Front Right Leg");
	front_left_leg.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/Projet INF443/Blender_Dragon/jambe_avant_gauche.obj"), "Front Left Leg");
	back_left_leg.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/Projet INF443/Blender_Dragon/jambe_gauche_arriere.obj"), "Back Left Leg");
	back_right_leg.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/Projet INF443/Blender_Dragon/jambe_droite_arriere.obj"), "Back Right Leg");
	tail.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/Projet INF443/Blender_Dragon/dragon_tail.obj"), "Dragon Tail");
	inner_head.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/Projet INF443/Blender_Dragon/Inner_head_dragon.obj"), "Inner Head");
	inner_head.shading.color = vec3(1, 1, 1);
	main_body.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/Projet INF443/Blender_Dragon/dragon_body_nothing_only.obj"), "Main Body");
	main_body.texture = texture;
	tail.texture = texture;
	voile_rwing.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/Projet INF443/Blender_Dragon/Voile_RWing.obj"), "Voile RWing");
	voile_lwing.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/Projet INF443/Blender_Dragon/Voile_LWing.obj"), "Voile LWing");
	voile_rwing.texture = texture;
	voile_lwing.texture = texture2;
	body_rwing.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/Projet INF443/Blender_Dragon/Body_RWing_centered.obj"), "Body RWing");
	body_lwing.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/Projet INF443/Blender_Dragon/Body_LWing_centered.obj"), "Body LWing");
	body_rwing.texture = texture;
	body_lwing.texture = texture;
	pique_rwing.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/Projet INF443/Blender_Dragon/Pique_RWing.obj"), "Pique RWing");
	pique_lwing.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/Projet INF443/Blender_Dragon/Pique_LWing.obj"), "Pique LWing");
	//piques_dos.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/Projet INF443/Blender_Dragon/"), "Pique Dos");
	griffes_pied_avant_gauche.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/Projet INF443/Blender_Dragon/griffes_pied_avant_gauche.obj"), "griffes_pag");
	griffes_pied_avant_droit.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/Projet INF443/Blender_Dragon/griffes_pied_avant_droit.obj"), "griffes_pad");
	griffes_pied_arriere_gauche.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/Projet INF443/Blender_Dragon/griffes_pied_arriere_gauche.obj"), "griffes_prg");
	griffes_pied_arriere_droit.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/Projet INF443/Blender_Dragon/griffes_pied_arriere_droit.obj"), "griffes_prd");
	eyes.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/Projet INF443/Blender_Dragon/Eyes_dragon.obj"), "eyes");
	eyes.shading.color = vec3(1, 0, 1);
	eyes.transform.scaling = 10000;

	//front_left_leg.texture = texture;
	front_right_leg.texture = texture;
	front_left_leg.texture = texture;
	back_right_leg.texture = texture;
	back_left_leg.texture = texture;
	neck_low.texture = texture;
	neck_head.texture = texture;

	vec3 rwing_translation = vec3(-.7, 3.3, 2.5);
	vec3 lwing_translation = vec3(.3, 3.4, 2.5);
	vec3 f_left_leg_trans = vec3(-0.2, -2.8, -2);
	vec3 f_right_leg_trans = vec3(0.7, -3, -2.5);
	vec3 b_right_leg_trans = vec3(0.3, -3.1, -0.3);
	vec3 b_left_leg_trans = vec3(-0.3, -3.5, 0);
	vec3 neck_low_trans = vec3(0, -2.5, -3.3);
	vec3 neck_head_trans = vec3(0, -4.7, -3.6);

	front_left_leg.transform.translation = f_left_leg_trans;
	griffes_pied_avant_gauche.transform.translation = f_left_leg_trans;
	front_right_leg.transform.translation = f_right_leg_trans;
	griffes_pied_avant_droit.transform.translation = f_right_leg_trans;
	back_right_leg.transform.translation = b_right_leg_trans;
	griffes_pied_arriere_droit.transform.translation = b_right_leg_trans;
	back_left_leg.transform.translation = b_left_leg_trans;
	griffes_pied_arriere_gauche.transform.translation = b_left_leg_trans;
	neck_low.transform.translation = neck_low_trans;
	neck_head.transform.translation = neck_head_trans;

	hierarchy.add(main_body);
	hierarchy.add(neck_low, "Main Body", -neck_low_trans);
	hierarchy.add(neck_head, "Neck Low", neck_low_trans-neck_head_trans);
	hierarchy.add(front_right_leg, "Main Body", -f_right_leg_trans);
	hierarchy.add(front_left_leg, "Main Body", -f_left_leg_trans);
	hierarchy.add(back_left_leg, "Main Body", -b_left_leg_trans);
	hierarchy.add(back_right_leg, "Main Body", -b_right_leg_trans);
	hierarchy.add(eyes, "Neck Head", neck_head_trans);
	hierarchy.add(cornes, "Neck Head", neck_head_trans);
	hierarchy.add(inner_head, "Neck Head", neck_head_trans);
	hierarchy.add(body_rwing, "Main Body", rwing_translation); // the translation is used to place the cube at the extremity of the cylinder
	hierarchy.add(body_lwing, "Main Body", lwing_translation);//, {1.0f, 0, 0});
	hierarchy.add(griffes_pied_avant_gauche, "Front Left Leg");
	hierarchy.add(griffes_pied_avant_droit, "Front Right Leg");
	hierarchy.add(griffes_pied_arriere_gauche, "Back Left Leg");
	hierarchy.add(griffes_pied_arriere_droit, "Back Right Leg");
	hierarchy.add(voile_lwing, "Body LWing", -lwing_translation);
	hierarchy.add(voile_rwing, "Body RWing", -rwing_translation);
	hierarchy.add(pique_rwing, "Body RWing", -rwing_translation);
	hierarchy.add(pique_lwing, "Body LWing", -lwing_translation);
	hierarchy.add(tail, "Main Body", { 0,0,0.02 });
	
	
	hierarchy["Main Body"].transform.scaling = 0.5;
	//hierarchy["Main Body"].transform.translation = vec3(5,0,0);
	hierarchy.update_local_to_global_coordinates();
		//.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, 3.14 / 2);
	//hierarchy.update_local_to_global_coordinates();
	//hierarchy.add(l_wing_mid, "LeftWingEnd");
	//hierarchy.add(l_wing_mid, "Left Wing End");
}
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
	// Default frame
	global_frame.initialize(mesh_primitive_frame(), "Frame");
	skybox.initialize("assets/skybox/");

	// Load the terrain (display a debug message as the loading can take some time)
	std::cout << " \nLoad terrain file ..." << std::endl;
	terrain.initialize(mesh_load_file_obj("assets/mountain.obj"), "Terrain");
	std::cout << " [OK] Terrain loaded\n" << std::endl;

	// Load the texture of the terrain
	std::cout << " \nLoad terrain texture ..." << std::endl;
	terrain.texture = opengl_load_texture_image("assets/mountain.jpg");
	std::cout << " [OK] Texture loaded\n" << std::endl;
	
	make_dragon();
	// Initial placement of the camera
	environment.camera.position_camera = { 1.f, 0.f, 1.0f };
	environment.camera.manipulator_rotate_roll_pitch_yaw(0, 0,0);
}



void scene_structure::display()
{	
	// set the light position to the camera
	environment.light = environment.camera.position(); 

	// The standard frame
	if (gui.display_frame)
		draw(global_frame, environment);
	timer2.update();
	double vitesse_ailes = 3. * timer2.t;
	hierarchy["Neck Low"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, 1-(std::sin(vitesse_ailes) * std::sin(vitesse_ailes) - 0.5) * 0.5);
	hierarchy["Body LWing"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, (std::sin(vitesse_ailes) * std::sin(vitesse_ailes) - 0.5) * 0.5);
	hierarchy["Body RWing"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, -(std::sin(vitesse_ailes) * std::sin(vitesse_ailes) - 0.5) * 0.5);
	hierarchy["Dragon Tail"].transform.rotation = rotation_transform::from_axis_angle({ 1,0.3,0 }, -(std::sin(vitesse_ailes) * std::sin(vitesse_ailes) - 0.5) * 0.1);
	hierarchy["Front Left Leg"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, -(std::sin(vitesse_ailes) * std::sin(vitesse_ailes) - 0.5) * 0.5);
	hierarchy["Front Right Leg"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, -(std::sin(vitesse_ailes) * std::sin(vitesse_ailes) - 0.5) * 0.5);
	hierarchy["Back Left Leg"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, -(std::sin(vitesse_ailes) * std::sin(vitesse_ailes) - 0.5) * 0.5);
	hierarchy["Back Right Leg"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, -(std::sin(vitesse_ailes) * std::sin(vitesse_ailes) - 0.5) * 0.5);
	hierarchy["Neck Head"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, -1-(std::sin(vitesse_ailes)  * std::sin(vitesse_ailes) - 0.5) * 0.5);

	double rayon_cercle = 5.;
	//hierarchy["Main Body"].transform.translation = vec3(rayon_cercle * std::cos(timer2.t), 0, rayon_cercle * std::sin(timer2.t));
	//hierarchy["Main Body"].transform.rotation = rotation_transform::from_axis_angle({ 0,-1,0 }, timer2.t);
	hierarchy.update_local_to_global_coordinates();
	// Displaying the shape deformed by the shader
	//draw(skybox, environment);
	draw(hierarchy, environment);
	//draw(terrain, environment);
}



void scene_structure::display_gui()
{
	ImGui::Checkbox("Frame", &gui.display_frame);
	ImGui::SliderFloat("Speed", &gui.speed, 1.f, 50.f); // Set the camera velocity
	ImGui::SliderFloat("Sensibility", &gui.sensibility, 1.f, 50.f);
}


