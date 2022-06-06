#include "soldat.hpp"

using namespace cgp;

float eps = 0.01;

bool is_equal_to(float a, float b)
{
	return (bool) (std::abs(a - b) < eps);
}
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
	mesh_drawable sword_blade;
	mesh_drawable sword_guard;
	mesh_drawable shield;


	vec3 grey_color = vec3(0.6, 0.6, 0.6);
	vec3 grey_color_2 = vec3(0.55, 0.55, 0.55);
	auto texture_armure = opengl_load_texture_image("assets/Soldat_Texture/Armure.png", GL_REPEAT);
	auto texture_vetements = opengl_load_texture_image("assets/Soldat_Texture/vetements.png", GL_REPEAT);
	GLuint texture_sword;
	GLuint texture_sword_guard;
	GLuint texture_shield = opengl_load_texture_image("assets/Soldat_Texture/shield_texture.jpg", GL_REPEAT);
//eyes.texture = opengl_load_texture_image("assets/eye_texture.jpg");
	
	sword_blade.initialize(mesh_load_file_obj("assets/Soldat/sword_sec_mod_blade.obj"), "Sword 2");
	sword_blade.transform.scaling = 0.25;
	sword_blade.transform.translation = vec3(-0.18, -0.23, 0.74);
	sword_guard.initialize(mesh_load_file_obj("assets/Soldat/sword_sec_mod_guard.obj"), "Sword");
	sword_guard.transform.scaling = 0.25;
	sword_guard.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, Pi / 2);
	sword_blade.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, Pi / 2);

	sword_guard.transform.translation = vec3(-0.18, -0.23, 0.74);
	shield.initialize(mesh_load_file_obj("assets/Soldat/shield.obj"), "Shield");
	shield.transform.scaling = 0.02;
	shield.transform.translation = vec3(-0.3, -0.3, 0);
	shield.transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 }, Pi-1.05*Pi/3);
	shield.transform.translation += vec3(0.54, 0.15, -0.2);
	shield.texture = texture_shield;
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
	vec3 genou_gauche_trans = vec3(-0.25, -0.55, 0.05);
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

	////Jambe Droite
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
	
	soldat_to_draw.add(sword_guard, "Gant Droit");
	soldat_to_draw.add(sword_blade, "Sword");
	soldat_to_draw.add(shield, "Gant Gauche");

	soldat_to_draw.update_local_to_global_coordinates();
}

void Soldat_Mesh::reset()
{
	soldat_to_draw["Torse"].transform.translation = trans_center;
	soldat_to_draw["Torse"].transform.rotation = rotation_transform::from_axis_angle({ 0,1,0 }, Pi);
	soldat_to_draw.update_local_to_global_coordinates();
}

Soldat_Mesh* Soldat::soldat_mesh = new Soldat_Mesh();
bool Soldat::is_mesh_initialized = false;

