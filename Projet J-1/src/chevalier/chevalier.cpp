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


	hat.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman/cavalier_hat.obj"), "Hat");
	hat_top.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman/cavalier_hat_top.obj"), "Hat Top");
	hat.texture = opengl_load_texture_image("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman_Texture/hat.jpg", GL_CLAMP_TO_EDGE, GL_MIRRORED_REPEAT);
	hat_top.texture = opengl_load_texture_image("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman_Texture/hat.jpg", GL_CLAMP_TO_EDGE, GL_MIRRORED_REPEAT);

	head.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman/cavalier_head.obj"), "Head");
	head.texture = opengl_load_texture_image("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman_Texture/skin.jpg");
	necklace.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman/cavalier_necklace.obj"), "Necklace");
	necklace.texture = opengl_load_texture_image("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman_Texture/fourrure.jpg");
	sword.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman/cavalier_sword.obj"), "Sword");
	sword.texture = opengl_load_texture_image("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman_Texture/sword.jpg");


	botte_gauche.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman/cavalier_left_boot.obj"), "Botte Gauche");
	botte_gauche.texture = opengl_load_texture_image("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman_Texture/boot.jpg");
	botte_droite.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman/cavalier_right_boot.obj"), "Botte Droite");
	botte_droite.texture = opengl_load_texture_image("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman_Texture/boot.jpg");

	articul_bras_droit.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman/articulation_bras_droit.obj"), "Articulation Bras Droit");
	articul_bras_droit.texture = opengl_load_texture_image("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman_Texture/fourrure.jpg");
	avant_bras_droit.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman/avant_bras_droit.obj"), "Avant Bras Droit");
	avant_bras_droit.texture = opengl_load_texture_image("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman_Texture/fourrure.jpg");
	bras_droit.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman/bras_droit.obj"), "Bras Droit");
	bras_droit.texture = opengl_load_texture_image("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman_Texture/fourrure.jpg");
	main_droite.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman/main_droite.obj"), "Main Droite");
	main_droite.texture = opengl_load_texture_image("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman_Texture/skin.jpg");

	avant_bras_gauche.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman/avant_bras_gauche.obj"), "Avant Bras Gauche");
	avant_bras_gauche.texture = opengl_load_texture_image("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman_Texture/fourrure.jpg");
	bras_gauche.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman/bras_gauche.obj"), "Bras Gauche");
	bras_gauche.texture = opengl_load_texture_image("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman_Texture/fourrure.jpg");
	main_gauche.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman/main_gauche.obj"), "Main Gauche");
	main_gauche.texture = opengl_load_texture_image("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman_Texture/skin.jpg");
	coude_gauche.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman/coude_gauche.obj"), "Coude Gauche");
	coude_gauche.texture = opengl_load_texture_image("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman_Texture/fourrure.jpg");

	torse.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman/torse_dos_nu.obj"), "Torse");
	torse.texture = opengl_load_texture_image("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman_Texture/fourrure.jpg");
	ceinture.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman/ceinture.obj"), "Ceinture");
	ceinture.texture = opengl_load_texture_image("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman_Texture/ceinture.jpg");
	plumes_casque.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman/plumes_casque.obj"), "Plumes Casque");
	plumes_casque.texture = opengl_load_texture_image("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman_Texture/feathers.jpg");

	hanche_droite.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman/hanche_droite.obj"), "Hanche Droite");
	hanche_droite.texture = opengl_load_texture_image("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman_Texture/fourrure_2.jpg");
	genou_droit.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman/genou_droit.obj"), "Genou Droit");
	genou_droit.texture = opengl_load_texture_image("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman_Texture/fourrure_2.jpg");
	jambe_droite.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman/jambe_droite.obj"), "Jambe Droite");
	jambe_droite.texture = opengl_load_texture_image("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman_Texture/fourrure_2.jpg");

	hanche_gauche.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman/hanche_gauche.obj"), "Hanche Gauche");
	hanche_gauche.texture = opengl_load_texture_image("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman_Texture/fourrure_2.jpg");
	genou_gauche.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman/genou_gauche.obj"), "Genou Gauche");
	genou_gauche.texture = opengl_load_texture_image("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman_Texture/fourrure_2.jpg");
	jambe_gauche.initialize(mesh_load_file_obj("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman/jambe_gauche.obj"), "Jambe Gauche");
	jambe_gauche.texture = opengl_load_texture_image("C:/Users/Yassine/Desktop/projet_INF443_Maa_Bar_/assets/Horseman_Texture/fourrure_2.jpg");

	vec3 head_trans = vec3(0, -11, 1.8);

	vec3 genou_gauche_trans = vec3(-1.1, -6.9, 4);
	vec3 hanche_gauche_trans = vec3(-0.3, -8, 2.4);
	vec3 bras_gauche_trans = vec3(-0.25, -10.3, 2.8);
	vec3 coude_gauche_trans = vec3(-0.75, -9.3, 2.9);

	vec3 coude_droit_trans = vec3(0.2, -9.3, 2 * 1.8 - 2.9 + 0.05);
	vec3 hanche_droite_trans = vec3(-0.3, -8, 2 * 1.8 - 2.4 + 0.1);
	vec3 genou_droit_trans = vec3(-1.1, -6.9, 2 * 1.8 - 4 + 0.3);
	vec3 bras_droit_trans = vec3(0.4, -10.3, 2 * 1.8 - 2.8 + 0.4);

	head.transform.translation = head_trans;
	hat.transform.translation = head_trans;
	hat_top.transform.translation = head_trans;
	necklace.transform.translation = head_trans;

	hanche_gauche.transform.translation = hanche_gauche_trans;
	jambe_gauche.transform.translation = hanche_gauche_trans;
	genou_gauche.transform.translation = genou_gauche_trans;
	botte_gauche.transform.translation = genou_gauche_trans;

	hanche_droite.transform.translation = hanche_droite_trans;
	jambe_droite.transform.translation = hanche_droite_trans;
	genou_droit.transform.translation = genou_droit_trans;
	botte_droite.transform.translation = genou_droit_trans;


	bras_gauche.transform.translation = bras_gauche_trans;
	coude_gauche.transform.translation = coude_gauche_trans;
	avant_bras_gauche.transform.translation = coude_gauche_trans;
	main_gauche.transform.translation = coude_gauche_trans;

	bras_droit.transform.translation = bras_droit_trans;
	articul_bras_droit.transform.translation = coude_droit_trans;
	avant_bras_droit.transform.translation = coude_droit_trans;
	main_droite.transform.translation = coude_droit_trans;
	sword.transform.translation = coude_droit_trans;

	man_drawable.add(torse);
	man_drawable.add(head, "Torse", -head_trans);
	man_drawable.add(hat, "Head");
	man_drawable.add(hat_top, "Hat");
	man_drawable.add(necklace, "Hat");

	//Pour les plumes, comment faire ? temporairement sur le torse
	man_drawable.add(plumes_casque, "Torse");
	man_drawable.add(ceinture, "Torse");

	//Jambes
	man_drawable.add(hanche_gauche, "Ceinture", -hanche_gauche_trans);
	man_drawable.add(jambe_gauche, "Hanche Gauche");
	man_drawable.add(genou_gauche, "Jambe Gauche", hanche_gauche_trans - genou_gauche_trans);
	man_drawable.add(botte_gauche, "Genou Gauche");

	man_drawable.add(hanche_droite, "Ceinture", -hanche_droite_trans);
	man_drawable.add(jambe_droite, "Hanche Droite");
	man_drawable.add(genou_droit, "Jambe Droite", hanche_droite_trans - genou_droit_trans);
	man_drawable.add(botte_droite, "Genou Droit");

	//Bras
	man_drawable.add(bras_droit, "Torse", -bras_droit_trans);
	man_drawable.add(articul_bras_droit, "Bras Droit", bras_droit_trans - coude_droit_trans);
	man_drawable.add(avant_bras_droit, "Articulation Bras Droit");
	man_drawable.add(main_droite, "Avant Bras Droit");
	man_drawable.add(sword, "Main Droite");

	man_drawable.add(bras_gauche, "Torse", -bras_gauche_trans);
	man_drawable.add(coude_gauche, "Bras Gauche", bras_gauche_trans - coude_gauche_trans);
	man_drawable.add(avant_bras_gauche, "Coude Gauche");
	man_drawable.add(main_gauche, "Avant Bras Gauche");

	man_drawable.update_local_to_global_coordinates();



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
	main_saddle.texture = opengl_load_texture_image("assets/Horseman_Texture/saddle.jpg");
	saddle_top.initialize(mesh_load_file_obj("assets/French Horseman/cavalier_saddle_top.obj"), "Top Saddle");
	saddle_top.texture = opengl_load_texture_image("assets/Horseman_Texture/saddle.jpg");
	saddle_sit.initialize(mesh_load_file_obj("assets/French Horseman/cavalier_saddle_sit.obj"), "Sit Saddle");
	saddle_sit.texture = opengl_load_texture_image("assets/Horseman_Texture/saddle.jpg");
	saddle_front.initialize(mesh_load_file_obj("assets/French Horseman/cavalier_saddle_front.obj"), "Front Saddle");
	saddle_front.texture = opengl_load_texture_image("assets/Horseman_Texture/saddle.jpg");
	saddle_rope_front.initialize(mesh_load_file_obj("assets/French Horseman/cavalier_saddle_rope_front.obj"), "Front Rope Saddle");
	saddle_rope_front.texture = opengl_load_texture_image("assets/Horseman_Texture/saddle.jpg");
	saddle_main_ropes.initialize(mesh_load_file_obj("assets/French Horseman/cavalier_saddle_main_ropes.obj"), "Main Ropes Saddle");
	saddle_main_ropes.texture = opengl_load_texture_image("assets/Horseman_Texture/saddle.jpg");
	saddle_bottom_ropes.initialize(mesh_load_file_obj("assets/French Horseman/cavalier_saddle_bottom_ropes.obj"), "Bottom Ropes Saddle");
	saddle_bottom_ropes.texture = opengl_load_texture_image("assets/Horseman_Texture/saddle.jpg");
	saddle_head_ropes.initialize(mesh_load_file_obj("assets/French Horseman/cavalier_saddle_head_ropes.obj"), "Head Ropes Saddle");
	saddle_head_ropes.texture = opengl_load_texture_image("assets/Horseman_Texture/saddle.jpg");

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
		horse_body_up.texture = opengl_load_texture_image("assets/Horseman_Texture/horse.jpg");
		horse_body_left.initialize(mesh_load_file_obj("assets/French Horseman/cavalier_horse_remaining_body_left.obj"), "2");
		horse_body_left.texture = opengl_load_texture_image("assets/Horseman_Texture/horse.jpg");
		horse_body_right.initialize(mesh_load_file_obj("assets/French Horseman/cavalier_remaining_body_right.obj").push_back(to_add2), "3");
		horse_body_right.texture = opengl_load_texture_image("assets/Horseman_Texture/horse.jpg");
		back_right_leg.initialize(mesh_load_file_obj("assets/French Horseman/good_leg_back_2.obj"), "Back Right Leg");
		back_right_leg.texture = opengl_load_texture_image("assets/Horseman_Texture/horse.jpg");
		back_left_leg.initialize(mesh_load_file_obj("assets/French Horseman/cavalier_leg_back_left.obj"), "Back Left Leg");
		back_left_leg.texture = opengl_load_texture_image("assets/Horseman_Texture/horse.jpg");
		front_right_middle_leg.initialize(mesh_load_file_obj("assets/French Horseman/cavalier_leg_front_right_middle.obj").push_back(to_add), "Front Right Middle Leg");
		front_right_middle_leg.texture = opengl_load_texture_image("assets/Horseman_Texture/horse.jpg");
		front_right_leg.initialize(mesh_load_file_obj("assets/French Horseman/good_leg_front.obj"), "Front Right Leg");
		front_right_leg.texture = opengl_load_texture_image("assets/Horseman_Texture/horse.jpg");
		back_right_middle_leg.initialize(mesh_load_file_obj("assets/French Horseman/cavalier_leg_back_right_middle_small.obj"), "Back Right Middle Leg");
		back_right_middle_leg.texture = opengl_load_texture_image("assets/Horseman_Texture/horse.jpg");
		front_left_leg.initialize(mesh_load_file_obj("assets/French Horseman/cavalier_leg_front_left.obj"), "Front Left Leg");
		front_left_leg.texture = opengl_load_texture_image("assets/Horseman_Texture/horse.jpg");
		front_left_middle_leg.initialize(mesh_load_file_obj("assets/French Horseman/leg_front_middle_left.obj"), "Front Left Middle Leg");
		front_left_middle_leg.texture = opengl_load_texture_image("assets/Horseman_Texture/horse.jpg");
		back_left_middle_leg.initialize(mesh_load_file_obj("assets/French Horseman/middle_leg_final.obj"), "Back Left Middle Leg");
		back_left_middle_leg.texture = opengl_load_texture_image("assets/Horseman_Texture/horse.jpg");
		tail.initialize(mesh_load_file_obj("assets/French Horseman/cavalier_horse_tail.obj"), "Tail");
		tail.texture = opengl_load_texture_image("assets/Horseman_Texture/horse.jpg");

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
		//horse_drawable.add(left_stirrup, "2");
		//horse_drawable.add(right_stirrup, "3");
	
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
	horse_drawable["1"].transform.rotation = rotation_transform::from_axis_angle({0,-1,0 }, Pi/2);
	man_drawable["Torse"].transform.rotation = rotation_transform::from_axis_angle({ 0,-1,0 }, Pi / 2);
	saddle_drawable["Main Saddle"].transform.rotation = rotation_transform::from_axis_angle({ 0,-1,0 }, Pi / 2);
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

