#include "scene.hpp"



using namespace cgp;

mesh_drawable testing_mesh;
mesh_drawable testing_mesh_2;
mesh test;
vec3 ray;

bool is_in(cgp::vec3 pos, cgp::vec3 c, cgp::vec3 h)
{
	float eps = 0.001;
	return (bool) (c.x - h.x / 2 - eps <= pos.x)  && (pos.x <= eps + c.x + h.x / 2) && (c.y - h.y / 2 - eps <= pos.y) && (pos.y <= eps + c.y + h.y / 2) && (c.z - h.z / 2 - eps <= pos.z) && (pos.z <= eps + c.z + h.z / 2);
}

void scene_structure::display_my_skybox()
{
	skyboxX.updateSkybox(timer.t);
	skyboxX.setBlend(gui.pps / 10);
	environment.fogColor = vec3(0.8 + (0.3 - 0.8) * skyboxX.getBlend(), 0.8 + (0.3 - 0.8) * skyboxX.getBlend(), 0.8 + (0.3 - 0.8) * skyboxX.getBlend());
	skyboxX.setFogColour(environment.fogColor);
	skyboxX.draw_Skybox(environment);
}
void scene_structure::display_terrain_and_non_transparent_decoration()
{
	ter.draw_all_Terrains(environment);
	rocks_1->draw_rocks(environment);
	rocks_2->draw_rocks(environment);
	rocks_3->draw_rocks(environment);
	carts->draw_carts(environment);
}
void scene_structure::update_and_display_soldiers()
{
	for (auto s : soldats)
		s->draw_soldat(environment, height_func, normal_func);
}
void scene_structure::update_and_display_chevaliers()
{
	for (auto c : chevaliers)
		c->phase_1(timer.t);

	for (auto c : chevaliers)
		c->draw_chevalier(environment, height_func, normal_func);
}
void scene_structure::update_and_display_dragon()
{
	dragon.fly(timer.t,0.3,vec3(10, 10, 10),0.3);
	dragon.fly(timer.t, 3, vec3(60, 2, 60), 3);
	dragon.orienterBas(timer.t, 3, 13);
	
	dragon.throw_fire(timer.t, 1, 10, flamme1, environment);
	dragon.draw_dragon(environment);
}
void scene_structure::update_and_display_particules()
{
	fire_particules->generateParticles(vec3(0, 0, 0), timer.t);
	smoke_particules->generateParticles(vec3(0, 1, 0), timer.t);
	fire_particules->drawParticles(environment);
	smoke_particules->drawParticles(environment);
}
void scene_structure::update_and_display_flames()
{
	flamme1 = new Flamme(3., 15., 2, 1.);
}
void scene_structure::main_display_loop()
{
	if (!gui.start_scene)
		return;
	if (gui.not_initialized)
		init();

}
void scene_structure::checkCollisionsObjetsFixes()
{
	gridCutCollisions->detectCollisionFixe(environment.camera.position(), vec3(0.1, 0.1, 0.1));
}
void scene_structure::get_pointed_object(cgp::vec2 mouse_position, camera_base& camera)
{

	vec4 ray_nds = vec4(mouse_position.x, mouse_position.y, -1, 1);
	vec4 ray_eye = environment.projection.matrix_inverse() * ray_nds;
	ray_eye = vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);
	vec3 ray_wor = (inverse(camera.matrix_view()) * ray_eye).xyz();
	ray_wor = 1/norm(ray_wor) * ray_wor;
	ray = ray_wor;
	test = mesh_primitive_arrow(environment.camera.position(), environment.camera.position() + 100 * ray);
	double best_chev = 1.79769e+308;
	int best_chev_idx = -1;
	double best_drag = 1.79769e+308;
	int best_drag_idx = -1;
	double best_sold = 1.79769e+308;
	int best_sold_idx = -1;

	for (int idx = 0; idx < soldats.size(); idx++)
	{
		Soldat* sold = soldats[idx];
		vec3 center = sold->get_center();
		vec3 h_box = sold->get_hit_box();

		for (int i = 0; i < 3; i++)
		{
			vec4 dir_norm = vec4((i + 1) % 3 % 2, i % 3 % 2, (i + 2) % 3 % 2, 0);
			mat4 A = { dir_norm, {1,0,0,-ray_wor.x}, {0,1,0,-ray_wor.y}, {0,0,1, -ray_wor.z} };
			vec4 xyzt1 = inverse(A) * vec4(center[i] + h_box[i] / 2, camera.position());
			vec4 xyzt2 = inverse(A) * vec4(center[i] - h_box[i] / 2, camera.position());
			if (is_in(xyzt1.xyz(), center, h_box) && xyzt1.w >= 0 && xyzt1.w < best_sold)
			{
				best_sold = xyzt1.w;
				best_sold_idx = idx;
			}

			if (is_in(xyzt2.xyz(), center, h_box) && xyzt2.w >= 0 && xyzt2.w < best_sold)
			{
				best_sold = xyzt2.w;
				best_sold_idx = idx;
			}

		}

	}
	
	

	//Chevaliers
	for (int idx = 0; idx< chevaliers.size(); idx++)
	{
		Chevalier* chev = chevaliers[idx];
		vec3 center = chev->get_center();
		vec3 h_box = chev->get_hit_box();
		for (int i = 0; i < 3; i++)
		{
			vec4 dir_norm = vec4((i+1) % 3 % 2, i % 3 % 2, (i + 2) % 3 % 2, 0);
			mat4 A = { dir_norm, {1,0,0,-ray_wor.x}, {0,1,0,-ray_wor.y}, {0,0,1, -ray_wor.z} };
			

			vec4 xyzt1 = inverse(A) * vec4(center[i] + h_box[i] / 2, camera.position());
			vec4 xyzt2 = inverse(A) * vec4(center[i] - h_box[i] / 2, camera.position());
			

			if (is_in(xyzt1.xyz(), center, h_box) && xyzt1.w >= 0 && xyzt1.w < best_chev)
			{
				best_chev = xyzt1.w;
				best_chev_idx = idx;
				
				
			}

			if (is_in(xyzt2.xyz(), center, h_box) && xyzt2.w >= 0 && xyzt2.w < best_chev)
			{
				best_chev = xyzt2.w;
				best_chev_idx = idx;

				
			}

		}
		
	}

	

	//Dragon
	int idx = 0;
	for (int i = 0; i < 3; i++)
	{
		vec3 center = dragon.get_current_position();
		vec3 h_box_1 = dragon.hit_box_1;
		vec3 h_box_2 = dragon.hit_box_2;
		rotation_transform rota = dragon.get_rotation() * rotation_transform::between_vector({1,0,0}, {0,0,1});
		
		
		vec4 dir_norm = rota*vec4((i + 1) % 3 % 2, i % 3 % 2, (i + 2) % 3 % 2, 0);
		h_box_1 = abs(rota * h_box_1);
		h_box_2 = abs(rota * h_box_2);

		mat4 A = { dir_norm, {1,0,0,-ray_wor.x}, {0,1,0,-ray_wor.y}, {0,0,1, -ray_wor.z} };
		vec4 xyzt1 = inverse(A) * vec4(center[i] + h_box_1[i] / 2, camera.position());
		vec4 xyzt2 = inverse(A) * vec4(center[i] -  h_box_1[i] / 2, camera.position());
		vec4 xyzt3 = inverse(A) * vec4(center[i] + h_box_2[i]/2, camera.position());
		vec4 xyzt4 = inverse(A) * vec4(center[i] - h_box_2[i] / 2, camera.position());
		if (is_in(xyzt1.xyz(), center, h_box_1) && xyzt1.w >= 0 && xyzt1.w < best_drag)
		{
			best_drag = xyzt1.w;
			best_drag_idx = idx;
		}

		if (is_in(xyzt1.xyz(), center, h_box_1) && xyzt2.w >= 0 && xyzt2.w < best_drag)
		{
			best_drag = xyzt2.w;
			best_drag_idx = idx;
		}
		if (is_in(xyzt3.xyz(), center, h_box_2) && xyzt3.w >= 0 && xyzt3.w < best_drag)
		{
			best_drag = xyzt3.w;
			best_drag_idx = idx;
		}
		if (is_in(xyzt4.xyz(), center, h_box_2) && xyzt4.w >= 0 && xyzt4.w < best_drag)
		{
			best_drag = xyzt4.w;
			best_drag_idx = idx;
		}
	}



	if (best_drag <= best_chev && best_drag <= best_sold)
	{
		char_to_follow = { best_drag_idx, "Drag" };
	}
	else if (best_sold <= best_chev && best_sold <= best_drag)
	{
		char_to_follow = { best_sold_idx, "Sold" };
	}
	else if (best_chev <= best_sold && best_chev <= best_drag)
	{
		char_to_follow = { best_chev_idx, "Chev" };
	}
	else
		char_to_follow = { -1, " " };


}

