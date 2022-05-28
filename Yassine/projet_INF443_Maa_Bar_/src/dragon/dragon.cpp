#include "dragon.hpp"


using namespace cgp;

float distance(cgp::vec3 vec)
{
	return std::sqrt(dot(vec, vec));
}

vec3 compute_spline(float t, float ti, float ti_1, cgp::vec3 pi, cgp::vec3 pi_1, cgp::vec3 pi_2 = vec3(-100000, -100000, -100000), float ti_2 = 0.0, float K = 0.5)
{
	if (pi_2.x == -100000)
	{
		float dt = ti_1 - ti;
		float s = (t - ti) / dt;
		vec3 di = 2 * K * (pi_1 - pi) / dt;
		return (2 * s * s * s - 3 * s * s + 1) * pi + (2 * s * s * s - 3 * s * s + s) * di + (-2 * s * s * s + 3 * s * s) * pi_1;
	}
	else
	{
		float dt1 = ti_1 - ti;
		float dt2 = ti_2 - ti;
		float s = (t - ti)/dt1;
		vec3 di = 2 * K * (pi_1 - pi) / dt1;
		vec3 di_1 = 2 * K * (pi_2 - pi) / dt2;
		return (2 * s * s * s - 3 * s * s + 1) * pi + (s * s * s - 2 * s * s + s) * di + (-2 * s * s * s + 3 * s * s) * pi_1 + (s * s * s - s * s) * di_1;

	}
	
}

vec3 compute_spline_der(float t, float ti, float ti_1, cgp::vec3 pi, cgp::vec3 pi_1, cgp::vec3 pi_2 = vec3(-100000, -100000, -100000), float ti_2 = 0.0, float K = 0.5)
{
	if (pi_2.x == -100000)
	{
		float dt = ti_1 - ti;
		float s = (t - ti) / dt;
		vec3 di = 2 * K * (pi_1 - pi) / dt;
		return (6 * s * s - 6 * s) * pi + (6 * s * s - 6 * s + 1) * di + (-6 * s * s + 6 * s) * pi_1;
	}
	else
	{
		float dt1 = ti_1 - ti;
		float dt2 = ti_2 - ti;
		float s = (t - ti) / dt1;
		vec3 di = 2 * K * (pi_1 - pi) / dt1;
		vec3 di_1 = 2 * K * (pi_2 - pi) / dt2;
		return (6 * s * s - 6 * s) * pi + (3* s * s - 4 * s + 1) * di + (-6 * s * s + 6 * s) * pi_1 + (3* s * s - 2 * s) * di_1;

	}
	
}