Soldat::Soldat(cgp::vec3 pos_)
{
	pos = pos_;
	initial_pos = pos_;
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

void Soldat::draw_soldat(scene_environment_camera_head& environment, float(*height_func)(float, float), cgp::vec3(*normal_func)(float, float))
{
	if (Soldat::is_mesh_initialized)
	{
		vec3 normale = normal_func(pos.x, pos.z);
		vec3 last_translation = vec3(0, height_func(pos.x, pos.z) - pos.y - 0.1*dot({1,1,1},normale), 0);
		pos += last_translation;
		soldat_mesh->soldat_to_draw["Torse"].transform.translation = pos;
		soldat_mesh->soldat_to_draw["Torse"].transform.rotation *= rotation_transform::between_vector({ 0,-1,0 }, normale);
		if (is_dead)
			soldat_mesh->soldat_to_draw["Torse"].transform.rotation = last_rotation;
		update_soldat();
	
		draw(soldat_mesh->soldat_to_draw, environment);
		soldat_mesh->reset();
	}
}

void Soldat::update_soldat()
{
	soldat_mesh->soldat_to_draw.update_local_to_global_coordinates();
}

void Soldat::setPreviousTime(float t)
{
	previous_time = t;
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

float Soldat::getRadius()
{
	return radius;
}

void Soldat::setRadius(float _radius)
{
	radius = _radius;
}

cgp::vec4 Soldat::getLegAngles()
{
	float left_leg;
	float right_leg;
	float left_low_leg;
	float right_low_leg;
	auto r1 = soldat_mesh->soldat_to_draw["Jambe Gauche"].transform.rotation.data ;
	auto r2 = soldat_mesh->soldat_to_draw["Jambe Droite"].transform.rotation.data;
	auto r3 = soldat_mesh->soldat_to_draw["Genou Gauche"].transform.rotation.data;
	auto r4 = soldat_mesh->soldat_to_draw["Genou Droit"].transform.rotation.data;
	rotation_transform::convert_quaternion_to_axis_angle(r1, vec3(), left_leg);
	rotation_transform::convert_quaternion_to_axis_angle(r2, vec3(), right_leg);
	rotation_transform::convert_quaternion_to_axis_angle(r3, vec3(), left_low_leg);
	rotation_transform::convert_quaternion_to_axis_angle(r4, vec3(), right_low_leg);

	return vec4(left_leg, right_leg, left_low_leg, right_low_leg);
}

cgp::vec4 Soldat::getArmAngles()
{
	float left_arm;
	float right_arm;
	float left_elbow;
	float right_elbow;
	auto r1 = soldat_mesh->soldat_to_draw["Bras Gauche"].transform.rotation.data;
	auto r2 = soldat_mesh->soldat_to_draw["Bras Droit"].transform.rotation.data;
	auto r3 = soldat_mesh->soldat_to_draw["Coude Gauche"].transform.rotation.data;
	auto r4 = soldat_mesh->soldat_to_draw["Coude Droit"].transform.rotation.data;
	rotation_transform::convert_quaternion_to_axis_angle(r1, vec3(), left_arm);
	rotation_transform::convert_quaternion_to_axis_angle(r2, vec3(), right_arm);
	rotation_transform::convert_quaternion_to_axis_angle(r3, vec3(), left_elbow);
	rotation_transform::convert_quaternion_to_axis_angle(r4, vec3(), right_elbow);
	return vec4(left_arm, right_arm, left_elbow, right_elbow);
	
}

cgp::vec3 Soldat::getOrientation()
{
	return get_rotation() * vec3(0, 0, 1);
}

float Soldat::getTorseAngle()
{
	return dot(getOrientation(), vec3(0, 1,0));
}

rotation_transform Soldat::get_rotation()
{
	return soldat_mesh->soldat_to_draw["Torse"].transform.rotation;
}

cgp::vec3 Soldat::get_hit_box()
{
	return hit_box;
}

void Soldat::translate(cgp::vec3 v)
{
	pos += v;
}

void Soldat::walk(cgp::vec3 dir, float t, float beginning_time, float duration, float walking_speed, float _step_duration)
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
	

	right_leg_up(act_t, 0, _step_duration / 3);
	right_leg_down(act_t, _step_duration / 3, _step_duration / 6);
	left_leg_up(act_t, _step_duration / 2, _step_duration / 3);
	left_leg_down(act_t, 5 * _step_duration / 6, _step_duration / 6);

	move_left_arm_back(act_t, 0, _step_duration / 2);
	move_left_arm_front(act_t, _step_duration / 2, _step_duration / 2);
	move_right_arm_front(act_t, 0, _step_duration / 2);
	move_right_arm_back(act_t, _step_duration / 2, _step_duration / 2);

	end_walking(t, beginning_time+duration - _step_duration / 2, _step_duration / 2);
	if (std::abs(walking_speed + 1) < 0.001)
		walking_speed = speed;

	translate((t-previous_time)*get_rotation()*dir);

	setPreviousTime(t);
}

void Soldat::kneel(float t, float beginning_time, float duration)
{
	if (t < beginning_time)
		return;
	if (t - beginning_time > duration)
		return;
	if (is_equal(t - beginning_time, 0))
		leg_angles = getLegAngles();

	float ratio = (t - beginning_time) / duration;
	soldat_mesh->soldat_to_draw["Genou Droit"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, leg_angles.w + (Pi / 2 - leg_angles.w) * ratio);
	soldat_mesh->soldat_to_draw["Genou Gauche"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, leg_angles.z + (Pi / 2 - leg_angles.z) * ratio);

}

void Soldat::hands_behind_head(float t, float beginning_time, float duration, float a1, float a2)
{
	if (t < beginning_time)
		return;
	if (t - beginning_time > duration)
		return;
	if (is_equal(t - beginning_time, 0))
		arm_angles = getArmAngles();

	float ratio = (t - beginning_time) / duration;
	soldat_mesh->soldat_to_draw["Bras Gauche"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, arm_angles.x + (0.95*Pi-arm_angles.x)*ratio);
	soldat_mesh->soldat_to_draw["Coude Gauche"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,-1 }, arm_angles.z + (0.6*Pi-arm_angles.z)*ratio);
	soldat_mesh->soldat_to_draw["Bras Droit"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, arm_angles.y + (0.95 * Pi - arm_angles.y) * ratio);
	soldat_mesh->soldat_to_draw["Coude Droit"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,1 },arm_angles.w + (0.55*Pi - arm_angles.w)*ratio);
	
}