void scene_structure::init()
{
	//Paramètres modifiables 
	gui.not_initialized = false;
	init_chevaliers();
	init_soldiers();

	timer.start();

}

mesh_drawable hit_box;
Particle_Cloud* p;
ParticleEmitter * p_gen;

void scene_structure::update_camera(int key)
{
	inputs_keyboard_parameters const& keyboard = inputs.keyboard;
	float const dt = timer.update();

	if (environment.is_camera_head_used)
	{
		camera_head& camera = environment.camera;

		vec3 forward_displacement = gui.speed * 0.1f * dt * camera.front();

		vec3 orientation = environment.camera.front();
		double speed_dep = 50 * gui.speed * 0.1f * dt;


		float const pitch = 0.5f; // speed of the pitch
		float const roll = 0.7f; // speed of the roll

		if (key == GLFW_KEY_ESCAPE)
			char_to_follow = { -1, " " };

		if (keyboard.up || key == 87)
		{
			camera.position_camera += speed_dep * orientation;

		}
		if (keyboard.down || key == 83)
			camera.position_camera -= speed_dep * orientation;
		if (keyboard.right || key == 68)
		{
			if (std::abs(orientation[0]) < 0.000001)
				orientation[0] = 0.000001;
			//double ratio = orientation[2] / orientation[0];
			//camera.position_camera += speed_dep * vec3(-ratio / std::sqrt(1 + ratio*ratio), 0, -1. / std::sqrt(1 + ratio*ratio));
			camera.position_camera += speed_dep * camera.right();
		}

		if (keyboard.left || key == 65)
		{
			if (std::abs(orientation[0]) < 0.000001)
				orientation[0] = 0.000001;
			double ratio = orientation[2] / orientation[0];
			//camera.position_camera -= speed_dep * vec3(-ratio / std::sqrt(1 + ratio * ratio), 0, -1. / std::sqrt(1 + ratio * ratio));
			camera.position_camera -= speed_dep * camera.right();
		}

		if (key == 90)
			camera.position_camera += speed_dep * vec3(0, 1, 0);
		if (key == 88)
			camera.position_camera -= speed_dep * vec3(0, 1, 0);
	}
	else
	{
		//camera_spherical_coordinates& camera = environment.camera_fixe;

		//vec3 forward_displacement = gui.speed * 0.1f * dt * camera.front();

		//vec3 orientation = environment.camera.front();
		//double speed_dep = 50 * gui.speed * 0.1f * dt;


		//float const pitch = 0.5f; // speed of the pitch
		//float const roll = 0.7f; // speed of the roll

		//if (key == GLFW_KEY_ESCAPE)
		//	char_to_follow = { -1, " " };

		//if (keyboard.up || key == 87)
		//{
		//	camera. += speed_dep * orientation;

		//}
		//if (keyboard.down || key == 83)
		//	camera.position_camera -= speed_dep * orientation;
		//if (keyboard.right || key == 68)
		//{
		//	if (std::abs(orientation[0]) < 0.000001)
		//		orientation[0] = 0.000001;
		//	//double ratio = orientation[2] / orientation[0];
		//	//camera.position_camera += speed_dep * vec3(-ratio / std::sqrt(1 + ratio*ratio), 0, -1. / std::sqrt(1 + ratio*ratio));
		//	camera.position_camera += speed_dep * camera.right();
		//}

		//if (keyboard.left || key == 65)
		//{
		//	if (std::abs(orientation[0]) < 0.000001)
		//		orientation[0] = 0.000001;
		//	double ratio = orientation[2] / orientation[0];
		//	//camera.position_camera -= speed_dep * vec3(-ratio / std::sqrt(1 + ratio * ratio), 0, -1. / std::sqrt(1 + ratio * ratio));
		//	camera.position_camera -= speed_dep * camera.right();
		//}

		//if (key == 90)
		//	camera.position_camera += speed_dep * vec3(0, 1, 0);
		//if (key == 88)
		//	camera.position_camera -= speed_dep * vec3(0, 1, 0)
	}
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
	mesh_drawable::default_shader = opengl_load_shader("shaders/mesh_2/vert.glsl", "shaders/mesh_2/frag.glsl");
	low_tree = build_tree();
	
	GLuint const shader_deformation = opengl_load_shader("shaders/deformation/vert.glsl", "shaders/deformation/frag.glsl");
	

	// Default frame
	global_frame.initialize(mesh_primitive_frame(), "Frame");

	
	
	// Update the current time
	timer.update();
	
	
	// Initial placement of the camera

	skyboxX.setBlend(0.5);

	//testing_mesh.initialize(mesh_primitive_quadrangle(), "Testing Mesh");
	//testing_mesh.texture = water->getReflectionTexture();
	//testing_mesh_2.initialize(mesh_primitive_quadrangle({-1,-1,0}, {0,-1,0}, {0,0,0}, {-1,0,0}), "Testing Mesh");
	//testing_mesh_2.texture = water->getRefractionTexture();
	////terrain.texture = water->getRefractionTexture();
	//GLuint shader_screen_effect = opengl_load_shader("shaders/screen_effect_convolution/vert.glsl", "shaders/screen_effect_convolution/frag.glsl");
	////GLuint shader_screen_effect = opengl_load_shader("shaders/mesh_2/vert.glsl", "shaders/mesh_2/frag.glsl");
	//screen_effect.initialize(shader_screen_effect, inputs.window.width, inputs.window.height);
	//testing_mesh.shader = shader_screen_effect;
	//testing_mesh_2.shader = shader_screen_effect;
	timer2.start();
}