void Dragon::make_dragon()
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
	mesh_drawable front_left_foot;
	mesh_drawable front_right_foot;
	mesh_drawable back_left_foot;
	mesh_drawable back_right_foot;
	mesh_drawable front_left_foot_low;
	mesh_drawable front_right_foot_low;
	mesh_drawable back_left_foot_low;
	mesh_drawable back_right_foot_low;
	mesh_drawable front_left_low_leg;
	mesh_drawable front_right_low_leg;
	mesh_drawable back_left_low_leg;
	mesh_drawable back_right_low_leg;
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
	mesh_drawable upper_mouth;
	mesh_drawable bottom_mouth;
	mesh_drawable inner_upper_mouth;
	mesh_drawable inner_bottom_mouth;
	mesh_drawable pique_pied_gauche;
	mesh_drawable pique_pied_droit;
	mesh_drawable neck_articulation;

	auto texture2 = opengl_load_texture_image("assets/Dragon/dragon_texture_2.jpg", GL_CLAMP_TO_EDGE, GL_MIRRORED_REPEAT);
	auto texture = opengl_load_texture_image("assets/Dragon/dragon_texture.png", GL_CLAMP_TO_EDGE, GL_MIRRORED_REPEAT);
	neck_articulation.initialize(mesh_load_file_obj("assets/Dragon/neck_articulation.obj"), "Neck Articulation");
	neck_articulation.texture = texture;
	neck_head.initialize(mesh_load_file_obj("assets/Dragon/head_without_mouth.obj"), "Neck Head");
	neck_low.initialize(mesh_load_file_obj("assets/Dragon/neck_dragon_low.obj"), "Neck Low");
	cornes.initialize(mesh_load_file_obj("assets/Dragon/Cornes_Dragon.obj"), "Cornes");
	cornes.texture = texture;
	front_right_leg.initialize(mesh_load_file_obj("assets/Dragon/cuisse_avant_droit.obj"), "Front Right Leg");
	front_left_leg.initialize(mesh_load_file_obj("assets/Dragon/cuisse_avant_gauche.obj"), "Front Left Leg");
	back_left_leg.initialize(mesh_load_file_obj("assets/Dragon/cuisse_arriere_gauche.obj"), "Back Left Leg");
	back_right_leg.initialize(mesh_load_file_obj("assets/Dragon/cuisse_arriere_droite.obj"), "Back Right Leg");
	tail.initialize(mesh_load_file_obj("assets/Dragon/dragon_tail.obj"), "Dragon Tail");
	inner_head.initialize(mesh_load_file_obj("assets/Dragon/inner_head_without_mouth.obj"), "Inner Head");
	inner_head.shading.color = vec3(1, 1, 1);
	main_body.initialize(mesh_load_file_obj("assets/Dragon/dragon_body_reconstitue_2.obj"), "Main Body");
	main_body.texture = texture;
	tail.texture = texture;
	front_left_low_leg.initialize(mesh_load_file_obj("assets/Dragon/mollet_avant_gauche.obj"), "Front Left Low Leg");
	front_right_low_leg.initialize(mesh_load_file_obj("assets/Dragon/mollet_avant_droit.obj"), "Front Right Low Leg");
	back_left_low_leg.initialize(mesh_load_file_obj("assets/Dragon/mollet_arriere_gauche.obj"), "Back Left Low Leg");
	back_right_low_leg.initialize(mesh_load_file_obj("assets/Dragon/mollet_arriere_droit.obj"), "Back Right Low Leg");
	front_left_foot.initialize(mesh_load_file_obj("assets/Dragon/pied_avant_gauche.obj"), "Front Left Foot");
	front_right_foot.initialize(mesh_load_file_obj("assets/Dragon/pied_avant_droit.obj"), "Front Right Foot");
	back_left_foot.initialize(mesh_load_file_obj("assets/Dragon/pied_arriere_gauche.obj"), "Back Left Foot");
	back_right_foot.initialize(mesh_load_file_obj("assets/Dragon/pied_arriere_droit.obj"), "Back Right Foot");
	back_right_foot_low.initialize(mesh_load_file_obj("assets/Dragon/pied_arriere_droit_orteils.obj"), "Back Right Foot Low");
	back_left_foot_low.initialize(mesh_load_file_obj("assets/Dragon/pied_arriere_gauche_orteils.obj"), "Back Left Foot Low");
	voile_rwing.initialize(mesh_load_file_obj("assets/Dragon/Voile_RWing.obj"), "Voile RWing");
	voile_lwing.initialize(mesh_load_file_obj("assets/Dragon/Voile_LWing.obj"), "Voile LWing");
	voile_rwing.texture = texture;
	voile_lwing.texture = texture2;
	body_rwing.initialize(mesh_load_file_obj("assets/Dragon/Body_RWing_centered.obj"), "Body RWing");
	body_lwing.initialize(mesh_load_file_obj("assets/Dragon/Body_LWing_centered.obj"), "Body LWing");
	body_rwing.texture = texture;
	body_lwing.texture = texture;
	pique_rwing.initialize(mesh_load_file_obj("assets/Dragon/Pique_RWing.obj"), "Pique RWing");
	pique_lwing.initialize(mesh_load_file_obj("assets/Dragon/Pique_LWing.obj"), "Pique LWing");
	//piques_dos.initialize(mesh_load_file_obj("assets/Dragon/"), "Pique Dos");
	griffes_pied_avant_gauche.initialize(mesh_load_file_obj("assets/Dragon/griffes_pied_avant_gauche.obj"), "griffes_pag");
	griffes_pied_avant_droit.initialize(mesh_load_file_obj("assets/Dragon/griffes_pied_avant_droit.obj"), "griffes_pad");
	griffes_pied_arriere_gauche.initialize(mesh_load_file_obj("assets/Dragon/griffes_pied_arriere_gauche.obj"), "griffes_prg");
	griffes_pied_arriere_droit.initialize(mesh_load_file_obj("assets/Dragon/griffes_pied_arriere_droit.obj"), "griffes_prd");
	eyes.initialize(mesh_load_file_obj("assets/Dragon/Eyes_dragon.obj"), "eyes");
	eyes.shading.color = vec3(1, 0, 1);
	eyes.transform.scaling = 10000;
	upper_mouth.initialize(mesh_load_file_obj("assets/Dragon/upper_mouth.obj"), "Upper Mouth");
	bottom_mouth.initialize(mesh_load_file_obj("assets/Dragon/bottom_mouth.obj"), "Bottom Mouth");
	inner_upper_mouth.initialize(mesh_load_file_obj("assets/Dragon/inner_upper_mouth.obj"), "Inner Upper Mouth");
	inner_bottom_mouth.initialize(mesh_load_file_obj("assets/Dragon/inner_bottom_mouth.obj"), "Inner Bottom Mouth");
	pique_pied_droit.initialize(mesh_load_file_obj("assets/Dragon/pique_pied_arriere_droit.obj"), "Pique Right Foot");
	pique_pied_gauche.initialize(mesh_load_file_obj("assets/Dragon/pique_pied_arriere_gauche.obj"), "Pique Left Foot");
	
	//front_left_leg.texture = texture;
	front_right_leg.texture = texture;
	front_left_leg.texture = texture;
	back_right_leg.texture = texture;
	back_left_leg.texture = texture;
	front_left_low_leg.texture = texture;
	front_left_foot.texture = texture;
	front_right_low_leg.texture = texture;
	front_right_foot.texture = texture;
	back_left_low_leg.texture = texture;
	back_left_foot.texture = texture;
	back_right_low_leg.texture = texture;
	back_right_foot.texture = texture;
	neck_low.texture = texture;
	neck_head.texture = texture;
	back_right_foot_low.texture = texture;
	back_left_foot_low.texture = texture;
	upper_mouth.texture = texture;
	bottom_mouth.texture = texture;

	vec3 rwing_translation = vec3(-.7, 3.3, 2.5);
	vec3 lwing_translation = vec3(.3, 3.4, 2.5);
	vec3 f_left_leg_trans = vec3(-0.6, -2.6, -2.6);
	vec3 f_right_leg_trans = vec3(0.7, -3, -2.5);
	vec3 b_right_leg_trans = vec3(0.3, -3.1, -0.3);
	vec3 b_left_leg_trans = vec3(-0.6, -3, -0.3);
	vec3 neck_low_trans = vec3(0, -2.5, -3.3);
	vec3 neck_head_trans = vec3(0, -4.7, -3.6);
	vec3 f_left_low_leg_trans = vec3(-0.5, -1.45, -2.1);
	vec3 f_left_foot_trans = vec3(-0.7, -0.5, -3.2);
	vec3 f_right_low_leg_trans = vec3(0.7, -1.6, -2.5);
	vec3 f_right_foot_trans = vec3(1.4, -3.6, -5.8);
	vec3 b_left_low_leg_trans = vec3(-0.8, -1.8, -1.2);
	vec3 b_left_foot_trans = vec3(-0.7, -1.6, 0.3f);
	vec3 b_right_low_leg_trans = vec3(0.8, -1.8, -1.2);
	vec3 b_right_foot_trans = vec3(0.8, -1.6, 0.4);//vec3(0.7, -1.2, 0.6);
	vec3 b_right_foot_low_trans = vec3(0.7, -1, 0.05);
	vec3 b_left_foot_low_trans = vec3(-0.8, -1, 0);
	vec3 bottom_mouth_trans = vec3(0, -4.8, -4.3);
	vec3 upper_mouth_trans = vec3(0, -5.1, -4.6);

	front_left_leg.transform.translation = f_left_leg_trans;
	griffes_pied_avant_gauche.transform.translation = f_left_foot_trans;
	front_right_leg.transform.translation = f_right_leg_trans;
	griffes_pied_avant_droit.transform.translation = f_right_foot_trans;
	back_right_leg.transform.translation = b_right_leg_trans;
	griffes_pied_arriere_droit.transform.translation = b_right_foot_low_trans;
	back_left_leg.transform.translation = b_left_leg_trans;
	griffes_pied_arriere_gauche.transform.translation = b_left_foot_low_trans;
	pique_pied_droit.transform.translation = b_right_foot_trans;
	pique_pied_gauche.transform.translation = b_left_foot_trans;
	neck_low.transform.translation = neck_low_trans;
	neck_articulation.transform.translation = neck_low_trans;
	neck_head.transform.translation = neck_head_trans;
	front_left_low_leg.transform.translation = f_left_low_leg_trans;
	front_left_foot.transform.translation = f_left_foot_trans;
	front_right_low_leg.transform.translation = f_right_low_leg_trans;
	front_right_foot.transform.translation = f_right_foot_trans;
	back_left_low_leg.transform.translation = b_left_low_leg_trans;
	back_left_foot.transform.translation = b_left_foot_trans;
	back_right_low_leg.transform.translation = b_right_low_leg_trans;
	back_right_foot.transform.translation = b_right_foot_trans;
	back_right_foot_low.transform.translation = b_right_foot_low_trans;
	back_left_foot_low.transform.translation = b_left_foot_low_trans;
	upper_mouth.transform.translation = upper_mouth_trans;
	bottom_mouth.transform.translation = bottom_mouth_trans;
	inner_upper_mouth.transform.translation = upper_mouth_trans;
	inner_bottom_mouth.transform.translation = bottom_mouth_trans;
	

	dragon_hierarchy.add(main_body);
	dragon_hierarchy.add(neck_low, "Main Body", -neck_low_trans);
	dragon_hierarchy.add(neck_head, "Neck Low", neck_low_trans - neck_head_trans);
	dragon_hierarchy.add(front_right_leg, "Main Body", -f_right_leg_trans);
	dragon_hierarchy.add(front_left_leg, "Main Body", -f_left_leg_trans);
	dragon_hierarchy.add(back_left_leg, "Main Body", -b_left_leg_trans);
	dragon_hierarchy.add(back_right_leg, "Main Body", -b_right_leg_trans);
	dragon_hierarchy.add(eyes, "Neck Head", neck_head_trans);
	dragon_hierarchy.add(cornes, "Neck Head", neck_head_trans);
	dragon_hierarchy.add(inner_head, "Neck Head", neck_head_trans);
	dragon_hierarchy.add(body_rwing, "Main Body", rwing_translation); // the translation is used to place the cube at the extremity of the cylinder
	dragon_hierarchy.add(body_lwing, "Main Body", lwing_translation);//, {1.0f, 0, 0});
	dragon_hierarchy.add(front_left_low_leg, "Front Left Leg", f_left_leg_trans - f_left_low_leg_trans);
	dragon_hierarchy.add(front_left_foot, "Front Left Low Leg", f_left_low_leg_trans - f_left_foot_trans);
	dragon_hierarchy.add(front_right_low_leg, "Front Right Leg", f_right_leg_trans - f_right_low_leg_trans);
	dragon_hierarchy.add(front_right_foot, "Front Right Low Leg", f_right_low_leg_trans - f_right_foot_trans);
	dragon_hierarchy.add(back_left_low_leg, "Back Left Leg", b_left_leg_trans - b_left_low_leg_trans);
	dragon_hierarchy.add(back_left_foot, "Back Left Low Leg", b_left_low_leg_trans - b_left_foot_trans);
	dragon_hierarchy.add(back_right_low_leg, "Back Right Leg", b_right_leg_trans - b_right_low_leg_trans);
	dragon_hierarchy.add(back_right_foot, "Back Right Low Leg", b_right_low_leg_trans - b_right_foot_trans);
	dragon_hierarchy.add(back_right_foot_low, "Back Right Foot", b_right_foot_trans - b_right_foot_low_trans);
	dragon_hierarchy.add(back_left_foot_low, "Back Left Foot", b_left_foot_trans - b_left_foot_low_trans);
	dragon_hierarchy.add(griffes_pied_avant_gauche, "Front Left Foot");
	dragon_hierarchy.add(griffes_pied_avant_droit, "Front Right Foot");
	dragon_hierarchy.add(griffes_pied_arriere_gauche, "Back Left Foot Low");
	dragon_hierarchy.add(griffes_pied_arriere_droit, "Back Right Foot Low");
	dragon_hierarchy.add(voile_lwing, "Body LWing", -lwing_translation);
	dragon_hierarchy.add(voile_rwing, "Body RWing", -rwing_translation);
	dragon_hierarchy.add(pique_rwing, "Body RWing", -rwing_translation);
	dragon_hierarchy.add(pique_lwing, "Body LWing", -lwing_translation);
	dragon_hierarchy.add(tail, "Main Body", { 0,0,0.02 });
	dragon_hierarchy.add(upper_mouth, "Neck Head", neck_head_trans - upper_mouth_trans);
	dragon_hierarchy.add(bottom_mouth, "Neck Head", neck_head_trans - bottom_mouth_trans);
	dragon_hierarchy.add(inner_upper_mouth, "Upper Mouth");
	dragon_hierarchy.add(inner_bottom_mouth, "Bottom Mouth");
	dragon_hierarchy.add(pique_pied_droit, "Back Right Foot");
	dragon_hierarchy.add(pique_pied_gauche, "Back Left Foot");
	//dragon_hierarchy.add(neck_articulation, "Neck Low");

	dragon_hierarchy["Main Body"].transform.scaling = 0.5;
	dragon_hierarchy["Main Body"].transform.translation = vec3(0., -1., -1);
	//dragon["Main Body"].transform.translation = vec3(5,0,0);
	dragon_hierarchy.update_local_to_global_coordinates();
	
}