void Chevalier::setPreviousTime(float t)
{
	previousTime = t;
}

void Chevalier::draw_chevalier(scene_environment_camera_head& environment, float(*height_func)(float, float), cgp::vec3(*normal_func)(float, float))
{
	if (Chevalier::is_mesh_initialized)
	{

		vec3 normale = normal_func(horse_pos.x, horse_pos.z);
		vec3 trans_center_ = vec3(0, 0.2*dot(normale,vec3(0,1,0)), 0);

		vec3 last_translation = trans_center_  +vec3(0, height_func(horse_pos.x, horse_pos.z) - horse_pos.y, 0);
		
		horse_pos += last_translation;
		saddle_pos += last_translation;
		man_pos += last_translation;
		cheva_mesh->horse_drawable["1"].transform.translation = horse_pos;
		cheva_mesh->saddle_drawable["Main Saddle"].transform.translation = saddle_pos;
		cheva_mesh->man_drawable["Torse"].transform.translation = man_pos;
		
		auto r = rotation_transform::between_vector({ 0,-1,0 }, normale);/*
		cheva_mesh->horse_drawable["1"].transform.rotation *= r;
		cheva_mesh->saddle_drawable["Main Saddle"].transform.rotation *= r;
		cheva_mesh->man_drawable["Torse"].transform.rotation *= r;*/

		update_chevalier();

		draw(cheva_mesh->horse_drawable, environment);
		draw(cheva_mesh->saddle_drawable, environment);
		draw(cheva_mesh->man_drawable, environment);

		cheva_mesh->reset();
	}
}