void scene_structure::follow_caracter_camera(bool is_enabled)
{
	if (!is_enabled)
		return;

	int idx = std::get<0>(char_to_follow);

	if (idx == -1)
		return;
	
	//Ajouter tout ce qui est switch de caméra
	if (std::get<1>(char_to_follow) == "Chev")
	{
		environment.camera.position_camera = chevaliers[idx]->get_vision_pos();
		environment.camera.orientation_camera = rotation_transform::between_vector({ 0,0,-1 }, { 1,0,0 }) * chevaliers[idx]->get_vision_orientation()* rotation_transform::from_axis_angle({ 1,0,0 }, -0.2);
	}
	if (std::get<1>(char_to_follow) == "Drag")
	{
		rotation_transform rot = dragon.get_eyes_rotation() * rotation_transform::from_axis_angle({ 0,1,0 }, Pi);
		environment.camera.position_camera = dragon.get_mouth_position() + rot*vec3(0,0.2,0);
	 	environment.camera.orientation_camera = rot * rotation_transform::from_axis_angle({ 1,0,0 }, -0.25);
	}
	if (std::get<1>(char_to_follow) == "Sold")
	{
		rotation_transform rot = soldats[idx]->get_vision_orientation();
		environment.camera.position_camera = soldats[idx]->get_vision_pos();
		environment.camera.orientation_camera = rot;
	}

}