vec3 Dragon::get_current_position()
{
	return dragon_hierarchy["Main Body"].global_transform.translation;
}

vec3 Dragon::get_current_orientation()
{
	return rotation_transform::convert_quaternion_to_matrix(dragon_hierarchy["Main Body"].global_transform.rotation.data) * vec3(0, 0, 1);
}

vec3 Dragon::get_mouth_position()
{
	mat3 rot = rotation_transform::convert_quaternion_to_matrix(dragon_hierarchy["Neck Head"].global_transform.rotation.data);
	vec3 trans = 0.2 * rot * vec3(0, 0, 1);
	return (dragon_hierarchy["Upper Mouth"].global_transform.translation+dragon_hierarchy["Bottom Mouth"].global_transform.translation)/2 +trans;
}

vec3 Dragon::get_mouth_orientation()
{
	return rotation_transform::convert_quaternion_to_matrix(dragon_hierarchy["Neck Head"].global_transform.rotation.data) * vec3(0, 0, 1);
}

cgp::rotation_transform Dragon::get_rotation()
{
	return dragon_hierarchy["Main Body"].global_transform.rotation;
}

cgp::rotation_transform Dragon::get_eyes_rotation()
{
	return dragon_hierarchy["Neck Head"].global_transform.rotation;
}

void Dragon::reset_legs()
{
	dragon_hierarchy["Back Left Leg"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, 0);
	dragon_hierarchy["Back Left Low Leg"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, 0);
	dragon_hierarchy["Back Left Foot"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, 0);
	dragon_hierarchy["Back Left Foot Low"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, 0);
	dragon_hierarchy["Back Right Leg"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, 0);
	dragon_hierarchy["Back Right Low Leg"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, 0);
	dragon_hierarchy["Back Right Foot"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, 0);
	dragon_hierarchy["Back Right Foot Low"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, 0);
	dragon_hierarchy["Front Left Leg"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, 0);
	dragon_hierarchy["Front Left Low Leg"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, 0);
	dragon_hierarchy["Front Right Leg"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, 0);
	dragon_hierarchy["Front Right Low Leg"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, 0);
	dragon_hierarchy["Front Left Foot"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, 0);
	dragon_hierarchy["Front Right Foot"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, 0);
}

