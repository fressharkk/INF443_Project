#include "soldat.hpp"

using namespace cgp;

void Soldat_Mesh::make_soldat()
{
	//Ajouter des yeux 

	mesh_drawable accroches_cote;
	mesh_drawable accroches_epaules;
	mesh_drawable avant_bras_droit;
	mesh_drawable avant_bras_gauche;
	mesh_drawable bas_capuche;
	mesh_drawable bas_tunique;
	mesh_drawable bas_tunique_2;
	mesh_drawable bassin;
	mesh_drawable botte_droite;
	mesh_drawable botte_gauche;
	mesh_drawable bras_droit;
	mesh_drawable bras_gauche;
	mesh_drawable ceinture_basse;
	mesh_drawable ceinture_haute;
	mesh_drawable cou;
	mesh_drawable coude_droit;
	mesh_drawable coude_gauche;
	mesh_drawable epaule_droite;
	mesh_drawable epaule_gauche;
	mesh_drawable epaulette_droite;
	mesh_drawable epaulette_gauche;
	mesh_drawable eyes;
	mesh_drawable gant_droit;
	mesh_drawable gant_gauche;
	mesh_drawable genou_droit;
	mesh_drawable genou_gauche;
	mesh_drawable genouillere_gauche;
	mesh_drawable genouillere_droite;
	mesh_drawable helmet;
	mesh_drawable jambe_droite;
	mesh_drawable jambe_gauche;
	mesh_drawable mollet_droit;
	mesh_drawable mollet_gauche;
	mesh_drawable protection_bras_droit;
	mesh_drawable protection_bras_gauche;
	mesh_drawable protection_ceinture;
	mesh_drawable protection_coude_droit;
	mesh_drawable protection_coude_gauche;
	mesh_drawable tete;
	mesh_drawable tibia_droit;
	mesh_drawable tibia_gauche;
	mesh_drawable torse;

	vec3 grey_color = vec3(0.6, 0.6, 0.6);
	vec3 grey_color_2 = vec3(0.55, 0.55, 0.55);
	auto texture_armure = opengl_load_texture_image("assets/Soldat_Texture/Armure.png", GL_REPEAT);
	auto texture_vetements = opengl_load_texture_image("assets/Soldat_Texture/vetements.png", GL_REPEAT);


//eyes.texture = opengl_load_texture_image("assets/eye_texture.jpg");


	accroches_cote.initialize(mesh_load_file_obj("assets/Soldat/accroches_cote.obj"), "Accroches Cote");
	accroches_cote.texture = texture_vetements;
	accroches_epaules.initialize(mesh_load_file_obj("assets/Soldat/accroches_epaules.obj"), "Accroches Epaules");
	accroches_epaules.texture = texture_vetements;
	avant_bras_droit.initialize(mesh_load_file_obj("assets/Soldat/avant_bras_droit.obj"), "Avant Bras Droit");
	avant_bras_droit.texture = texture_armure;
	avant_bras_gauche.initialize(mesh_load_file_obj("assets/Soldat/avant_bras_gauche.obj"), "Avant Bras Gauche");
	avant_bras_gauche.texture = texture_armure;
	bas_capuche.initialize(mesh_load_file_obj("assets/Soldat/bas_capuche.obj"), "Bas Capuche");
	bas_capuche.texture = texture_armure;
	bas_tunique.initialize(mesh_load_file_obj("assets/Soldat/bas_tunique.obj"), "Bas Tunique");
	bas_tunique.texture = texture_vetements;
	bas_tunique_2.initialize(mesh_load_file_obj("assets/Soldat/bas_tunique_2.obj"), "Bas Tunique 2");
	bas_tunique_2.texture = texture_armure;
	bassin.initialize(mesh_load_file_obj("assets/Soldat/bassin.obj"), "Bassin");
	bassin.texture = texture_vetements;
	botte_droite.initialize(mesh_load_file_obj("assets/Soldat/botte_droite.obj"), "Botte Droite");
	botte_droite.texture = texture_vetements;
	botte_gauche.initialize(mesh_load_file_obj("assets/Soldat/botte_gauche.obj"), "Botte Gauche");
	botte_gauche.texture = texture_vetements;
	bras_droit.initialize(mesh_load_file_obj("assets/Soldat/bras_droit.obj"), "Bras Droit");
	bras_droit.texture = texture_armure;
	bras_gauche.initialize(mesh_load_file_obj("assets/Soldat/bras_gauche.obj"), "Bras Gauche");
	bras_gauche.texture = texture_armure;
	ceinture_basse.initialize(mesh_load_file_obj("assets/Soldat/ceinture_basse.obj"), "Ceinture Basse");
	ceinture_basse.texture = texture_armure;
	ceinture_haute.initialize(mesh_load_file_obj("assets/Soldat/ceinture_haute.obj"), "Ceinture Haute");
	ceinture_haute.texture = texture_vetements;
	cou.initialize(mesh_load_file_obj("assets/Soldat/cou.obj"), "Cou");
	cou.texture = texture_vetements;
	coude_droit.initialize(mesh_load_file_obj("assets/Soldat/coude_droit.obj"), "Coude Droit");
	coude_droit.texture = texture_armure;
	coude_gauche.initialize(mesh_load_file_obj("assets/Soldat/coude_gauche.obj"), "Coude Gauche");
	coude_gauche.texture = texture_armure;
	epaule_droite.initialize(mesh_load_file_obj("assets/Soldat/epaule_droite.obj"), "Epaule Droite");
	epaule_droite.texture = texture_armure;
	epaule_gauche.initialize(mesh_load_file_obj("assets/Soldat/epaule_gauche.obj"), "Epaule Gauche");
	epaule_gauche.texture = texture_armure;
	epaulette_droite.initialize(mesh_load_file_obj("assets/Soldat/epaulette_droit.obj"), "Epaulette Droite");
	epaulette_droite.texture = texture_armure;
	epaulette_gauche.initialize(mesh_load_file_obj("assets/Soldat/epaulette_gauche.obj"), "Epaulette Gauche");
	epaulette_gauche.texture = texture_armure;
	gant_droit.initialize(mesh_load_file_obj("assets/Soldat/gant_droit.obj"), "Gant Droit");
	gant_droit.texture = texture_armure;
	gant_gauche.initialize(mesh_load_file_obj("assets/Soldat/gant_gauche.obj"), "Gant Gauche");
	gant_gauche.texture = texture_armure;
	genou_droit.initialize(mesh_load_file_obj("assets/Soldat/genou_droit.obj"), "Genou Droit");
	genou_droit.texture = texture_armure;
	genou_gauche.initialize(mesh_load_file_obj("assets/Soldat/genou_gauche.obj"), "Genou Gauche");
	genou_gauche.texture = texture_armure;
	genouillere_droite.initialize(mesh_load_file_obj("assets/Soldat/genouillere_droite.obj"), "Genouillere Droite");
	genouillere_droite.texture = texture_armure;
	genouillere_gauche.initialize(mesh_load_file_obj("assets/Soldat/genouillere_gauche.obj"), "Genouillere Gauche");
	genouillere_gauche.texture = texture_armure;
	helmet.initialize(mesh_load_file_obj("assets/Soldat/helmet.obj"), "Casque");
	helmet.texture = texture_armure;
	jambe_droite.initialize(mesh_load_file_obj("assets/Soldat/jambe_droite.obj"), "Jambe Droite");
	jambe_droite.texture = texture_vetements;
	jambe_gauche.initialize(mesh_load_file_obj("assets/Soldat/jambe_gauche.obj"), "Jambe Gauche");
	jambe_gauche.texture = texture_vetements;
	mollet_droit.initialize(mesh_load_file_obj("assets/Soldat/mollet_droit.obj"), "Mollet Droit");
	mollet_droit.texture = texture_vetements;
	mollet_gauche.initialize(mesh_load_file_obj("assets/Soldat/mollet_gauche.obj"), "Mollet Gauche");
	mollet_gauche.texture = texture_vetements;
	protection_bras_droit.initialize(mesh_load_file_obj("assets/Soldat/protection_bras_droit.obj"), "Protection Bras Droit");
	protection_bras_droit.texture = texture_vetements;
	protection_bras_gauche.initialize(mesh_load_file_obj("assets/Soldat/protection_bras_gauche.obj"), "Protection Bras Gauche");
	protection_bras_droit.texture = texture_vetements;
	protection_ceinture.initialize(mesh_load_file_obj("assets/Soldat/protection_ceinture.obj"), "Protection Ceinture");
	protection_ceinture.texture = texture_armure;
	protection_coude_droit.initialize(mesh_load_file_obj("assets/Soldat/protection_coude_droit.obj"), "Protection Coude Droit");
	protection_coude_droit.texture = texture_vetements;
	protection_coude_gauche.initialize(mesh_load_file_obj("assets/Soldat/protection_coude_gauche.obj"), "Protection Coude Gauche");
	protection_coude_gauche.texture = texture_vetements;
	tete.initialize(mesh_load_file_obj("assets/Soldat/tete.obj"), "Tete");
	tete.texture = texture_armure;
	tibia_droit.initialize(mesh_load_file_obj("assets/Soldat/tibia_droit.obj"), "Tibia Droit");
	tibia_droit.texture = texture_armure;
	tibia_gauche.initialize(mesh_load_file_obj("assets/Soldat/tibia_gauche.obj"), "Tibia Gauche");
	tibia_gauche.texture = texture_armure;
	torse.initialize(mesh_load_file_obj("assets/Soldat/torse.obj"), "Torse");
	torse.texture = texture_armure;
	
	eyes.initialize(mesh_primitive_ellipsoid(vec3(0.3*0.1, 0.05*0.2, 0.1*0.3), vec3(-0.03, 1.72, 0.06)).push_back(mesh_primitive_ellipsoid(vec3(0.3 * 0.1, 0.05 * 0.2, 0.1 * 0.3), vec3(0.03, 1.72, 0.06))), "Eyes");

	vec3 coude_gauche_trans = vec3(-0.4, -1.25, 0.15);
	vec3 coude_droit_trans = vec3(0.4, -1.25, 0.15);
	vec3 epaule_gauche_trans = vec3(-0.2, -1.4, 0.1);
	vec3 epaule_droite_trans = vec3(0.2, -1.4, 0.1);
	vec3 jambe_droite_trans = vec3(0.1, -0.9, 0.1);
	vec3 genou_droit_trans = vec3(0.15, -0.55, 0.05);
	vec3 genou_gauche_trans = vec3(-0.15, -0.55, 0.05);
	vec3 jambe_gauche_trans = vec3(-0.1, -0.9, 0.1);
	vec3 tete_trans = vec3(0, -1.6, 0);

	coude_gauche.transform.translation = coude_gauche_trans;
	epaule_gauche.transform.translation = epaule_gauche_trans;
	epaulette_gauche.transform.translation = epaule_gauche_trans;
	bras_gauche.transform.translation = epaule_gauche_trans;
	protection_coude_gauche.transform.translation = coude_gauche_trans;
	avant_bras_gauche.transform.translation = coude_gauche_trans;
	gant_gauche.transform.translation = coude_gauche_trans;

	coude_droit.transform.translation = coude_droit_trans;
	epaule_droite.transform.translation = epaule_droite_trans;
	epaulette_droite.transform.translation = epaule_droite_trans;
	bras_droit.transform.translation = epaule_droite_trans;
	protection_coude_droit.transform.translation = coude_droit_trans;
	avant_bras_droit.transform.translation = coude_droit_trans;
	gant_droit.transform.translation = coude_droit_trans;

	jambe_droite.transform.translation = jambe_droite_trans;
	genou_droit.transform.translation = genou_droit_trans;
	mollet_droit.transform.translation = genou_droit_trans;
	genouillere_droite.transform.translation = genou_droit_trans;
	botte_droite.transform.translation = genou_droit_trans;
	tibia_droit.transform.translation = genou_droit_trans;

	jambe_gauche.transform.translation = jambe_gauche_trans;
	genou_gauche.transform.translation = genou_gauche_trans;
	mollet_gauche.transform.translation = genou_gauche_trans;
	genouillere_gauche.transform.translation = genou_gauche_trans;
	botte_gauche.transform.translation = genou_gauche_trans;
	tibia_gauche.transform.translation = genou_gauche_trans;

	tete.transform.translation = tete_trans;
	helmet.transform.translation = tete_trans;
	eyes.transform.translation = tete_trans;

	//Creation de la hierarchie
	soldat_to_draw.add(torse);
	soldat_to_draw.add(ceinture_haute, "Torse");
	soldat_to_draw.add(ceinture_basse, "Ceinture Haute");
	soldat_to_draw.add(protection_ceinture, "Ceinture Basse");
	soldat_to_draw.add(bassin, "Ceinture Basse");
	soldat_to_draw.add(bas_tunique, "Bassin");
	soldat_to_draw.add(bas_tunique_2, "Bassin");
	
	//Jambe Gauche
	soldat_to_draw.add(jambe_gauche, "Bassin", -jambe_gauche_trans);
	soldat_to_draw.add(genou_gauche, "Jambe Gauche", jambe_gauche_trans - genou_gauche_trans);
	soldat_to_draw.add(mollet_gauche, "Genou Gauche");
	soldat_to_draw.add(genouillere_gauche, "Genou Gauche");
	soldat_to_draw.add(botte_gauche, "Mollet Gauche");
	soldat_to_draw.add(tibia_gauche, "Mollet Gauche");

	//Jambe Droite
	soldat_to_draw.add(jambe_droite, "Bassin", -jambe_droite_trans);
	soldat_to_draw.add(genou_droit, "Jambe Droite", jambe_droite_trans - genou_droit_trans);
	soldat_to_draw.add(mollet_droit, "Genou Droit");
	soldat_to_draw.add(genouillere_droite, "Genou Droit");
	soldat_to_draw.add(botte_droite, "Mollet Droit");
	soldat_to_draw.add(tibia_droit, "Mollet Droit");

	//Bras Gauche
	soldat_to_draw.add(epaule_gauche, "Torse", -epaule_gauche_trans);
	soldat_to_draw.add(epaulette_gauche, "Epaule Gauche");
	soldat_to_draw.add(bras_gauche, "Epaule Gauche");
	soldat_to_draw.add(coude_gauche, "Bras Gauche", epaule_gauche_trans - coude_gauche_trans);
	soldat_to_draw.add(protection_coude_gauche, "Coude Gauche");
	soldat_to_draw.add(avant_bras_gauche, "Coude Gauche");
	soldat_to_draw.add(gant_gauche, "Avant Bras Gauche");

	//Bras Droit
	soldat_to_draw.add(epaule_droite, "Torse", -epaule_droite_trans);
	soldat_to_draw.add(epaulette_droite, "Epaule Droite");
	soldat_to_draw.add(bras_droit, "Epaule Droite");
	soldat_to_draw.add(coude_droit, "Bras Droit", epaule_droite_trans - coude_droit_trans);
	soldat_to_draw.add(protection_coude_droit, "Coude Droit");
	soldat_to_draw.add(avant_bras_droit, "Coude Droit");
	soldat_to_draw.add(gant_droit, "Avant Bras Droit");

	soldat_to_draw.add(cou, "Torse");
	soldat_to_draw.add(bas_capuche, "Cou");
	soldat_to_draw.add(tete, "Bas Capuche", -tete_trans);
	soldat_to_draw.add(helmet, "Tete");
	soldat_to_draw.add(eyes, "Tete");

	soldat_to_draw.add(accroches_cote, "Torse");
	soldat_to_draw.add(accroches_epaules, "Torse");
	

	soldat_to_draw.update_local_to_global_coordinates();
}