void Chevalier::phase_1(float t)
{
	if (t> 0.95 && t < 1.0)
	{
		phase_1_speed = base_speed + 0.05 * base_speed*rand_interval(-1, 1);
		phase_1_duration = std::abs(this->horse_pos.z - 35) / phase_1_speed;
		return;
	}
	
	trot(normalize(vec3(0, 0, std::abs(this->horse_pos.z - 35))), t, 1, phase_1_duration, phase_1_speed);
}

void Chevalier::update_chevalier()
{
	cheva_mesh->horse_drawable.update_local_to_global_coordinates();
	cheva_mesh->man_drawable.update_local_to_global_coordinates();
	cheva_mesh->saddle_drawable.update_local_to_global_coordinates();
}

void Chevalier::mouvement_test()
{
}

vec3 Chevalier::get_center()
{
	return horse_pos;
}


cgp::vec3 Chevalier::get_vision_pos()
{
	return this->cheva_mesh->man_drawable["Head"].global_transform.translation + get_vision_orientation().data* vec3(0.2, 3.5, -0.6)  + man_pos;
}

rotation_transform Chevalier::get_vision_orientation()
{
	return this->cheva_mesh->man_drawable["Head"].global_transform.rotation;
}
cgp::vec3 Chevalier::get_hit_box()
{
	return hit_box;
}