void Dragon::draw_dragon(scene_environment_camera_head& environment)
{
	dragon_hierarchy.update_local_to_global_coordinates();
	draw(dragon_hierarchy, environment);
	//dragon_hierarchy["Main Body"].transform.translation = vec3(0, 0, 0);
	//dragon_hierarchy.update_local_to_global_coordinates();
}

void Dragon::open_mouth(float t, float starting_time, float duration, float speed)
{	
	if (t < starting_time)
		return;
	float angle = 0.0;
	float target_angle = Pi / 12;
	if (std::abs(speed) < 0.0000001)
	{
		if (t > starting_time + duration)
			return;
		else
		{
			angle = target_angle * (t - starting_time) / duration;
		}
	}
	else
	{
		if (t > starting_time + target_angle / speed)
			return;
		else
			angle = target_angle * (t - starting_time) * speed;
	}

	dragon_hierarchy["Upper Mouth"].transform.rotation = rotation_transform::from_axis_angle({ -1.,0,0 }, angle);
	dragon_hierarchy["Bottom Mouth"].transform.rotation = rotation_transform::from_axis_angle({ 1.,0.,0. }, angle);
	//dragon_hierarchy.update_local_to_global_coordinates();
}

void Dragon::close_mouth(float t, float starting_time, float duration, float speed)
{
	if (t < starting_time)
		return;
	float angle = 0.0;
	float target_angle = Pi / 12;
	if (std::abs(speed) < 0.0000001)
	{
		if (t > starting_time + duration)
			return;
		else
		{
			angle = target_angle - target_angle * (t - starting_time) / duration;
		}
	}
	else
	{
		if (t > starting_time + target_angle / speed)
			return;
		else
			angle = target_angle - target_angle * (t - starting_time) * speed;
	}

	dragon_hierarchy["Upper Mouth"].transform.rotation = rotation_transform::from_axis_angle({ -1.,0,0 }, angle);
	dragon_hierarchy["Bottom Mouth"].transform.rotation = rotation_transform::from_axis_angle({ 1.,0.,0. }, angle);
	//dragon_hierarchy.update_local_to_global_coordinates();
}

void Dragon::stretching_back_legs(float t, float beginning_time, float duration)
{
	if (t < beginning_time)
		return;
	if (t > beginning_time + duration)
		return;

	float leg_angle = 0.0;
	float leg_target_angle = 1.2 * Pi / 2;
	float low_leg_angle = 0.0;
	float low_leg_target_angle = 3.2 * Pi / 4;
	float foot_angle = 0.0;
	float foot_target_angle = 2.1 * Pi / 3;
	float foot_low_angle = 0.0;
	float foot_low_target_angle = Pi / 3;

	leg_angle = leg_target_angle * (t - beginning_time) / duration;
	low_leg_angle = low_leg_target_angle * (t - beginning_time) / duration;
	foot_angle = foot_target_angle * (t - beginning_time) / duration;
	foot_low_angle = foot_low_target_angle * (t - beginning_time) / duration;
	
	dragon_hierarchy["Back Left Leg"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, leg_angle);
	dragon_hierarchy["Back Left Low Leg"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, low_leg_angle);
	dragon_hierarchy["Back Left Foot"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, foot_angle);
	dragon_hierarchy["Back Left Foot Low"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, foot_low_angle);

	dragon_hierarchy["Back Right Leg"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, leg_angle);
	dragon_hierarchy["Back Right Low Leg"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, low_leg_angle);
	dragon_hierarchy["Back Right Foot"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, foot_angle);
	dragon_hierarchy["Back Right Foot Low"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, foot_low_angle);
}

void Dragon::folding_back_legs(float t, float beginning_time, float duration)
{

	if (t < beginning_time)
		return;
	if (t > beginning_time + duration)
		return;

	float leg_angle = 0.0;
	float leg_target_angle = 1.2 * Pi / 2;
	float low_leg_angle = 0.0;
	float low_leg_target_angle = 3.2 * Pi / 4;
	float foot_angle = 0.0;
	float foot_target_angle = 2.1 * Pi / 3;
	float foot_low_angle = 0.0;
	float foot_low_target_angle = Pi / 3;

	leg_angle = leg_target_angle - leg_target_angle * (t - beginning_time) / duration;
	low_leg_angle = low_leg_target_angle - low_leg_target_angle * (t - beginning_time) / duration;
	foot_angle = foot_target_angle - foot_target_angle * (t - beginning_time) / duration;
	foot_low_angle = foot_low_target_angle - foot_low_target_angle * (t - beginning_time) / duration;

	dragon_hierarchy["Back Left Leg"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, leg_angle);
	dragon_hierarchy["Back Left Low Leg"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, low_leg_angle);
	dragon_hierarchy["Back Left Foot"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, foot_angle);
	dragon_hierarchy["Back Left Foot Low"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, foot_low_angle);

	dragon_hierarchy["Back Right Leg"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, leg_angle);
	dragon_hierarchy["Back Right Low Leg"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, low_leg_angle);
	dragon_hierarchy["Back Right Foot"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, foot_angle);
	dragon_hierarchy["Back Right Foot Low"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, foot_low_angle);

}