void scene_structure::draw_remaining()
{

	for (vec3 position : cart_position) {
		cart.transform.translation = position;
		float x = position[0];
		float y = position[1];
		float z = position[2] + 0.112;

		vec3 position_2 = { x,y,z };
		straw.transform.translation = position_2;
		draw(cart, environment);
		draw(straw, environment);
	}

	global_frame.initialize(mesh_primitive_frame());
}

void scene_structure::display_test()
{
	if (!gui.start_scene && !gui.not_initialized)
		delete_init();
	if (!gui.start_scene)
		return;
	if (gui.not_initialized)
		init();
	
	if (gui.display_billboard)
		timer.t = 0;

	timer.update();
	environment.update(timer.t);
	environment.light = environment.camera.position();
	display_my_skybox();
	display_terrain_and_non_transparent_decoration();
	update_and_display_soldiers();
	update_and_display_chevaliers();
	update_and_display_dragon();
	checkCollisionsObjetsFixes();
	update_and_display_particules();
	if (flamme1->is_active)
		checkFlameCollisionGround(flamme1, ter, timer.t);
}

void scene_structure::display()
{	
	//vec3 g;
	//float f;
	//if (!gui.start_scene)
	//	return;
	//if (gui.not_initialized)
	//	init();
	//if (gui.display_billboard)
	//{
	//	timer2.stop();
	//	timer2.t = 0;
	//	timer2.start();
	//} 
	//
	//
	//follow_caracter_camera(environment.is_camera_head_used);

	//timer2.update();
	//p_gen->setLifeLength(gui.LifeLength);
	//p_gen->setPps(gui.pps);
	//p_gen->setScale(gui.scale);
	//p_gen->setSpeed(gui.speed2);
	//p_gen->setGravEffect(gui.gravEffect);
	//p_gen->generateParticles(vec3(0, 0, 0), timer2.t);
	//soldats[0]->draw_soldat(environment);
	//p_gen->drawParticles(environment);
	//flamme1->draw_flamme(environment);
	//draw(terrain, environment);
	//ter.draw_all_Terrains(environment);
	//soldats[0]->draw_soldat(environment);
	//water->draw_Water(environment);
	//soldats[0]->right_leg_up(timer2.t, 1, 3);
	//Soldat::soldat_mesh->soldat_to_draw["Torse"].transform.rotation = rotation_transform::from_axis_angle({1,0,0}, Pi / 2);
	/*rotation_transform::convert_quaternion_to_axis_angle(soldats[0]->get_rotation().data, g, f);
	std::cout << f << std::endl;
	std::cout << g << std::endl;*/
//	soldats[0]->walk(timer2.t, 0, 10, 0.1, 2);
	//soldats[0]->test_mvt(timer2.t,0,2);
	//soldats[0]->left_slash(timer2.t, 1, 1);
	//soldats[0]->run_to(vec3(10,5,10), timer2.t, 2);
	//chevaliers[0]->trot(vec3(0, 0, 0), timer2.t, 1, 100);
	//chevaliers[0]->draw_chevalier(environment);
	
	//p_gen->draw_c->draw_p->myDraw(p_gen->draw_c->particles, terrain, environment);
	//for (int i = 0; i < soldats.size(); i++)
	//	soldats[i]->draw_soldat(environment);
	//for (int i = 0; i < chevaliers.size(); i++)
	//	chevaliers[i]->draw_chevalier(environment);
	
	
	// set the light position to the camera
	// The standard frame

	////glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	////glEnable(GL_BLEND);
	//dragon.fly(timer2.t, 1, vec3(20, 40, 10), 20);
	//dragon.fly(timer2.t, 22, vec3(0, 5, 0), 10);
	//dragon.throw_fire(timer2.t, 22, 3, flamme1, environment);
	//// Displaying the shape deformed by the shader

	//cgp::draw(terrain, environment);
	//cgp::draw(road, environment);
	//
	//draw(lake, environment);
	
	/*for (vec3 position : rock_position) {
		float x = position[0];
		float z = position[1];
		float y = position[2];
		z = evaluate_terrain_height(x, y);
		vec3 position_1 = { x,z,y };
		rock1.transform.translation = position_1;
		draw(rock1, environment);
	}

	for (vec3 position : rock_position_2) {
		float x = position[0];
		float z = position[1];
		float y = position[2] - 0.6;
		z = evaluate_terrain_height(x, y);
		z = z - 0.4f;
		vec3 position_2 = {x,z,y};
		rock2.transform.translation = position_2;
		draw(rock2, environment);
	}

	for (vec3 position : rock_position_3) {
		float x = position[0];
		float z = position[1];
		float y = position[2] - 0.6f;
		z = evaluate_terrain_height(x, y);
		vec3 position_3 = { x,z,y };
		rock3.transform.translation = position_3;
		draw(rock3, environment);
	}*/

	//cart
	/*for (vec3 position : cart_position) {
		cart.transform.translation = position;
		float x = position[0];
		float z = position[1] + 0.112;
		float y = position[2];

		vec3 position_2 = { x,z,y };
		straw.transform.translation = position_2;
		draw(cart, environment);
		draw(straw, environment);
	}*/


	//draw_remaining();
	////fire->draw_feu(environment);
	//dragon.dragon_hierarchy.update_local_to_global_coordinates();
	//draw(global_frame, environment);
	////cgp::draw(testing_mesh, environment);
	////dragon.open_mouth(timer2.t, 0, 1);
	////dragon.fly_(timer2.t, 1, vec3(0, 5, 10), 5);
	////dragon.fly_left_wing(timer2.t, 1, 4, 30);
	////dragon.fly_right_wing(timer2.t, 1, 4, 30);
	////dragon.stretching_back_legs(timer2.t, 1, 1);
	////dragon.stretching_front_legs(timer2.t, 1, 1, 1);
	////dragon.draw_dragon(environment);
	//
	////dragon.throw_fire(timer2.t, 3, 10, flamme1, environment);
	//dragon.draw_dragon(environment);
	////fire->draw_feu(environment);
	//
	////vec3 pos = dragon.dragon_hierarchy["Main Body"].transform.translation +dragon.dragon_hierarchy["Neck Low"].transform.translation;
	//vec3 pos = dragon.dragon_hierarchy["Neck Head"].global_transform.translation;
	////flamme1->draw_flamme(environment,dragon.get_mouth_position(), dragon.get_mouth_orientation());
	//for (auto chev : chevaliers)
	//	chev->draw_chevalier(environment);



}