cgp::vec4 Chevalier::getLegUpAngles()
{
	float left_back_leg;
	float right_back_leg;
	float left_front_leg;
	float right_front_leg;
	auto r1 = cheva_mesh->horse_drawable["Back Left Middle Leg"].transform.rotation.data;
	auto r2 = cheva_mesh->horse_drawable["Back Right Middle Leg"].transform.rotation.data;
	auto r3 = cheva_mesh->horse_drawable["Front Left Middle Leg"].transform.rotation.data;
	auto r4 = cheva_mesh->horse_drawable["Front Right Middle Leg"].transform.rotation.data;
	vec3 a1, a2, a3, a4;
	rotation_transform::convert_quaternion_to_axis_angle(r1, a1, left_back_leg);
	rotation_transform::convert_quaternion_to_axis_angle(r2, a2, right_back_leg);
	rotation_transform::convert_quaternion_to_axis_angle(r3, a3, left_front_leg);
	rotation_transform::convert_quaternion_to_axis_angle(r4, a4, right_front_leg);
	if (std::abs(a1.z + 1) < 0.01)
		left_back_leg = -left_back_leg;
	if (std::abs(a2.z + 1) < 0.01)
		right_back_leg = -right_back_leg;
	if (std::abs(a3.z + 1) < 0.01)
		left_front_leg = -left_front_leg;
	if (std::abs(a4.z + 1) < 0.01)
		right_front_leg = -right_front_leg;
	return vec4(left_back_leg, right_back_leg, left_front_leg, right_front_leg);

}