void Dragon::stretching_front_legs(float t, float beginning_time, float duration, float speed)
{
	if (t < beginning_time)
		return;

	float angle = 0.0;
	float target_angle = 1.2 * Pi / 6;
	float low_angle = 0.0;
	float low_target_angle = Pi / 4;
	if (std::abs(speed) < 0.0000001)
	{
		if (t > beginning_time + duration)
			return;
		else
		{
			angle = target_angle * (t - beginning_time) / duration;
			low_angle = low_target_angle * (t - beginning_time) / duration;
		}
	}
	else
	{
		if (t > beginning_time + std::max(target_angle, low_target_angle) / speed)
			return;
		else
		{
			angle = target_angle * (t - beginning_time) * speed;
			low_angle = low_target_angle * (t - beginning_time) * speed;
		}

	}
	dragon_hierarchy["Front Left Leg"].transform.rotation = rotation_transform::from_axis_angle({ 1.,0.,0. }, angle);
	dragon_hierarchy["Front Left Low Leg"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, low_angle);
	dragon_hierarchy["Front Right Leg"].transform.rotation = rotation_transform::from_axis_angle({ 1.,0.,0. }, angle);
	dragon_hierarchy["Front Right Low Leg"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, low_angle);
}

void Dragon::folding_front_legs(float t, float beginning_time, float duration, float speed)

{
	if (t < beginning_time)
		return;

	float angle = 0.0;
	float target_angle = 1.2 * Pi / 6;
	float low_angle = 0.0;
	float low_target_angle = Pi / 4;
	if (std::abs(speed) < 0.0000001)
	{
		if (t > beginning_time + duration)
			return;
		else
		{
			angle = target_angle - target_angle * (t - beginning_time) / duration;
			low_angle = low_target_angle - low_target_angle * (t - beginning_time) / duration;
		}
	}
	else
	{
		if (t > beginning_time + std::max(target_angle, low_target_angle) / speed)
			return;
		else
		{
			angle = target_angle - target_angle * (t - beginning_time) * speed;
			low_angle = low_target_angle - low_target_angle * (t - beginning_time) * speed;
		}

	}
	dragon_hierarchy["Front Left Leg"].transform.rotation = rotation_transform::from_axis_angle({ 1.,0.,0. }, angle);
	dragon_hierarchy["Front Left Low Leg"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, low_angle);
	dragon_hierarchy["Front Right Leg"].transform.rotation = rotation_transform::from_axis_angle({ 1.,0.,0. }, angle);
	dragon_hierarchy["Front Right Low Leg"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, low_angle);
}

void Dragon::initialize_rd_tail(int n)
{
	for (int i = 0; i < n; i++)
	random_tail_axis.push_back(vec3(0.3*rand_interval(0.0, 1.), rand_interval(0.0, 1.), 0.3*rand_interval(0.0, 1.)));

	dragon_random_tail_not_initialized = false;
}

void Dragon::random_moving_tail(float t, float beginning_time, float duration)
{
	float rd_dur = 1;
	float amplitude = 0.2;
	if (t < beginning_time || t > beginning_time + duration)
		return;

	if (dragon_random_tail_not_initialized)
	{
		int n = (int)duration / rd_dur + 1;
		initialize_rd_tail(n);
	}

	int k = (int) (t - beginning_time) / rd_dur;
	float time = std::fmod( (t - beginning_time),  rd_dur);
	dragon_hierarchy["Dragon Tail"].transform.rotation = rotation_transform::from_axis_angle(random_tail_axis[k],
		(std::sin(Pi/2*time/ rd_dur - Pi/4) * std::sin(Pi/2 * time/ rd_dur - Pi/4) - 0.5) * amplitude);

	
	
}

void Dragon::fly_left_wing(float t, float beginning_time, float wing_speed, float duration)
{
	if (t < beginning_time || t > beginning_time + duration)
		return;
	
	
	float angle = (std::sin(wing_speed*t) * std::sin(wing_speed*t) - 0.5) * 0.5;
	dragon_hierarchy["Body LWing"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, angle);
	
}

void Dragon::fly_right_wing(float t, float beginning_time, float wing_speed, float duration)
{
	if (t < beginning_time || t > beginning_time + duration)
		return;

	float angle = (std::sin(wing_speed * t) * std::sin(wing_speed * t) - 0.5) * 0.5;
	dragon_hierarchy["Body RWing"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,-1 }, angle);

}

void Dragon::full_stretching_neck(float t, float beginning_time, float duration)
{
	if (t < beginning_time || t > beginning_time + duration)
		return;
	

	float angle = 0.0;
	float target_angle = Pi / 3;
	float low_angle = 0.0;
	float low_target_angle = Pi / 4;
		
	angle = target_angle * (t - beginning_time) / duration;
	low_angle = low_target_angle * (t - beginning_time) / duration;
	

	
	dragon_hierarchy["Neck Low"].transform.rotation = rotation_transform::from_axis_angle({ 1.,0.,0. }, angle);
	dragon_hierarchy["Neck Head"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, low_angle);
	
}

void Dragon::walking_phase_1(float t, float beginning_time, float walking_speed, float duration)
{
	float speed = walking_speed;
	if (t < beginning_time)
		return;
	if (t > beginning_time + duration)
		return;

	float leg_angle = 0.0;
	float leg_target_angle = Pi / 6;
	float low_leg_angle = 0.0;
	float low_leg_target_angle = 0.2*Pi / 4;
	float foot_angle = 0.0;
	float foot_target_angle = 0*Pi / 6;
	float foot_low_angle = 0.0;
	float foot_low_target_angle = Pi / 6;

	float f_angle = 0.0;
	float f_target_angle = Pi / 3;
	float f_low_angle = 0.0;
	float f_low_target_angle = 0.2*Pi / 2;

	leg_angle = leg_target_angle * (t - beginning_time) / duration;
	low_leg_angle = low_leg_target_angle * (t - beginning_time) / duration;
	foot_angle = foot_target_angle * (t - beginning_time) / duration;
	foot_low_angle = foot_low_target_angle * (t - beginning_time) / duration;
	f_angle = f_target_angle * (t - beginning_time) / duration;
	f_low_angle = f_low_target_angle * (t - beginning_time) / duration;
	
	
	dragon_hierarchy["Back Left Leg"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, leg_angle);
	dragon_hierarchy["Back Left Low Leg"].transform.rotation = rotation_transform::from_axis_angle({-1,0,0 }, low_leg_angle);
	dragon_hierarchy["Back Left Foot"].transform.rotation = rotation_transform::from_axis_angle({1,0,0 }, foot_angle);
	dragon_hierarchy["Back Left Foot Low"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, foot_low_angle);

	/*dragon_hierarchy["Back Right Leg"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, leg_angle);
	dragon_hierarchy["Back Right Low Leg"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, low_leg_angle);
	dragon_hierarchy["Back Right Foot"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, foot_angle);
	dragon_hierarchy["Back Right Foot Low"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, foot_low_angle);*/

	//dragon_hierarchy["Front Left Leg"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, f_angle);
	//dragon_hierarchy["Front Left Low Leg"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, f_low_angle);

	dragon_hierarchy["Front Right Leg"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, f_angle);
	dragon_hierarchy["Front Right Low Leg"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, f_low_angle);

}