void Soldat::run_to(cgp::vec3 objective, float t, float beginning_time)
{
	if (t < beginning_time)
		return;

	vec3 dir = objective - pos;
	float walking_speed = 0.4;
	if (norm(dir) < 0.0001)
		return;
	soldat_mesh->soldat_to_draw["Torse"].transform.rotation = rotation_transform::between_vector(getOrientation(), normalize(dir));
	walk(normalize(dir), t, beginning_time, norm(dir) / walking_speed, 0.5);
}

void Soldat::walk_to(cgp::vec3 objective, float t, float beginning_time)
{
	if (t < beginning_time)
		return;

	vec3 dir = objective - pos;
	float walking_speed = 0.1;
	if (norm(dir) < 0.0001)
		return;
	soldat_mesh->soldat_to_draw["Torse"].transform.rotation = rotation_transform::between_vector(getOrientation(), normalize(dir));
	walk(normalize(dir), t, beginning_time, norm(dir) / walking_speed, 1);
}

void Soldat::end_walking(float t, float beginning_time, float duration)
{
	if (t < beginning_time)
		return;
	if (t - beginning_time > duration)
		return;
	if (std::abs(t - beginning_time) < 0.01)
	{
		leg_angles = getLegAngles();
		arm_angles = getArmAngles();
	}

	float ratio = (t - beginning_time) / duration;
	soldat_mesh->soldat_to_draw["Jambe Gauche"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, leg_angles.x - leg_angles.x * ratio);
	soldat_mesh->soldat_to_draw["Genou Gauche"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, leg_angles.z - leg_angles.z * ratio);
	soldat_mesh->soldat_to_draw["Jambe Droite"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, leg_angles.y - leg_angles.y * ratio);
	soldat_mesh->soldat_to_draw["Genou Droit"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, leg_angles.w - leg_angles.w * ratio);
	soldat_mesh->soldat_to_draw["Bras Gauche"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, arm_angles.x  - arm_angles.x * 2 * ratio);
	soldat_mesh->soldat_to_draw["Bras Droit"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, arm_angles.y  - arm_angles.y * 2 * ratio);
}


