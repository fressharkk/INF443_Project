#include "scene.hpp"



using namespace cgp;

mesh_drawable testing_mesh;
mesh test;
vec3 ray;

bool is_in(cgp::vec3 pos, cgp::vec3 c, cgp::vec3 h)
{
	float eps = 0.001;
	return (bool) (c.x - h.x / 2 - eps <= pos.x)  && (pos.x <= eps + c.x + h.x / 2) && (c.y - h.y / 2 - eps <= pos.y) && (pos.y <= eps + c.y + h.y / 2) && (c.z - h.z / 2 - eps <= pos.z) && (pos.z <= eps + c.z + h.z / 2);
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
	for (int i = 0; i < nb_chevaliers; i++)
	{

		chevaliers.push_back(new Chevalier(vec3(10, 5, 20 * (rand_interval(0, 1) - 0.5))));

	}

	for (int i = 0; i < nb_soldats; i++)
	{

		soldats.push_back(new Soldat(vec3(-10, 5, 20 * (rand_interval(0, 1) - 0.5))));

	}
}

mesh_drawable hit_box;


void scene_structure::update_camera(int key)
{
	inputs_keyboard_parameters const& keyboard = inputs.keyboard;
	camera_head& camera = environment.camera;

	// The camera moves forward all the time
	//   We consider in this example a constant velocity, so the displacement is: velocity * dt * front-camera-vector
	float const dt = timer.update();
	vec3 const forward_displacement = gui.speed * 0.1f * dt * camera.front();

	vec3 orientation = environment.camera_fixe.front();
	double speed_dep = 5*gui.speed * 0.1f * dt;

	// The camera rotates if we press on the arrow keys
	//  The rotation is only applied to the roll and pitch degrees of freedom.
	float const pitch = 0.5f; // speed of the pitch
	float const roll  = 0.7f; // speed of the roll

	if (key == GLFW_KEY_ESCAPE)
		char_to_follow = { -1, " " };

	if (keyboard.up || key == 87)
	{
		camera.position_camera += speed_dep * orientation;
		
	}
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
	flamme1 = new Flamme(3., 15., 2, 1.);
	
	Soldat::initialize_mesh();
	Chevalier::initialize_mesh();

	dragon.make_dragon();
	
	fire = new Feu(vec3(0, 0, 0), 20, 7, environment.feu_attributes);
	GLuint const shader_deformation = opengl_load_shader("shaders/deformation/vert.glsl", "shaders/deformation/frag.glsl");
	testing_mesh.initialize(mesh_primitive_grid());

	// Default frame
	global_frame.initialize(mesh_primitive_frame(), "Frame");
	
	skybox.initialize("assets/skybox/");
	//skybox.transform.rotation = rotation_transform::from_axis_angle({ 1.0f ,0.0f, 0.0f}, 2.1f) ;

	// Initialize the terrain
	int N_terrain_samples = 100;
	float terrain_length = 100;
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
	//cart.transform.rotation = rotation_transform::from_axis_angle({ 1.0f ,1.0f, 1.0f}, 2.1f) ;
	cart.transform.translation = { -5.5f,0 , evaluate_terrain_height(-5.5f,0)+0.01f};
	cart_position = generate_positions_on_road(100, terrain_length);
	cart.texture = opengl_load_texture_image("assets/bois.jpg", GL_CLAMP_TO_EDGE, GL_MIRRORED_REPEAT);

	mesh straw_mesh = create_straw_mesh();
	straw.initialize(straw_mesh, "straw");
	straw.texture = opengl_load_texture_image("assets/straw.jpg", GL_CLAMP_TO_EDGE, GL_MIRRORED_REPEAT);


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

	//dragon.make_dragon();

	// Initial placement of the camera
	environment.camera.position_camera = { 2.f, 0.f, 2.0f };
	environment.camera_fixe.axis = camera_spherical_coordinates_axis::y;
	environment.camera_fixe.look_at({ 15.0f,6.0f,6.0f }, { 0,0,0 });

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

	for (vec3 position : rock_position) {
		float x = position[0];
		float y = position[1];
		float z = position[2] - 0.6;
		z = evaluate_terrain_height(x, y);
		vec3 position_2 = { x,z,y };
		rock.transform.translation = position_2;
		float a = rand_interval(0, 3) / 3;
		//rock.transform.scaling = a;
		draw(rock, environment);
	}

	global_frame.initialize(mesh_primitive_frame());
}

void scene_structure::display()
{	
	if (!gui.start_scene)
		return;
	if (gui.not_initialized)
		init();

	draw(skybox, environment);
	Soldat::soldat_mesh->soldat_to_draw["Torse"].transform.translation = vec3(0.1 * timer2.t, 0.1 * timer2.t, 0.1 * timer2.t);
	soldats[0]->update_soldat();
	follow_caracter_camera(environment.is_camera_head_used);
	for (int i = 0; i < soldats.size(); i++)
		soldats[i]->draw_soldat(environment);
	
	for (int i = 0; i < chevaliers.size(); i++)
		chevaliers[i]->draw_chevalier(environment);
	draw(terrain, environment);
	draw(global_frame, environment);
	timer2.update();
	// set the light position to the camera
	environment.light = environment.camera.position(); 
	
	// The standard frame
	//mesh_drawable tfff;
	////tfff.initialize(test); 
	////tfff.shading.color = vec3(1, 0, 0);
	////draw(tfff, environment);
	//timer2.update();
	////glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	////glEnable(GL_BLEND);
	//dragon.fly(timer2.t, 1, vec3(20, 40, 10), 20);
	//dragon.fly(timer2.t, 22, vec3(0, 5, 0), 10);
	//dragon.throw_fire(timer2.t, 22, 3, flamme1, environment);
	//// Displaying the shape deformed by the shader
	
	//cgp::draw(terrain, environment);
	//cgp::draw(road, environment);
	//environment.update(timer2.t);  
	//
	//draw(lake, environment);
	////draw_remaining();
	////fire->draw_feu(environment);
	//dragon.dragon_hierarchy.update_local_to_global_coordinates();
	//cgp::draw(global_frame, environment);
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
	ImGui::Button("Test", { 10,10 });
}