void Dragon::walking_phase_2(float t, float beginning_time, float walking_speed, float duration)
{
	float speed = walking_speed;
	if (t < beginning_time)
		return;
	if (t > beginning_time + duration)
		return;

	float leg_angle = 0.0;
	float leg_target_angle = Pi / 6;
	float low_leg_angle = 0.0;
	float low_leg_target_angle = 0.2 * Pi / 4;
	float foot_angle = 0.0;
	float foot_target_angle = 0 * Pi / 6;
	float foot_low_angle = 0.0;
	float foot_low_target_angle = Pi / 6;

	float f_angle = 0.0;
	float f_target_angle = Pi / 3;
	float f_low_angle = 0.0;
	float f_low_target_angle = 0.2 * Pi / 2;


	leg_angle = leg_target_angle-leg_target_angle * (t - beginning_time) / duration;
	low_leg_angle = low_leg_target_angle-low_leg_target_angle * (t - beginning_time) / duration;
	foot_angle = foot_target_angle-foot_target_angle * (t - beginning_time) / duration;
	foot_low_angle = foot_low_target_angle-foot_low_target_angle * (t - beginning_time) / duration;

	f_angle = f_target_angle - f_target_angle * (t - beginning_time) / duration;
	f_low_angle = f_low_target_angle - f_low_target_angle * (t - beginning_time) / duration; 

	dragon_hierarchy["Back Left Leg"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, leg_angle);
	dragon_hierarchy["Back Left Low Leg"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, low_leg_angle);
	dragon_hierarchy["Back Left Foot"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, foot_angle);
	dragon_hierarchy["Back Left Foot Low"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, foot_low_angle);

	/*dragon_hierarchy["Back Right Leg"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, leg_angle);
	dragon_hierarchy["Back Right Low Leg"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, low_leg_angle);
	dragon_hierarchy["Back Right Foot"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, foot_angle);
	dragon_hierarchy["Back Right Foot Low"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, foot_low_angle);*/

	dragon_hierarchy["Front Right Leg"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, f_angle);
	dragon_hierarchy["Front Right Low Leg"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, f_low_angle);

}

void Dragon::walking_phase_3(float t, float beginning_time, float walking_speed, float duration)
{

	//float speed = walking_speed;
	//if (t < beginning_time)
	//	return;
	//if (t > beginning_time + duration)
	//	return;

	//float leg_angle = 0.0;
	//float leg_target_angle = 0.9 * Pi / 6;
	//float low_leg_angle = 0.0;
	//float low_leg_target_angle = 0.9 * Pi / 4;
	//float foot_angle = 0.0;
	//float foot_target_angle = Pi / 6;
	//float foot_low_angle = 0.0;
	//float foot_low_target_angle = Pi / 6;

	//leg_angle = leg_target_angle * (t - beginning_time) / duration;
	//low_leg_angle = low_leg_target_angle * (t - beginning_time) / duration;
	//foot_angle = foot_target_angle * (t - beginning_time) / duration;
	//foot_low_angle = foot_low_target_angle * (t - beginning_time) / duration;

	//dragon_hierarchy["Back Right Leg"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, leg_angle);
	//dragon_hierarchy["Back Right Low Leg"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, low_leg_angle);
	//dragon_hierarchy["Back Right Foot"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, foot_angle);
	//dragon_hierarchy["Back Right Foot Low"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, foot_low_angle);

	//dragon_hierarchy["Back Left Leg"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, leg_angle);
	//dragon_hierarchy["Back Left Low Leg"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, low_leg_angle);
	//dragon_hierarchy["Back Left Foot"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, foot_angle);
	//dragon_hierarchy["Back Left Foot Low"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, foot_low_angle);

	float speed = walking_speed;
	if (t < beginning_time)
		return;
	if (t > beginning_time + duration)
		return;

	float leg_angle = 0.0;
	float leg_target_angle = Pi / 6;
	float low_leg_angle = 0.0;
	float low_leg_target_angle = 0.2 * Pi / 4;
	float foot_angle = 0.0;
	float foot_target_angle = 0 * Pi / 6;
	float foot_low_angle = 0.0;
	float foot_low_target_angle = Pi / 6;

	float f_angle = 0.0;
	float f_target_angle = Pi / 3;
	float f_low_angle = 0.0;
	float f_low_target_angle = 0.2 * Pi / 2;

	leg_angle = leg_target_angle * (t - beginning_time) / duration;
	low_leg_angle = low_leg_target_angle * (t - beginning_time) / duration;
	foot_angle = foot_target_angle * (t - beginning_time) / duration;
	foot_low_angle = foot_low_target_angle * (t - beginning_time) / duration;
	f_angle = f_target_angle * (t - beginning_time) / duration;
	f_low_angle = f_low_target_angle * (t - beginning_time) / duration;


	dragon_hierarchy["Back Right Leg"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, leg_angle);
	dragon_hierarchy["Back Right Low Leg"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, low_leg_angle);
	dragon_hierarchy["Back Right Foot"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, foot_angle);
	dragon_hierarchy["Back Right Foot Low"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, foot_low_angle);

	/*dragon_hierarchy["Back Right Leg"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, leg_angle);
	dragon_hierarchy["Back Right Low Leg"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, low_leg_angle);
	dragon_hierarchy["Back Right Foot"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, foot_angle);
	dragon_hierarchy["Back Right Foot Low"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, foot_low_angle);*/

	//dragon_hierarchy["Front Left Leg"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, f_angle);
	//dragon_hierarchy["Front Left Low Leg"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, f_low_angle);

	dragon_hierarchy["Front Left Leg"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, f_angle);
	dragon_hierarchy["Front Left Low Leg"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, f_low_angle);

}