void Soldat::test_mvt(float t, float beginning_time, float duration)
{
	if (t < beginning_time)
		return;
	if (t - beginning_time > duration)
		return;
	if (is_equal(t - beginning_time, 0))
		arm_angles = getArmAngles();
	
	float v0 = 0.05;
	float alpha = Pi / 3;
	float ratio = (t - beginning_time) / duration;
	soldat_mesh->soldat_to_draw["Bras Gauche"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, Pi / 3);
	soldat_mesh->soldat_to_draw["Shield"].transform.translation = soldat_mesh->soldat_to_draw["Shield"].transform.rotation*vec3(0, -9.81 * 0.5 * 0.5 * t, 0);
	//vec3 trans = 0.5 * get_rotation() * vec3(0, -0.5 * 9.81 * (0.5*t) * (0.5*t) + v0 * sin(alpha) * (0.5*t), v0 * cos(alpha) * 0.5*t);
	//std::cout << soldat_mesh->soldat_to_draw["Sword"].global_transform.translation.y << std::endl;
	//if (soldat_mesh->soldat_to_draw["Sword"].global_transform.translation.y > 0)
	//	soldat_mesh->soldat_to_draw["Sword"].transform.translation = trans;
	/*soldat_mesh->soldat_to_draw["Bras Droit"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, arm_angles.y + (Pi / 3 - arm_angles.y) * ratio);
	soldat_mesh->soldat_to_draw["Bras Gauche"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, arm_angles.x + (Pi / 3 - arm_angles.x) * ratio);*/
}

void Soldat::right_leg_up(float t, float beginning_time, float duration)
{
	
	if (t < beginning_time)
		return;
	if (t > beginning_time + duration)
		return;
	if (std::abs(t - beginning_time) < 0.01)
	{
		leg_angles = getLegAngles();
		torse_angle = getTorseAngle();
		rot = get_rotation();
		
	}


	float ratio = (t - beginning_time) / duration;
	//soldat_mesh->soldat_to_draw["Torse"].transform.rotation = rotation_transform::from_axis_angle(rot*vec3(1, 0, 0), Pi / 12 * ratio) * rot;//torse_angle + (torse_inclinaison*0.7 - torse_angle)*ratio)*rot;
	soldat_mesh->soldat_to_draw["Jambe Gauche"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, leg_angles.x+ (Pi/3 - leg_angles.x)*ratio );
	soldat_mesh->soldat_to_draw["Genou Gauche"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, leg_angles.z + (Pi/3 - leg_angles.z)*ratio);
	soldat_mesh->soldat_to_draw["Jambe Droite"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 },leg_angles.y -leg_angles.y * ratio);
	soldat_mesh->soldat_to_draw["Genou Droit"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, leg_angles.w-leg_angles.w * ratio);

}

void Soldat::right_leg_down(float t, float beginning_time,  float duration)
{
	if (t < beginning_time)
		return;
	if (t > beginning_time + duration)
		return;
	if (std::abs(t - beginning_time) < 0.01)
	{
		leg_angles = getLegAngles();
		torse_angle = getTorseAngle();
		rot = get_rotation();
	}
	
	float ratio = (t - beginning_time) / duration;
	//soldat_mesh->soldat_to_draw["Torse"].transform.rotation *= rotation_transform::from_axis_angle({ 1,0,0 }, torse_angle+(torse_inclinaison -torse_angle)*ratio);
	soldat_mesh->soldat_to_draw["Jambe Gauche"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, leg_angles.x+(Pi/6 - leg_angles.x)*ratio);
	soldat_mesh->soldat_to_draw["Genou Gauche"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, leg_angles.z-leg_angles.z*ratio);
	//soldat_mesh->soldat_to_draw["Jambe Droite"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, -leg_angles.y * ratio);
	//soldat_mesh->soldat_to_draw["Genou Droit"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, -leg_angles.w * ratio);
	
}