cgp::vec4 Chevalier::getLegDownAngles()
{
	float left_back_leg;
	float right_back_leg;
	float left_front_leg;
	float right_front_leg;
	auto r1 = cheva_mesh->horse_drawable["Back Left Leg"].transform.rotation.data;
	auto r2 = cheva_mesh->horse_drawable["Back Right Leg"].transform.rotation.data;
	auto r3 = cheva_mesh->horse_drawable["Front Left Leg"].transform.rotation.data;
	auto r4 = cheva_mesh->horse_drawable["Front Right Leg"].transform.rotation.data;
	vec3 a1, a2, a3, a4;
	rotation_transform::convert_quaternion_to_axis_angle(r1, a1, left_back_leg);
	rotation_transform::convert_quaternion_to_axis_angle(r2, a2, right_back_leg);
	rotation_transform::convert_quaternion_to_axis_angle(r3, a3, left_front_leg);
	rotation_transform::convert_quaternion_to_axis_angle(r4, a4, right_front_leg);
	if (std::abs(a1.z + 1) < 0.01)
		left_back_leg = -left_back_leg;
	if (std::abs(a2.z + 1) < 0.01)
		right_back_leg = -right_back_leg;
	if (std::abs(a3.z + 1) < 0.01)
		left_front_leg = -left_front_leg;
	if (std::abs(a4.z + 1) < 0.01)
		right_front_leg = -right_front_leg;
	return vec4(left_back_leg, right_back_leg, left_front_leg, right_front_leg);
}

void Chevalier::flee()
{
}

rotation_transform Chevalier::get_horse_rotation()
{
	return cheva_mesh->horse_drawable["1"].transform.rotation;
}

void Chevalier::move_tail(float t, float beginning_time, float duration)
{
	if (t < beginning_time)
		return;
	if (t - beginning_time > duration)
		return;
	
	t -= beginning_time;
	cheva_mesh->horse_drawable["Tail"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,-1 }, 0.4+0.5*sin(3*t)*sin(3*t));

}
void Chevalier::trot_step_1(float t, float beginning_time, float duration)
{
	if (t < beginning_time)
		return;
	if (t - beginning_time > duration)
		return;

	if (std::abs(t - beginning_time) < 0.01)
	{
		leg_angles_down = getLegDownAngles();
		leg_angles_up = getLegUpAngles();
	}


	float t1 = 0.9 * Pi / 2;
	float t2 = -0.7 * Pi / 2;
	float t3 = Pi / 10;
	float t4 = 0.1 * Pi / 2;
	float t5 = 0;
	float t6 = 0;
	float t7 = 0;
	float t8 = 0;

	float ratio = (t - beginning_time) / duration;

	cheva_mesh->horse_drawable["Front Right Middle Leg"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, leg_angles_up.w + ratio*(t1-leg_angles_up.w));
	cheva_mesh->horse_drawable["Front Right Leg"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, leg_angles_down.w + ratio * (t2 - leg_angles_down.w));

	cheva_mesh->horse_drawable["Back Left Middle Leg"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, leg_angles_up.x + ratio * (t3 - leg_angles_up.x));
	cheva_mesh->horse_drawable["Back Left Leg"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, leg_angles_down.x + ratio * (t4 - leg_angles_down.x));

	cheva_mesh->horse_drawable["Front Left Middle Leg"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, leg_angles_up.z + ratio * (t5 - leg_angles_up.z));
	cheva_mesh->horse_drawable["Front Left Leg"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, leg_angles_down.z + ratio * (t6 - leg_angles_down.z));

	cheva_mesh->horse_drawable["Back Right Middle Leg"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, leg_angles_up.y + ratio * (t7 - leg_angles_up.y));
	cheva_mesh->horse_drawable["Back Right Leg"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, leg_angles_down.y + ratio * (t8 - leg_angles_down.y));
}