void Dragon::walking_phase_4(float t, float beginning_time, float walking_speed, float duration)
{
	/*float speed = walking_speed;
	if (t < beginning_time)
		return;
	if (t > beginning_time + duration)
		return;

	float leg_angle = 0.0;
	float leg_target_angle = 0.9 * Pi / 6;
	float low_leg_angle = 0.0;
	float low_leg_target_angle = 0.9 * Pi / 4;
	float foot_angle = 0.0;
	float foot_target_angle = Pi / 6;
	float foot_low_angle = 0.0;
	float foot_low_target_angle = Pi / 6;

	leg_angle = leg_target_angle - leg_target_angle * (t - beginning_time) / duration;
	low_leg_angle = low_leg_target_angle - low_leg_target_angle * (t - beginning_time) / duration;
	foot_angle = foot_target_angle - foot_target_angle * (t - beginning_time) / duration;
	foot_low_angle = foot_low_target_angle - foot_low_target_angle * (t - beginning_time) / duration;

	dragon_hierarchy["Back Right Leg"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, leg_angle);
	dragon_hierarchy["Back Right Low Leg"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, low_leg_angle);
	dragon_hierarchy["Back Right Foot"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, foot_angle);
	dragon_hierarchy["Back Right Foot Low"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, foot_low_angle);

	dragon_hierarchy["Back Left Leg"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, leg_angle);
	dragon_hierarchy["Back Left Low Leg"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, low_leg_angle);
	dragon_hierarchy["Back Left Foot"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, foot_angle);
	dragon_hierarchy["Back Left Foot Low"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, foot_low_angle);*/
	float speed = walking_speed;
	if (t < beginning_time)
		return;
	if (t > beginning_time + duration)
		return;

	float leg_angle = 0.0;
	float leg_target_angle = Pi / 6;
	float low_leg_angle = 0.0;
	float low_leg_target_angle = 0.2 * Pi / 4;
	float foot_angle = 0.0;
	float foot_target_angle = 0 * Pi / 6;
	float foot_low_angle = 0.0;
	float foot_low_target_angle = Pi / 6;

	float f_angle = 0.0;
	float f_target_angle = Pi / 3;
	float f_low_angle = 0.0;
	float f_low_target_angle = 0.2 * Pi / 2;


	leg_angle = leg_target_angle - leg_target_angle * (t - beginning_time) / duration;
	low_leg_angle = low_leg_target_angle - low_leg_target_angle * (t - beginning_time) / duration;
	foot_angle = foot_target_angle - foot_target_angle * (t - beginning_time) / duration;
	foot_low_angle = foot_low_target_angle - foot_low_target_angle * (t - beginning_time) / duration;

	f_angle = f_target_angle - f_target_angle * (t - beginning_time) / duration;
	f_low_angle = f_low_target_angle - f_low_target_angle * (t - beginning_time) / duration;

	dragon_hierarchy["Back Right Leg"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, leg_angle);
	dragon_hierarchy["Back Right Low Leg"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, low_leg_angle);
	dragon_hierarchy["Back Right Foot"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, foot_angle);
	dragon_hierarchy["Back Right Foot Low"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, foot_low_angle);

	/*dragon_hierarchy["Back Right Leg"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, leg_angle);
	dragon_hierarchy["Back Right Low Leg"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, low_leg_angle);
	dragon_hierarchy["Back Right Foot"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, foot_angle);
	dragon_hierarchy["Back Right Foot Low"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, foot_low_angle);*/

	dragon_hierarchy["Front Left Leg"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, f_angle);
	dragon_hierarchy["Front Left Low Leg"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, f_low_angle);

}

void Dragon::walking(float t, float beginning_time, vec3 where_to,  float duration)
{
	if (t < beginning_time || t > beginning_time + duration)
		return;
	if (t < beginning_time + 0.01 && t> beginning_time - 0.01)
	{
		initial_position_walking = get_current_position();
	}
	if (t < beginning_time +duration + 0.01 && t> beginning_time + duration - 0.01)
	{
		reset_legs();
	}
	vec3 diff = where_to - initial_position_walking;
	
	float distance = std::sqrt(dot(diff, diff));
	float speed = distance / duration;
	float step_dur = 0.25/speed;
	int nb_pas = (int) duration/step_dur;
	
	for (int i = 0; i < nb_pas+1; i++)
	{
		walking_phase_1(t, 4*step_dur* i, 1, step_dur);
		walking_phase_2(t, 4*step_dur * i + step_dur, 1, step_dur);
		walking_phase_3(t, 4*step_dur * i + 2*step_dur, 1, step_dur);
		walking_phase_4(t, 4*step_dur * i + 3*step_dur, 1, step_dur);
	}
	
	dragon_hierarchy["Main Body"].transform.translation = initial_position_walking + (t - beginning_time) / duration * diff;
}