void Soldat::left_leg_up(float t, float beginning_time, float duration)
{
	if (t < beginning_time)
		return;
	if (t > beginning_time + duration)
		return;
	if (std::abs(t - beginning_time) < 0.01)
	{
		leg_angles = getLegAngles();
		torse_angle = getTorseAngle();
		rot = get_rotation();
	}

	float ratio = (t - beginning_time) / duration;
		
	//soldat_mesh->soldat_to_draw["Torse"].transform.rotation *= rotation_transform::from_axis_angle({ 1,0,0 }, torse_angle + (torse_inclinaison * 0.7 - torse_angle) * ratio);
	soldat_mesh->soldat_to_draw["Jambe Gauche"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, leg_angles.x + (0- leg_angles.x) * ratio);
	soldat_mesh->soldat_to_draw["Genou Gauche"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, leg_angles.z + (0 - leg_angles.z) * ratio);
	soldat_mesh->soldat_to_draw["Jambe Droite"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, leg_angles.y + (Pi/3 - leg_angles.y) * ratio);
	soldat_mesh->soldat_to_draw["Genou Droit"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, leg_angles.w + (Pi/3 - leg_angles.w) * ratio);
	//setPreviousTime(t);
}

void Soldat::left_leg_down(float t, float beginning_time, float duration)
{
	if (t < beginning_time)
		return;
	if (t > beginning_time + duration)
		return;
	if (std::abs(t - beginning_time) < 0.01)
	{
		leg_angles = getLegAngles();
		torse_angle = getTorseAngle();
		rot = get_rotation();
	}

	float ratio = (t - beginning_time) / duration;

	//soldat_mesh->soldat_to_draw["Torse"].transform.rotation *= rotation_transform::from_axis_angle({ 1,0,0 }, torse_angle + (torse_inclinaison - torse_angle) * ratio);
	soldat_mesh->soldat_to_draw["Jambe Droite"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, leg_angles.y + (Pi / 6 - leg_angles.y) * ratio);
	soldat_mesh->soldat_to_draw["Genou Droit"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, leg_angles.w - leg_angles.w * ratio);
	//soldat_mesh->soldat_to_draw["Jambe Droite"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, -leg_angles.y * ratio);
	//soldat_mesh->soldat_to_draw["Genou Droit"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, -leg_angles.w * ratio);

}

void Soldat::move_left_arm_back(float t, float beginning_time, float duration)
{
	if (t < beginning_time)
		return;
	if (t > beginning_time + duration)
		return;
	if (std::abs(t - beginning_time) < 0.01 || std::abs(t-beginning_time - duration/2) < 0.01)
	{
		arm_angles = getArmAngles();
		
	}

	float ratio = (t - beginning_time) / duration;

	if ((t-beginning_time) < duration/2.)
		soldat_mesh->soldat_to_draw["Bras Gauche"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, arm_angles.x + (Pi / 6 - arm_angles.x) * 2*ratio);
	else
		soldat_mesh->soldat_to_draw["Bras Gauche"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, arm_angles.x - arm_angles.x * 2*(ratio-0.5) );

}

void Soldat::move_left_arm_front(float t, float beginning_time, float duration)
{
	if (t < beginning_time)
		return;
	if (t > beginning_time + duration)
		return;
	if (std::abs(t - beginning_time) < 0.01 || std::abs(t - beginning_time - duration / 2) < 0.01)
	{
		arm_angles = getArmAngles();
	}

	float ratio = (t - beginning_time) / duration;

	if ((t - beginning_time) < duration / 2.)
	{
		soldat_mesh->soldat_to_draw["Bras Gauche"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, arm_angles.x + (Pi / 4 - arm_angles.x) * 2 * ratio);
	}
	else
	{
		soldat_mesh->soldat_to_draw["Bras Gauche"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, arm_angles.x - arm_angles.x * 2 * (ratio - 0.5));
	}
		
}

