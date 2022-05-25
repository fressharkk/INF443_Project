#include "chevalier.hpp"

using namespace cgp;


void Chevalier_Mesh::make_chevalier()
{
	make_horse();
	make_saddle();
	make_man();
}

void Chevalier_Mesh::make_man_obsolete()
{
	mesh_drawable hat;
	mesh_drawable head;
	mesh_drawable left_boot;
	mesh_drawable right_boot;
	mesh_drawable main_body;
	mesh_drawable necklace;
	mesh_drawable sword;

	hat.initialize(mesh_load_file_obj("assets/French Horseman/cavalier_hat.obj"), "Hat");
	head.initialize(mesh_load_file_obj("assets/French Horseman/cavalier_head.obj"), "Head");
	left_boot.initialize(mesh_load_file_obj("assets/French Horseman/cavalier_left_boot.obj"), "Left Boot");
	right_boot.initialize(mesh_load_file_obj("assets/French Horseman/cavalier_right_boot.obj"), "Right Boot");
	main_body.initialize(mesh_load_file_obj("assets/French Horseman/cavalier_main_body.obj"), "Main Body");
	necklace.initialize(mesh_load_file_obj("assets/French Horseman/cavalier_necklace.obj"), "Necklace");
	sword.initialize(mesh_load_file_obj("assets/French Horseman/cavalier_sword.obj"), "Sword");


	man_drawable.add(main_body);
	man_drawable.add(head, "Main Body");
	man_drawable.add(left_boot, "Main Body");
    man_drawable.add(right_boot, "Main Body");
	man_drawable.add(hat, "Main Body");
	man_drawable.add(necklace, "Hat");
	man_drawable.add(sword, "Main Body");
}


void Chevalier_Mesh::make_man()
{
	mesh_drawable hat;
	mesh_drawable hat_top;
	mesh_drawable head;
	mesh_drawable necklace;
	mesh_drawable sword;

	mesh_drawable botte_gauche;
	mesh_drawable botte_droite;

	mesh_drawable articul_bras_droit;
	mesh_drawable avant_bras_droit;
	mesh_drawable bras_droit;
	mesh_drawable main_droite;

	mesh_drawable avant_bras_gauche;
	mesh_drawable bras_gauche;
	mesh_drawable main_gauche;
	mesh_drawable coude_gauche;

	mesh_drawable torse;
	mesh_drawable ceinture;
	mesh_drawable plumes_casque;

	mesh_drawable hanche_droite;
	mesh_drawable genou_droit;
	mesh_drawable jambe_droite;

	mesh_drawable hanche_gauche;
	mesh_drawable genou_gauche;
	mesh_drawable jambe_gauche;

	hat.initialize(mesh_load_file_obj("assets/Horseman/cavalier_hat.obj"), "Hat");
	hat_top.initialize(mesh_load_file_obj("assets/Horseman/cavalier_hat_top.obj"), "Hat Top");
	head.initialize(mesh_load_file_obj("assets/Horseman/cavalier_head.obj"), "Head");
	necklace.initialize(mesh_load_file_obj("assets/Horseman/cavalier_necklace.obj"), "Necklace");
	sword.initialize(mesh_load_file_obj("assets/Horseman/cavalier_sword.obj"), "Sword");


	botte_gauche.initialize(mesh_load_file_obj("assets/Horseman/cavalier_left_boot.obj"), "Botte Gauche");
	botte_droite.initialize(mesh_load_file_obj("assets/Horseman/cavalier_right_boot.obj"), "Botte Droite");

	articul_bras_droit.initialize(mesh_load_file_obj("assets/Horseman/articulation_bras_droit.obj"), "Articulation Bras Droit");
	avant_bras_droit.initialize(mesh_load_file_obj("assets/Horseman/avant_bras_droit.obj"), "Avant Bras Droit");
	bras_droit.initialize(mesh_load_file_obj("assets/Horseman/bras_droit.obj"), "Bras Droit");
	main_droite.initialize(mesh_load_file_obj("assets/Horseman/main_droite.obj"), "Main Droite");

	avant_bras_gauche.initialize(mesh_load_file_obj("assets/Horseman/avant_bras_gauche.obj"), "Avant Bras Gauche");
	bras_gauche.initialize(mesh_load_file_obj("assets/Horseman/bras_gauche.obj"), "Bras Gauche");
	main_gauche.initialize(mesh_load_file_obj("assets/Horseman/main_gauche.obj"), "Main Gauche");
	coude_gauche.initialize(mesh_load_file_obj("assets/Horseman/coude_gauche.obj"), "Coude Gauche");

	torse.initialize(mesh_load_file_obj("assets/Horseman/torse_dos_nu.obj"), "Torse");
	ceinture.initialize(mesh_load_file_obj("assets/Horseman/ceinture.obj"), "Ceinture");
	plumes_casque.initialize(mesh_load_file_obj("assets/Horseman/plumes_casque.obj"), "Plumes Casque");

	hanche_droite.initialize(mesh_load_file_obj("assets/Horseman/hanche_droite.obj"), "Hanche Droite");
	genou_droit.initialize(mesh_load_file_obj("assets/Horseman/genou_droit.obj"), "Genou Droit");
	jambe_droite.initialize(mesh_load_file_obj("assets/Horseman/jambe_droite.obj"), "Jambe Droite");

	hanche_gauche.initialize(mesh_load_file_obj("assets/Horseman/hanche_gauche.obj"), "Hanche Gauche");
	genou_gauche.initialize(mesh_load_file_obj("assets/Horseman/genou_gauche.obj"), "Genou Gauche");
	jambe_gauche.initialize(mesh_load_file_obj("assets/Horseman/jambe_gauche.obj"), "Jambe Gauche");

	man_drawable.add(torse);
	man_drawable.add(head, "Torse");
	man_drawable.add(hat, "Head");
	man_drawable.add(hat_top, "Hat");
	man_drawable.add(necklace, "Hat");

	//Pour les plumes, comment faire ? temporairement sur le torse
	man_drawable.add(plumes_casque, "Torse");
	man_drawable.add(ceinture, "Torse");

	//Jambes
	man_drawable.add(hanche_gauche, "Ceinture");
	man_drawable.add(jambe_gauche, "Ceinture");
	man_drawable.add(genou_gauche, "Jambe Gauche");
	man_drawable.add(botte_gauche, "Genou Gauche");
	man_drawable.add(hanche_droite, "Ceinture");
	man_drawable.add(jambe_droite, "Hanche Droite");
	man_drawable.add(genou_droit, "Jambe Droite");
	man_drawable.add(botte_droite, "Genou Droit");

	//Bras
	man_drawable.add(bras_droit, "Torse");
	man_drawable.add(articul_bras_droit, "Bras Droit");
	man_drawable.add(avant_bras_droit, "Articulation Bras Droit");
	man_drawable.add(main_droite, "Avant Bras Droit");
	man_drawable.add(sword, "Main Droite");

	man_drawable.add(bras_gauche, "Torse");
	man_drawable.add(coude_gauche, "Bras Gauche");
	man_drawable.add(avant_bras_gauche, "Coude Gauche");
	man_drawable.add(main_gauche, "Avant Bras Gauche");


}