void scene_structure::display_gui()
{

	ImGui::Checkbox("Frame", &gui.display_frame);
	ImGui::SliderFloat("Speed", &gui.speed, 1.f, 50.f); // Set the camera velocity
	ImGui::SliderFloat("Sensibility", &gui.sensibility, 1.f, 50.f);
	ImGui::Checkbox("Use Head Camera", &environment.is_camera_head_used);
	ImGui::SliderInt("Number of Chevaliers", &nb_chevaliers, 1, 50);
	ImGui::SliderInt("Number of Soldiers", &nb_soldats, 1, 50);
	ImGui::Checkbox("Start the Scene ?", &gui.start_scene);
	auto l = ImGui::Button("Test", { 10,10 });
	ImGui::SliderFloat("Gravity Effect", &gui.gravEffect, 0,2*Pi);
	ImGui::SliderFloat("Scale ", &gui.scale, 0, 2*Pi);
	ImGui::SliderFloat("LifeLength", &gui.LifeLength, 0, 2*Pi);
	ImGui::SliderFloat("PPS", &gui.pps, 0, 10);
	ImGui::SliderFloat("Speed", &gui.speed2, 0, 0.1);
	ImGui::Checkbox("Reset Time", &gui.display_billboard);
}

void scene_structure::display_Water_FBO()
{
	// Update the texture size of the FBO if needed
	if (inputs.window.is_resized)
		water->updateWindowSize(inputs.window.width, inputs.window.height);

	environment.update_water_camera();

	glEnable(GL_CLIP_DISTANCE0);

	water->bindReflectionFrameBuffer();
	//environment.use_water_camera = true;
	//environment.is_camera_head_used = false;
	environment.water_plane = vec4(0, 1, 0, 0.5);
	display();
	water->unbindCurrentFrameBuffer();
	environment.use_water_camera = false;
	//environment.is_camera_head_used = true;

	water->bindRefractionFrameBuffer();
	environment.water_plane = vec4(0, -1, 0, -0.5);
	display();
	water->unbindCurrentFrameBuffer();

	// Display the quad using the FBO texture, and use the shader applying the filter
	
	glDisable(GL_CLIP_DISTANCE0);
	display();

	cactus->draw_billboards(environment);
	draw(tree, environment);

	draw(global_frame, environment);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	water->draw_Water(environment,timer2.t);
}