void Soldat::move_right_arm_back(float t, float beginning_time, float duration)
{
	if (t < beginning_time)
		return;
	if (t > beginning_time + duration)
		return;
	if (std::abs(t - beginning_time) < 0.01 || std::abs(t - beginning_time - duration / 2) < 0.01)
	{
		arm_angles = getArmAngles();

	}

	float ratio = (t - beginning_time) / duration;

	if ((t - beginning_time) < duration / 2.)
		soldat_mesh->soldat_to_draw["Bras Droit"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, arm_angles.y + (Pi / 6 - arm_angles.y) * 2 * ratio);
	else
		soldat_mesh->soldat_to_draw["Bras Droit"].transform.rotation = rotation_transform::from_axis_angle({ 1,0,0 }, arm_angles.y - arm_angles.y * 2 * (ratio - 0.5));

}

void Soldat::move_right_arm_front(float t, float beginning_time, float duration)
{
	if (t < beginning_time)
		return;
	if (t > beginning_time + duration)
		return;
	if (std::abs(t - beginning_time) < 0.01 || std::abs(t - beginning_time - duration / 2) < 0.01)
	{
		arm_angles = getArmAngles();
	}

	float ratio = (t - beginning_time) / duration;

	if ((t - beginning_time) < duration / 2.)
	{
		soldat_mesh->soldat_to_draw["Bras Droit"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, arm_angles.y + (Pi / 4 - arm_angles.y) * 2 * ratio);
	}
	else
	{
		soldat_mesh->soldat_to_draw["Bras Droit"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, arm_angles.y - arm_angles.y * 2 * (ratio - 0.5));
	}

}

void Soldat::shield_up(float t, float beginning_time, float duration )
{
	if (t < beginning_time)
		return;
	if (t - beginning_time > duration)
		return;
	if (std::abs(t - beginning_time) < 0.01)
		arm_angles = getArmAngles();

	float ratio = (t - beginning_time) / duration;
	
	soldat_mesh->soldat_to_draw["Bras Gauche"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, arm_angles.x+(Pi / 2-arm_angles.x)*ratio);
	soldat_mesh -> soldat_to_draw["Coude Gauche"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,-1}, arm_angles.z + (Pi / 2 - arm_angles.z) * ratio);
}

void Soldat::shield_down(float t, float beginning_time, float duration)
{
	if (t < beginning_time)
		return;
	if (t - beginning_time > duration)
		return;
	if (std::abs(t - beginning_time) < 0.01)
		arm_angles = getArmAngles();

	float ratio = (t - beginning_time) / duration;

	soldat_mesh->soldat_to_draw["Bras Gauche"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, arm_angles.x + ( - arm_angles.x) * ratio);
	soldat_mesh->soldat_to_draw["Coude Gauche"].transform.rotation = rotation_transform::from_axis_angle({ 0,0,-1 }, arm_angles.z + ( - arm_angles.z) * ratio);
}


void Soldat::fall_back(float t, float beginning_time, float duration)
{
	if (t < beginning_time)
		return;
	if (t - beginning_time > duration)
		return;
	if (std::abs(t - beginning_time) < 0.01)
		arm_angles = getArmAngles();

	float ratio = (t - beginning_time) / duration;

	
	soldat_mesh->soldat_to_draw["Torse"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, ratio*Pi/2);

}

// ACTIONS PRINCIPALES
void Soldat::defend(cgp::vec3 nearest, float t, float beginning_time, float up_duration)
{
	shield_up(t, beginning_time);
	shield_down(t, beginning_time + up_duration);
}

void Soldat::die(float t, float beginning_time)
{
	if (t < beginning_time)
		return;
	if (is_dead && t>beginning_time+0.4)
		return;
	fall_back(t, beginning_time);
	is_dead = true;
	last_rotation = get_rotation();
}