void Chevalier_Mesh::make_saddle()
{

	//Declaring the mesh_drawables for the saddle
	mesh_drawable main_saddle;
	mesh_drawable saddle_top;
	mesh_drawable saddle_sit;
	mesh_drawable saddle_front;
	mesh_drawable saddle_rope_front;
	mesh_drawable saddle_main_ropes;
	mesh_drawable saddle_bottom_ropes;
	mesh_drawable saddle_head_ropes;

	//Initializing the mesh_drawables for the sadle
	main_saddle.initialize(mesh_load_file_obj("assets/French Horseman/cavalier_saddle.obj"), "Main Saddle");
	saddle_top.initialize(mesh_load_file_obj("assets/French Horseman/cavalier_saddle_top.obj"), "Top Saddle");
	saddle_sit.initialize(mesh_load_file_obj("assets/French Horseman/cavalier_saddle_sit.obj"), "Sit Saddle");
	saddle_front.initialize(mesh_load_file_obj("assets/French Horseman/cavalier_saddle_front.obj"), "Front Saddle");
	saddle_rope_front.initialize(mesh_load_file_obj("assets/French Horseman/cavalier_saddle_rope_front.obj"), "Front Rope Saddle");
	saddle_main_ropes.initialize(mesh_load_file_obj("assets/French Horseman/cavalier_saddle_main_ropes.obj"), "Main Ropes Saddle");
	saddle_bottom_ropes.initialize(mesh_load_file_obj("assets/French Horseman/cavalier_saddle_bottom_ropes.obj"), "Bottom Ropes Saddle");
	saddle_head_ropes.initialize(mesh_load_file_obj("assets/French Horseman/cavalier_saddle_head_ropes.obj"), "Head Ropes Saddle");

	//Translations
	vec3 main_ropes_trans = vec3(-6, -8, 2.5);
	saddle_main_ropes.transform.translation = main_ropes_trans;

	//Adding it to the hierarchy
	saddle_drawable.add(main_saddle);
	saddle_drawable.add(saddle_top, "Main Saddle");
	saddle_drawable.add(saddle_sit, "Main Saddle");
	saddle_drawable.add(saddle_front, "Main Saddle");
	saddle_drawable.add(saddle_main_ropes, "Main Saddle", -main_ropes_trans);
	saddle_drawable.add(saddle_rope_front, "Main Saddle");
	saddle_drawable.add(saddle_bottom_ropes, "Main Saddle");
	saddle_drawable.add(saddle_head_ropes, "Main Saddle");
}

