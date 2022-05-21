#include "dragon.hpp"


using namespace cgp;


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


	neck_head.initialize(mesh_load_file_obj("assets/Dragon/neck_dragon_head.obj"), "Neck Head");
	neck_low.initialize(mesh_load_file_obj("assets/Dragon/neck_dragon_low.obj"), "Neck Low");
	cornes.initialize(mesh_load_file_obj("assets/Dragon/Cornes_Dragon.obj"), "Cornes");
	auto texture2 = opengl_load_texture_image("assets/Dragon/dragon_texture_2.jpg", GL_CLAMP_TO_EDGE, GL_MIRRORED_REPEAT);
	auto texture = opengl_load_texture_image("assets/Dragon/dragon_texture.png", GL_CLAMP_TO_EDGE, GL_MIRRORED_REPEAT);

	cornes.texture = texture;
	front_right_leg.initialize(mesh_load_file_obj("assets/Dragon/cuisse_avant_droit.obj"), "Front Right Leg");
	front_left_leg.initialize(mesh_load_file_obj("assets/Dragon/cuisse_avant_gauche.obj"), "Front Left Leg");
	back_left_leg.initialize(mesh_load_file_obj("assets/Dragon/cuisse_arriere_gauche.obj"), "Back Left Leg");
	back_right_leg.initialize(mesh_load_file_obj("assets/Dragon/cuisse_arriere_droite.obj"), "Back Right Leg");
	tail.initialize(mesh_load_file_obj("assets/Dragon/dragon_tail.obj"), "Dragon Tail");
	inner_head.initialize(mesh_load_file_obj("assets/Dragon/Inner_head_dragon.obj"), "Inner Head");
	inner_head.shading.color = vec3(1, 1, 1);
	main_body.initialize(mesh_load_file_obj("assets/Dragon/dragon_body_nothing_only.obj"), "Main Body");
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
	vec3 b_right_foot_trans = vec3(0.7, -1.6, 0.6);
	vec3 b_right_foot_low_trans = vec3(0.7, -1, 0.05);
	vec3 b_left_foot_low_trans = vec3(-0.8, -1, 0);

	front_left_leg.transform.translation = f_left_leg_trans;
	griffes_pied_avant_gauche.transform.translation = f_left_foot_trans;
	front_right_leg.transform.translation = f_right_leg_trans;
	griffes_pied_avant_droit.transform.translation = f_right_foot_trans;
	back_right_leg.transform.translation = b_right_leg_trans;
	griffes_pied_arriere_droit.transform.translation = b_right_foot_low_trans;
	back_left_leg.transform.translation = b_left_leg_trans;
	griffes_pied_arriere_gauche.transform.translation = b_left_foot_low_trans;
	neck_low.transform.translation = neck_low_trans;
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

	//test = back_left_foot_low;

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


	dragon_hierarchy["Main Body"].transform.scaling = 0.5;
	//dragon["Main Body"].transform.translation = vec3(5,0,0);
	dragon_hierarchy.update_local_to_global_coordinates();
	//.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, 3.14 / 2);
//dragon.update_local_to_global_coordinates();
//dragon_hierarchy.add(l_wing_mid, "LeftWingEnd");
//dragon_hierarchy.add(l_wing_mid, "Left Wing End");
}

void Dragon::draw_dragon(scene_environment_camera_head& environment)
{
	draw(dragon_hierarchy, environment);
}