void Soldat::left_slash(float t, float beginning_time, float duration)
{
	if (t < beginning_time)
		return;
	if (t > beginning_time + duration)
		return;
	if (std::abs(t - beginning_time) < 0.01 || std::abs(t-beginning_time-duration/2) < 0.01)
		arm_angles = getArmAngles();
	float ratio = (t - beginning_time) / duration;



	if ((t - beginning_time) < duration / 2)
		soldat_mesh->soldat_to_draw["Bras Droit"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, arm_angles.y+ (Pi/2 - arm_angles.y) * 2 * ratio);
	else
	{
		soldat_mesh->soldat_to_draw["Coude Droit"].transform.rotation = rotation_transform::from_axis_angle({ 1,1,0 }, arm_angles.w + (Pi / 3 - arm_angles.w) * 2 * (ratio - 0.5));
		soldat_mesh->soldat_to_draw["Bras Droit"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, Pi / 2 - 1.5*Pi / 3 * 2 * (ratio - 0.5));
	}
}

void Soldat::sword_kill()
{
	//soldat_mesh->soldat_to_draw["Bras Droit"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, Pi / 3);
}

void Soldat::right_slash(float t, float beginning_time, float duration)
{
	if (t < beginning_time)
		return;
	if (t > beginning_time + duration)
		return;
	if ((std::abs(t - beginning_time) < 0.01) || std::abs(t - beginning_time - duration / 2) < 0.01)
		arm_angles = getArmAngles();

	float ratio = (t - beginning_time) / duration;

	if ((t - beginning_time) < duration / 2)
	{
		soldat_mesh->soldat_to_draw["Bras Droit"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, arm_angles.y + (Pi / 2 - arm_angles.y) * 2 * ratio);
		soldat_mesh->soldat_to_draw["Coude Droit"].transform.rotation = rotation_transform::from_axis_angle({ 1,1,0 }, arm_angles.w - arm_angles.w * 2 * ratio);
	}
	else
		soldat_mesh->soldat_to_draw["Bras Droit"].transform.rotation = rotation_transform::from_axis_angle({ -1,0,0 }, arm_angles.y * (1 - 2 * (ratio - 0.5)));

}

void Soldat::throwWeapon(float t, float beginning_time, float duration)
{
	if (t < beginning_time)
		return;
	if (t + beginning_time > duration)
		return;
	
	//Phase 1 : bras droit levé => Ok
	//Phase 2 : Epée qui part => Calcul de la trajectoire 
	//Phase 3 : Idem bouclier => Ok début
	//Phase 4 : Genoux Pliés => Ok
	//Phase 5 : Bras Derrières la tete
}
//
//void Soldat::see_neighbors(std::vector<cgp::vec3> chevaliers, std::vector<cgp::vec3> soldats)
//{
//	nb_chevaliers = 0;
//	nb_soldats = 0;
//	nearest_soldat = vec3(100, 100, 100);
//	nearest_chev = vec3(100, 100, 100);
//
//	for (auto chev : chevaliers)
//	{
//		if (norm(chev - pos) < radius && norm(chev - pos) > 0.01)
//			nb_chevaliers += 1;
//		if (norm(chev - pos) < norm(nearest_chev - pos))
//			nearest_chev = chev;
//	}
//	for (auto sold : soldats)
//	{
//		if (norm(sold - pos) < radius)
//			nb_soldats += 1;
//		if (norm(sold - pos) < norm(nearest_soldat - pos))
//			nearest_soldat = sold;
//	}
//
//}
//
//void Soldat::gestionActions(std::vector<cgp::vec3> chevaliers, std::vector<cgp::vec3> soldats)
//{
//	see_neighbors(chevaliers, soldats);
//	if (nb_chevaliers <= nb_soldats)
//		attack(nearest_chev);
//	else if (nb_chevaliers > nb_soldats && nb_chevaliers - nb_soldats < 3)
//		defend(nearest_chev, 0, 0, 0);
//	else
//	{
//		float p = rand_interval();
//		if (p < 0.8)
//			surrender();
//		if (p >= 0.2)
//			flee();
//	}
//	
//}