void Chevalier_Mesh::make_horse()
{
	//Declaring the mesh_drawables for the Chevalier::horse_drawable body
	mesh_drawable horse_body_up;
	mesh_drawable horse_body_left;
	mesh_drawable horse_body_right;
	mesh_drawable back_right_leg;
	mesh_drawable back_left_leg;
	mesh_drawable front_right_middle_leg;
	mesh_drawable front_right_leg;
	mesh_drawable back_right_middle_leg;
	mesh_drawable front_left_leg;
	mesh_drawable front_left_middle_leg;
	mesh_drawable back_left_middle_leg;
	mesh_drawable tail;

	//Corrections made in order to have a more beautiful Chevalier::horse_drawable
	mesh to_add = mesh_load_file_obj("assets/French Horseman/leg_right_part_2.obj");
	mesh to_add2 = mesh_load_file_obj("assets/French Horseman/cavalier_leg_back_right_middle_to_add.obj");


	//Initializing the mesh_drawables for the Chevalier::horse_drawable body
	horse_body_up.initialize(mesh_load_file_obj("assets/French Horseman/cavalier_horse_body_up.obj"), "1");
	horse_body_left.initialize(mesh_load_file_obj("assets/French Horseman/cavalier_horse_remaining_body_left.obj"), "2");
	horse_body_right.initialize(mesh_load_file_obj("assets/French Horseman/cavalier_remaining_body_right.obj").push_back(to_add2), "3");
	back_right_leg.initialize(mesh_load_file_obj("assets/French Horseman/good_leg_back_2.obj"), "Back Right Leg");
	back_left_leg.initialize(mesh_load_file_obj("assets/French Horseman/cavalier_leg_back_left.obj"), "Back Left Leg");
	front_right_middle_leg.initialize(mesh_load_file_obj("assets/French Horseman/cavalier_leg_front_right_middle.obj").push_back(to_add), "Front Right Middle Leg");
	front_right_leg.initialize(mesh_load_file_obj("assets/French Horseman/good_leg_front.obj"), "Front Right Leg");
	back_right_middle_leg.initialize(mesh_load_file_obj("assets/French Horseman/cavalier_leg_back_right_middle_small.obj"), "Back Right Middle Leg");
	front_left_leg.initialize(mesh_load_file_obj("assets/French Horseman/cavalier_leg_front_left.obj"), "Front Left Leg");
	front_left_middle_leg.initialize(mesh_load_file_obj("assets/French Horseman/leg_front_middle_left.obj"), "Front Left Middle Leg");
	back_left_middle_leg.initialize(mesh_load_file_obj("assets/French Horseman/middle_leg_final.obj"), "Back Left Middle Leg");
	tail.initialize(mesh_load_file_obj("assets/French Horseman/cavalier_horse_tail.obj"), "Tail");

	//Moving pieces in order to get a good rotation 
	vec3 b_r_leg_trans = vec3(3.4, -2.7, 0.8);
	vec3 b_l_leg_trans = vec3(3.4, -2.7, 2.7);
	vec3 f_r_m_leg_trans = vec3(-2.7, -4.7, 1.5);
	vec3 f_r_leg_trans = vec3(-2.7, -2.7, 1.5);
	vec3 b_r_m_leg_trans = vec3(3.4, -5, 0.8);
	vec3 f_l_leg_trans = vec3(-2.7, -2.7, 2.7);
	vec3 f_l_m_leg_trans = vec3(-2.7, -4.7, 2.7);
	vec3 b_l_m_leg_trans = vec3(3.4, -4.7, 2.7);
	vec3 trans_tail = vec3(4.5, -6, 2);

	back_right_leg.transform.translation = b_r_leg_trans;
	back_left_leg.transform.translation = b_l_leg_trans;
	front_right_middle_leg.transform.translation = f_r_m_leg_trans;
	front_right_leg.transform.translation = f_r_leg_trans;
	back_right_middle_leg.transform.translation = b_r_m_leg_trans;
	front_left_leg.transform.translation = f_l_leg_trans;
	front_left_middle_leg.transform.translation = f_l_m_leg_trans;
	back_left_middle_leg.transform.translation = b_l_m_leg_trans;
	tail.transform.translation = trans_tail;

	//Transaltion between legs and middle legs
	vec3 decalage = vec3(0, -2, 0);

	//Adding the Chevalier::horse_drawable body to everything
	horse_drawable.add(horse_body_up);
	horse_drawable.add(horse_body_left, "1");
	horse_drawable.add(horse_body_right, "1");
	horse_drawable.add(front_right_middle_leg, "3", -f_r_m_leg_trans);
	horse_drawable.add(back_right_middle_leg, "3", -b_r_m_leg_trans);
	horse_drawable.add(front_left_middle_leg, "2", -f_l_m_leg_trans);
	horse_drawable.add(back_left_middle_leg, "2", -b_l_m_leg_trans);
	horse_drawable.add(back_right_leg, "Back Right Middle Leg", decalage);
	horse_drawable.add(back_left_leg, "Back Left Middle Leg", decalage);
	horse_drawable.add(front_right_leg, "Front Right Middle Leg", decalage);//, -f_r_leg_trans);
	horse_drawable.add(front_left_leg, "Front Left Middle Leg", decalage);
	horse_drawable.add(tail, "1", -trans_tail + vec3(0.3, 0, 0));

	//Declaring drawables for stirrups
	mesh_drawable left_stirrup;
	mesh_drawable right_stirrup;

	//Initializing stirrups
	left_stirrup.initialize(mesh_load_file_obj("assets/French Horseman/cavalier_left_stirrup.obj"), "left_stirrup");
	right_stirrup.initialize(mesh_load_file_obj("assets/French Horseman/cavalier_right_stirrup.obj"), "right_stirrup");
	horse_drawable.add(left_stirrup, "2");
	horse_drawable.add(right_stirrup, "3");
}