void scene_structure::delete_init()
{
	std::cout << "DELETING CHEVALIERS : " << chevaliers.empty() << std::endl;
	std::cout << "DELETING SOLDATS : " << soldats.empty() << std::endl;

	gui.not_initialized = true;
}

void scene_structure::initialize_test()
{
	initialize_cameras();
	initialize_skybox();
	initialize_terrain_and_non_transparent_decoration();
	initialize_chevaliers();
	initialize_soldiers();
	initialize_flames();
	initialize_dragon();
	initialize_water();
	initialize_billboards();
	initialize_collisions();
	initialize_particule_generator();

}

void scene_structure::initialize_skybox()
{
	skyboxX.initialize();
}

void scene_structure::initialize_flames()
{
	flamme1 = new Flamme(3., 15., 2, 1.);
	fire = new Feu(vec3(0, 0, 0), 20, 7, environment.feu_attributes);
}

void scene_structure::initialize_terrain_and_non_transparent_decoration()
{
	float terrain_length = ter.getTerrainLength();
	vec4 bounds = vec4(-terrain_length / 2, terrain_length / 2, -terrain_length / 2, terrain_length / 2);
	ter.initialize();
	rocks_1 = new Rocks(1, 1, 0.3, { 0,0,0 }, bounds,height_func, normal_func);
	rocks_2 = new Rocks(2, 1, 1.f, { 0,0,0 }, bounds, height_func, normal_func);
	rocks_3 = new Rocks(3, 1, 0.5 , { 0,0,0 }, bounds, height_func, normal_func);
	carts = new Carts(1, 0.05, bounds, height_func, normal_func);
}