void Soldat_Mesh::reset()
{
	soldat_to_draw["Torse"].transform.translation = trans_center;
	soldat_to_draw.update_local_to_global_coordinates();
}

Soldat_Mesh* Soldat::soldat_mesh = new Soldat_Mesh();
bool Soldat::is_mesh_initialized = false;

Soldat::Soldat(cgp::vec3 pos_)
{
	pos = pos_;
	hit_box = vec3(0.6, 2, 0.2);
	if (!Soldat::is_mesh_initialized)
		initialize_mesh();
}

void Soldat::initialize_mesh()
{
	if (!Soldat::is_mesh_initialized)
	{
		soldat_mesh->make_soldat();
		is_mesh_initialized = true;
	}
}

void Soldat::draw_soldat(scene_environment_camera_head& environment)
{
	if (Soldat::is_mesh_initialized)
	{
		soldat_mesh->soldat_to_draw["Torse"].transform.translation += pos;
		update_soldat();
	
		draw(soldat_mesh->soldat_to_draw, environment);
		soldat_mesh->reset();
	}
}

void Soldat::update_soldat()
{
	soldat_mesh->soldat_to_draw.update_local_to_global_coordinates();
}

vec3 Soldat::get_center()
{
	return pos;
}


cgp::vec3 Soldat::get_vision_pos()
{
	soldat_mesh->soldat_to_draw.update_local_to_global_coordinates();

	return soldat_mesh->soldat_to_draw["Eyes"].global_transform.translation + soldat_mesh->soldat_to_draw["Eyes"].global_transform.rotation*vec3(0,0.12, 0.02);
}

rotation_transform Soldat::get_vision_orientation()
{
	return soldat_mesh->soldat_to_draw["Eyes"].global_transform.rotation * rotation_transform::from_axis_angle({0,1,0},Pi);
}
cgp::vec3 Soldat::get_hit_box()
{
	return hit_box;
}