void Chevalier_Mesh::scale(float s)
{
	man_drawable["Torse"].transform.scaling = s;
	saddle_drawable["Main Saddle"].transform.scaling = s;
	horse_drawable["1"].transform.scaling = s;
}

void Chevalier_Mesh::reset()
{
	//Tout RESET
	
	horse_drawable["1"].transform.translation = trans_center;
	man_drawable["Torse"].transform.translation = trans_center;
	saddle_drawable["Main Saddle"].transform.translation = trans_center;
	scale();

	man_drawable.update_local_to_global_coordinates();
	saddle_drawable.update_local_to_global_coordinates();
	horse_drawable.update_local_to_global_coordinates();
}







Chevalier_Mesh* Chevalier::cheva_mesh = new Chevalier_Mesh();
bool Chevalier::is_mesh_initialized = false;

Chevalier::Chevalier(cgp::vec3 _horse_pos)
{
	horse_pos = _horse_pos;
	man_pos = _horse_pos;
	saddle_pos = _horse_pos;
	hit_box = vec3(4, 4.3, 1.6);
	if (!Chevalier::is_mesh_initialized)
		initialize_mesh();

}

Chevalier::Chevalier(cgp::vec3 _horse_pos, cgp::vec3 _saddle_pos, cgp::vec3 _man_pos)
{
	horse_pos = _horse_pos;
	man_pos = _man_pos;
	saddle_pos = _saddle_pos;
	if (!Chevalier::is_mesh_initialized)
		initialize_mesh();
}

void Chevalier::initialize_mesh()
{
	if (!Chevalier::is_mesh_initialized)
	{
		cheva_mesh->make_chevalier();
		is_mesh_initialized = true;
	}
}

void Chevalier::draw_chevalier(scene_environment_camera_head& environment)
{
	if (Chevalier::is_mesh_initialized)
	{
		cheva_mesh->horse_drawable["1"].transform.translation += horse_pos;
		cheva_mesh->saddle_drawable["Main Saddle"].transform.translation += saddle_pos;
		cheva_mesh->man_drawable["Torse"].transform.translation += man_pos;
		cheva_mesh->horse_drawable.update_local_to_global_coordinates();
		cheva_mesh->saddle_drawable.update_local_to_global_coordinates();
		cheva_mesh->man_drawable.update_local_to_global_coordinates();


		draw(cheva_mesh->horse_drawable, environment);
		draw(cheva_mesh->saddle_drawable, environment);
		draw(cheva_mesh->man_drawable, environment);

		cheva_mesh->reset();
	}
}

void Chevalier::mouvement_test()
{
}

vec3 Chevalier::get_center()
{
	return horse_pos;
}

void Chevalier::get_orientation()
{
	
}

cgp::vec3 Chevalier::get_hit_box()
{
	return hit_box;
}