void scene_structure::initialize_dragon()
{

	dragon.make_dragon();
}

void scene_structure::initialize_chevaliers()
{
	Chevalier::initialize_mesh();
}

void scene_structure::init_chevaliers()
{
	float terrain_length = ter.getTerrainLength();
	float z_pos = -330;
	float percent = (float)nb_chevaliers / 50;
	float covered_distance = 200 * percent;

	for (int i = 0; i < nb_chevaliers; i++)
	{
		float x_coord = (float)-covered_distance + 2 * i * covered_distance / nb_chevaliers;
		vec3 pp = vec3(x_coord, 0, z_pos);
		chevaliers.push_back(new Chevalier(pp));
	}
}

void scene_structure::initialize_soldiers()
{
	Soldat::initialize_mesh();
}

void scene_structure::init_soldiers()
{
	float terrain_length = ter.getTerrainLength();
	float z_pos = 40;
	float percent = (float)nb_soldats / 50;
	float covered_distance = 200 * percent;

	for (int i = 0; i < nb_soldats; i++)
	{
		float x_coord = (float)-covered_distance + 2 * i * covered_distance / nb_soldats;
		vec3 pp = vec3(x_coord, 0, z_pos);
		soldats.push_back(new Soldat(pp));
	}
}

void scene_structure::initialize_water()
{
	environment.water_plane = vec4(0, -1, 0, -0.5);
	water = new Water(17, vec3(75, -0.25, 75));
}

void scene_structure::initialize_cameras()
{
	environment.camera.position_camera = { 75.f, 2.f, 75.0f };
	environment.camera_fixe.axis = camera_spherical_coordinates_axis::y;
	environment.camera_fixe.look_at({ 15.0f,6.0f,6.0f }, { 0,0,0 });
}

void scene_structure::initialize_particule_generator()
{
	ParticleTexture text_fire(opengl_load_texture_image("assets/Particles_Texture/fire.png"), 8);
	ParticleTexture text_smoke(opengl_load_texture_image("assets/Particles_Texture/smoke.png"), 8);
	
	fire_particules = new ParticleEmitter(text_fire, 5, 1, -0.1, 10.f, 10,0,false,true);
	fire_particules->randomizeRotation();
	fire_particules->setLifeError(0.1f);
	fire_particules->setSpeedError(0.1f);
	fire_particules->setScaleError(0.5f);

	smoke_particules = new ParticleEmitter(text_smoke, 5, 1, -0.1, 10.f, 3, 0, true, false);
	smoke_particules->randomizeRotation();
	smoke_particules->setLifeError(0.1f);
	smoke_particules->setSpeedError(0.1f);
	smoke_particules->setScaleError(0.5f);
}

void scene_structure::initialize_billboards()
{

	cactus = new BillBoards("assets/Terrain_Texture/cactus.png", 50, 2, -100, 100, -100, 100, &(myTerrain::getHeight), &(myTerrain::get_normal));

}

void scene_structure::initialize_collisions()
{
	gridCutCollisions = new gridCut();
	l_pos x;
	gridCutCollisions->divide_Terrain(rocks_1, rocks_2, rocks_3, water, x ,carts);
}