void Chevalier::trot_step_2(float t, float beginning_time, float duration)
{
	if (t < beginning_time)
		return;
	if (t - beginning_time > duration)
		return;

	if (std::abs(t - beginning_time) < 0.01)
	{
		leg_angles_down = getLegDownAngles();
		leg_angles_up = getLegUpAngles();
	}


	float t1 = Pi / 3;
	float t2 = -Pi / 10;
	float t3 = Pi / 6;
	float t4 = 0.1 * Pi / 2;
	float t5 = Pi / 6;
	float t6 = -0.4 * Pi;
	float t7 = Pi / 12;
	float t8 = -Pi / 6;

	float ratio = (t - beginning_time) / duration;

	cheva_mesh->horse_drawable["Front Right Middle Leg"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, leg_angles_up.w + ratio * (t1 - leg_angles_up.w));
	cheva_mesh->horse_drawable["Front Right Leg"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, leg_angles_down.w + ratio * (t2 - leg_angles_down.w));

	cheva_mesh->horse_drawable["Back Left Middle Leg"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, leg_angles_up.x + ratio * (t3 - leg_angles_up.x));
	cheva_mesh->horse_drawable["Back Left Leg"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, leg_angles_down.x + ratio * (t4 - leg_angles_down.x));

	cheva_mesh->horse_drawable["Front Left Middle Leg"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, leg_angles_up.z + ratio * (t5 - leg_angles_up.z));
	cheva_mesh->horse_drawable["Front Left Leg"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, leg_angles_down.z + ratio * (t6 - leg_angles_down.z));

	cheva_mesh->horse_drawable["Back Right Middle Leg"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, leg_angles_up.y + ratio * (t7 - leg_angles_up.y));
	cheva_mesh->horse_drawable["Back Right Leg"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, leg_angles_down.y + ratio * (t8 - leg_angles_down.y));
}

void Chevalier::trot_step_3(float t, float beginning_time, float duration)
{
	if (t < beginning_time)
		return;
	if (t - beginning_time > duration)
		return;

	if (std::abs(t - beginning_time) < 0.01)
	{
		leg_angles_down = getLegDownAngles();
		leg_angles_up = getLegUpAngles();
	}

	float t1 = -Pi / 24;
	float t2 = -Pi / 20;
	float t3 = -Pi / 12;
	float t4 = 0.1 * Pi / 2;
	float t5 = 0.9 * Pi / 2;
	float t6 = -0.4 * Pi;
	float t7 = -0;
	float t8 = 0.7 * Pi / 3;

	float ratio = (t - beginning_time) / duration;

	cheva_mesh->horse_drawable["Front Right Middle Leg"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, leg_angles_up.w + ratio * (t1 - leg_angles_up.w));
	cheva_mesh->horse_drawable["Front Right Leg"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, leg_angles_down.w + ratio * (t2 - leg_angles_down.w));

	cheva_mesh->horse_drawable["Back Left Middle Leg"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, leg_angles_up.x + ratio * (t3 - leg_angles_up.x));
	cheva_mesh->horse_drawable["Back Left Leg"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, leg_angles_down.x + ratio * (t4 - leg_angles_down.x));

	cheva_mesh->horse_drawable["Front Left Middle Leg"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, leg_angles_up.z + ratio * (t5 - leg_angles_up.z));
	cheva_mesh->horse_drawable["Front Left Leg"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, leg_angles_down.z + ratio * (t6 - leg_angles_down.z));

	cheva_mesh->horse_drawable["Back Right Middle Leg"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, leg_angles_up.y + ratio * (t7 - leg_angles_up.y));
	cheva_mesh->horse_drawable["Back Right Leg"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, leg_angles_down.y + ratio * (t8 - leg_angles_down.y));

}