void Dragon::fly(float t, float beginning_time, cgp::vec3 where_to, float duration, std::string type)
{
	if (t < beginning_time || t > beginning_time + duration)
		return;
	if (beginning_time - 0.01 < t && beginning_time + 0.01 > t)
	{
		initial_position_temp = get_current_position();
		current_orientation_temp = 4*rotation_transform::convert_quaternion_to_matrix(dragon_hierarchy["Main Body"].global_transform.rotation.data) * vec3(0,0,1);
		float dist = distance(where_to - current_orientation_temp);
		time_coupure = duration * 4/(dist+4);
	}
	if (type == "spline_cardinale")
	{

		dragon_hierarchy["Main Body"].transform.translation = compute_spline(t, beginning_time + time_coupure, beginning_time + duration, initial_position_temp, where_to);
		vec3 dir_vect = compute_spline_der(t, beginning_time + time_coupure, beginning_time + duration, initial_position_temp, where_to);
		vec3 norm_dir_vect = 1 / distance(dir_vect) * dir_vect;
		dragon_hierarchy["Main Body"].transform.rotation = rotation_transform::between_vector(vec3(0, 0, 1), norm_dir_vect);
		dragon_hierarchy.update_local_to_global_coordinates();

		if (dragon_hierarchy["Body RWing"].global_transform.translation.y < dragon_hierarchy["Main Body"].global_transform.translation.y)
		{
			mat3 rot1 = rotation_transform::convert_quaternion_to_matrix(rotation_transform::between_vector(vec3(0, 0, 1), norm_dir_vect).data);
			mat3 rot2 = rotation_transform::convert_quaternion_to_matrix(rotation_transform::from_axis_angle({ 0,0,1 }, Pi).data);
			dragon_hierarchy["Main Body"].transform.rotation = rotation_transform::from_matrix(rot1 * rot2);
		}

	}
	if (type == "spline_int_cardinale")
	{

		vec3 int_point = initial_position_temp + current_orientation_temp;
		/*
		vec3 diff = where_to - current_orientation_temp;
		diff = 1 / distance(diff)*diff;
		int_point += vec3(-4 * diff.z, 0., -4 * diff.x) + 4*current_orientation_temp;
		std::cout << int_point << std::endl;*/
		if (t - beginning_time < time_coupure)
		{
			dragon_hierarchy["Main Body"].transform.translation = compute_spline(t, beginning_time, beginning_time + time_coupure, initial_position_temp, int_point,where_to, beginning_time+duration);
			vec3 dir_vect = compute_spline_der(t, beginning_time, beginning_time + time_coupure, initial_position_temp, int_point, where_to, beginning_time + duration);
			vec3 norm_dir_vect = 1 / distance(dir_vect) * dir_vect;
			dragon_hierarchy["Main Body"].transform.rotation = rotation_transform::between_vector(vec3(0, 0, 1), norm_dir_vect);
			dragon_hierarchy.update_local_to_global_coordinates();

			if (dragon_hierarchy["Body RWing"].global_transform.translation.y < dragon_hierarchy["Main Body"].global_transform.translation.y)
			{
				mat3 rot1 = rotation_transform::convert_quaternion_to_matrix(rotation_transform::between_vector(vec3(0, 0, 1), norm_dir_vect).data);
				mat3 rot2 = rotation_transform::convert_quaternion_to_matrix(rotation_transform::from_axis_angle({0,0,1}, Pi).data);
				dragon_hierarchy["Main Body"].transform.rotation = rotation_transform::from_matrix(rot1 * rot2);
			}
				
		}
		else
		{
			dragon_hierarchy["Main Body"].transform.translation = compute_spline(t, beginning_time+ time_coupure, beginning_time + duration, int_point, where_to);
			vec3 dir_vect = compute_spline_der(t, beginning_time + time_coupure, beginning_time + duration, int_point, where_to);
			vec3 norm_dir_vect = 1 / distance(dir_vect) * dir_vect;
			dragon_hierarchy["Main Body"].transform.rotation = rotation_transform::between_vector(vec3(0, 0, 1), norm_dir_vect);
			dragon_hierarchy.update_local_to_global_coordinates();

			if (dragon_hierarchy["Body RWing"].global_transform.translation.y < dragon_hierarchy["Main Body"].global_transform.translation.y)
			{
				mat3 rot1 = rotation_transform::convert_quaternion_to_matrix(rotation_transform::between_vector(vec3(0, 0, 1), norm_dir_vect).data);
				mat3 rot2 = rotation_transform::convert_quaternion_to_matrix(rotation_transform::from_axis_angle({ 0,0,1 }, Pi).data);
				dragon_hierarchy["Main Body"].transform.rotation = rotation_transform::from_matrix(rot1 * rot2);
			}
		}
			
		dragon_hierarchy["Main Body"].transform.rotation.data;
	}
}


void Dragon::fly_(float t, float beginning_time, cgp::vec3 where_to, float duration, std::string type)
{
	if (t < beginning_time || t > beginning_time + duration)
		return;
	if (beginning_time - 0.01 < t && beginning_time + 0.01 > t)
	{
		initial_position_temp = get_current_position();
	}
	if (type == "spline_cardinale")
	{
		
	
	
			dragon_hierarchy["Main Body"].transform.translation = compute_spline(t, beginning_time + time_coupure, beginning_time + duration, initial_position_temp, where_to);
			vec3 dir_vect = compute_spline_der(t, beginning_time + time_coupure, beginning_time + duration, initial_position_temp, where_to);
			vec3 norm_dir_vect = 1 / distance(dir_vect) * dir_vect;
			dragon_hierarchy["Main Body"].transform.rotation = rotation_transform::between_vector(vec3(0, 0, 1), norm_dir_vect);
			dragon_hierarchy.update_local_to_global_coordinates();

			if (dragon_hierarchy["Body RWing"].global_transform.translation.y < dragon_hierarchy["Main Body"].global_transform.translation.y)
			{
				mat3 rot1 = rotation_transform::convert_quaternion_to_matrix(rotation_transform::between_vector(vec3(0, 0, 1), norm_dir_vect).data);
				mat3 rot2 = rotation_transform::convert_quaternion_to_matrix(rotation_transform::from_axis_angle({ 0,0,1 }, Pi).data);
				dragon_hierarchy["Main Body"].transform.rotation = rotation_transform::from_matrix(rot1 * rot2);
			}

	}
}
void Dragon::throw_fire(float t, float beginning_time, float duration, Flamme* flame, scene_environment_camera_head& environment)
{
	if (t < beginning_time || t > beginning_time + duration)
		return;
	full_stretching_neck(t, beginning_time, 0.5);
	open_mouth(t, beginning_time+0.3, 0.4);
	flame->set_dir_axis(get_mouth_orientation());
	flame->set_pos(get_mouth_position());
	if (t - beginning_time > 0.6 && t < beginning_time + duration - 0.1)
		flame->draw_flamme(environment);
	close_mouth(t, beginning_time + duration - 0.2, 0.2);

}

Flamme::Flamme(float _cone_radius, float _cone_height, float _speed, float _time_begin)
{
	cone_radius = _cone_radius;
	cone_height = _cone_height;
	speed = _speed;
	time_begin = _time_begin;
	mesh cone = mesh_primitive_cone(cone_radius, cone_height, { 0,0,0 }, { 0,0,1 }, false, 40, 20);
	GLuint const shader = opengl_load_shader("shaders/fire/fire_vert.glsl", "shaders/fire/fire_frag.glsl");
	flamme_mesh_d.initialize(cone, "Flamme");
	flamme_mesh_d.texture = opengl_load_texture_image("assets/texture_flamme_throwing.jpg");
	flamme_mesh_d.shader = shader;
}

void Flamme::set_dir_axis(cgp::vec3 _dir_axis)
{
	dir_axis = _dir_axis;
}

void Flamme::set_pos(cgp::vec3 _pos)
{
	pos = _pos;
}

void Flamme::draw_flamme(scene_environment_camera_head& environment)
{
	//this->flamme_mesh_d.transform.translation = vec3(0., 0., -this->cone_height);
	environment.update_flame(vec4(this->cone_radius, std::abs(this->cone_height), this->speed, this->time_begin));
	this->flamme_mesh_d.transform.rotation = rotation_transform::between_vector({ 0.,0.,-1. }, dir_axis);
	this->flamme_mesh_d.transform.translation = this->cone_height * dir_axis + pos;
	draw(this->flamme_mesh_d, environment);
}