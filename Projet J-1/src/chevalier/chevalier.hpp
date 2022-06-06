#include "Feu/Feu.hpp"
#include "cgp/cgp.hpp"

class Chevalier_Mesh {
public :
	cgp::hierarchy_mesh_drawable man_drawable;
	cgp::hierarchy_mesh_drawable saddle_drawable;
	cgp::hierarchy_mesh_drawable horse_drawable;

	const cgp::vec3 trans_center = cgp::vec3(0, -1.5, 0.6);
	void make_chevalier();
	void make_man();
	void make_man_obsolete();
	void make_saddle();
	void make_horse();
	void scale(float s = 0.3);

	void reset();
};

class Chevalier
{
private : 
	cgp::vec3 man_pos;
	cgp::vec3 saddle_pos;
	cgp::vec3 horse_pos;
	cgp::vec4 leg_angles_up;
	cgp::vec4 leg_angles_down;
	float previousTime;
	float step_duration = 1;
	float walking_speed = 1;
	float ropes_speed = 5  ;
	float base_speed = 15;
	float phase_1_speed = 25;
	float phase_1_duration;
public :
	static bool is_mesh_initialized;
	static Chevalier_Mesh* cheva_mesh;

	void setPreviousTime(float t);
	
	void phase_1(float t);

	cgp::vec3 hit_box;
	Chevalier(cgp::vec3 horse_pos);
	Chevalier(cgp::vec3 horse_pos, cgp::vec3 saddle_pos, cgp::vec3 man_pos);
	static void initialize_mesh();
	void draw_chevalier(scene_environment_camera_head& environment, float (*height_func)(float, float), cgp::vec3 (*normal_func)(float,float));
	void update_chevalier();
	cgp::rotation_transform get_horse_rotation();
	//Fonctions d'animation et mouvement 

	cgp::vec3 get_center();
	cgp::vec3 get_hit_box();
	cgp::vec3 get_vision_pos();
	cgp::rotation_transform get_vision_orientation();
	cgp::vec4 getLegUpAngles();
	cgp::vec4 getLegDownAngles();
	void get_orientation();
	void mouvement_test();

	//Fonctions de déplacement
	
	void trot_step_1(float t, float beginning_time, float duration = 0.0);
	void trot_step_2(float t, float beginning_time, float duration = 0.0);
	void trot_step_3(float t, float beginning_time, float duration = 0.0);
	void trot_step_4(float t, float beginning_time, float duration = 0.0);

	void man_jump_trot(float t, float beginning_time, float duration = 0.0);

	void move_tail(float t, float beginning_time, float duration = 0.0);
	void trot(cgp::vec3 dir, float t, float beginning_time, float duration = 0.0, float walking_speed = -1, float step_duration = -1);
	void move_left_arm_back(float t, float beginning_time, float duration = 0.0);
	void move_left_arm_front(float t, float beginning_time, float duration = 0.0);
	void move_right_arm_back(float t, float beginning_time, float duration = 0.0);
	void move_right_arm_front(float t, float beginning_time, float duration = 0.0);

	//Fonctions globales d'action 
	void attack(); //Plusieurs types d'attaques
	void defend();
	void flee();
	void die();
	void ally();
	void kill();
	void get_burnt();
	void run_randomly();
	void see_neighbors();
	void fall();
	void getUp();
	void getOnHorse();
	void sit();
	void layDown();
	void throwWeapon();
	void surrender();
	void fallFromHorseLeft();
	void fallFromHorseRight();
	void getDownHorse();
	void trample();
	void fearHorse();

};