void Chevalier::trot_step_4(float t, float beginning_time, float duration)
{
	if (t < beginning_time)
		return;
	if (t - beginning_time > duration)
		return;

	if (std::abs(t - beginning_time) < 0.01)
	{
		leg_angles_down = getLegDownAngles();
		leg_angles_up = getLegUpAngles();
	}


	float t1 = Pi/6;
	float t2 = -0.6 * Pi;
	float t3 = -0.7 * Pi / 2;
	float t4 = 0.8 * Pi / 2;
	float t5 = 0.2 * Pi / 2;
	float t6 = -0.1 * Pi;
	float t7 = 0.2 * Pi;
	float t8 = Pi / 40;

	float ratio = (t - beginning_time) / duration;

	cheva_mesh->horse_drawable["Front Right Middle Leg"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, leg_angles_up.w + ratio * (t1 - leg_angles_up.w));
	cheva_mesh->horse_drawable["Front Right Leg"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, leg_angles_down.w + ratio * (t2 - leg_angles_down.w));

	cheva_mesh->horse_drawable["Back Left Middle Leg"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, leg_angles_up.x + ratio * (t3 - leg_angles_up.x));
	cheva_mesh->horse_drawable["Back Left Leg"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, leg_angles_down.x + ratio * (t4 - leg_angles_down.x));

	cheva_mesh->horse_drawable["Front Left Middle Leg"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, leg_angles_up.z + ratio * (t5 - leg_angles_up.z));
	cheva_mesh->horse_drawable["Front Left Leg"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, leg_angles_down.z + ratio * (t6 - leg_angles_down.z));

	cheva_mesh->horse_drawable["Back Right Middle Leg"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, leg_angles_up.y + ratio * (t7 - leg_angles_up.y));
	cheva_mesh->horse_drawable["Back Right Leg"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, leg_angles_down.y + ratio * (t8 - leg_angles_down.y));

}

void Chevalier::trot(cgp::vec3 dir, float t, float beginning_time, float duration, float walking_speed, float _step_duration)
{
	if (t < beginning_time)
		return;
	if (t > duration + beginning_time)
		return;
	if (std::abs(t - beginning_time) < 0.01)
		setPreviousTime(beginning_time);

	if (std::abs(_step_duration + 1) < 0.001)
		_step_duration = step_duration;

	float act_t = std::fmod(t - beginning_time, _step_duration);


	trot_step_1(act_t, 0, _step_duration / 4);
	trot_step_2(act_t, _step_duration / 4, _step_duration / 4);
	trot_step_3(act_t, _step_duration / 2, _step_duration / 4);
	trot_step_4(act_t, 3 * _step_duration / 4, _step_duration / 4);
	move_tail(t, 0, duration);
	man_jump_trot(t, beginning_time, duration);
	//end_trot(t, beginning_time + duration - _step_duration / 2, _step_duration / 2);
	
	if (std::abs(walking_speed + 1) < 0.001)
		walking_speed = walking_speed;

	horse_pos += (walking_speed * (t - previousTime) *  dir);
	saddle_pos += (walking_speed * (t - previousTime) *  dir);
	man_pos += (walking_speed * (t - previousTime) * dir);
	setPreviousTime(t);
}

void Chevalier::man_jump_trot(float t, float beginning_time, float duration)
{
	if (t < beginning_time)
		return;
	if (t - beginning_time > duration)
		return;
	t = (t - beginning_time);

	cheva_mesh->man_drawable["Torse"].transform.translation += vec3(0.1 * sin(ropes_speed * t) * sin(ropes_speed * t), 0.2*sin(ropes_speed * t) * sin(ropes_speed * t), 0);
	cheva_mesh->saddle_drawable["Main Ropes Saddle"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, -0.2 * sin(ropes_speed * t) * sin(ropes_speed * t));
}