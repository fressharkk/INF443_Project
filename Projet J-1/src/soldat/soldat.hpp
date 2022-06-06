#include "cgp/cgp.hpp"
#include "chevalier/chevalier.hpp"
#include <vector>
class Soldat_Mesh
{
public:
	cgp::hierarchy_mesh_drawable soldat_to_draw;
	const cgp::vec3 trans_center = cgp::vec3(0, -0.9, 0);
	void make_soldat();
	void reset();
};

class Soldat
{
private:
	cgp::vec3 pos;
	cgp::vec3 initial_pos;
	float step_duration = 2;
	float previous_time;
	bool is_dead = false;
	int nb_chevaliers = 0;
	int nb_soldats = 0;
	cgp::vec3 nearest_chev = cgp::vec3(1000, 1000, 1000);
	cgp::vec3 nearest_soldat = cgp::vec3(1000, 1000, 1000);
	float radius = 10;

public:
	static bool is_mesh_initialized;
	static Soldat_Mesh* soldat_mesh;
	static void initialize_mesh();

	cgp::rotation_transform last_rotation;
	cgp::vec4 arm_angles = cgp::vec4(0, 0, 0, 0);
	cgp::vec4 leg_angles = cgp::vec4(0,0,0,0);
	float torse_angle = 0;
	const float torse_inclinaison = cgp::Pi / 10;
	float speed = 0.6;
	cgp::vec3 hit_box;
	cgp::rotation_transform rot;
	cgp::vec3 axis_or;
	
	Soldat(cgp::vec3 pos_);
	
	void draw_soldat(scene_environment_camera_head& environment, float(*height_func)(float, float), cgp::vec3(*normal_func)(float, float));
	void update_soldat();
	void setPreviousTime(float t);
	cgp::vec3 get_center();
	cgp::vec3 get_hit_box();
	cgp::vec3 get_vision_pos();
	cgp::rotation_transform get_vision_orientation();
	float getRadius();
	void setRadius(float _radius);
	cgp::vec4 getLegAngles();
	cgp::vec4 getArmAngles(); 
	cgp::vec3 getOrientation();
	float getTorseAngle();

	cgp::rotation_transform get_rotation();

	//Fonctions de bases
	void translate(cgp::vec3 v);

	//Fonctions d'animation et mouvement 
	
	void test_mvt(float t, float beginning_time, float duration = 0.0);
	void right_leg_up(float t, float beginning_time, float duration = 0.0);
	void right_leg_down(float t, float beginning_time, float duration = 0.0);
	void left_leg_up(float t, float beginning_time,  float duration = 0.0);
	void left_leg_down(float t, float beginning_time, float duration = 0.0);
	void move_left_arm_back(float t, float beginning_time, float duration = 0.0);
	void move_left_arm_front(float t, float beginning_time, float duration = 0.0);
	void move_right_arm_back(float t, float beginning_time, float duration = 0.0);
	void move_right_arm_front(float t, float beginning_time, float duration = 0.0);
	void walk(cgp::vec3 dir, float t, float beginning_time, float duration = 0.0, float walking_speed = -1, float step_duration = -1);
	void kneel(float t, float beginning_time, float duration = 0.0);

	void hands_behind_head(float t, float beginning_time, float duration, float a1, float a2);
	
	void run_to(cgp::vec3 objective, float t, float beginning_time);
	void walk_to(cgp::vec3 objective, float t, float beginning_time);

	void end_walking(float t, float beginning_time, float duration);
	//Types d'attaques :
	
	void slash_throat();
	void sword_kill();
	void cut_head();
	void right_slash(float t, float beginning_time, float duration = 0.3);
	void left_slash(float t, float beginning_time, float duration = 0.3);
	
	//Défense : 
	
	void shield_up(float t, float beginning_time, float duration = 0.3);
	void shield_down(float t, float beginning_time, float duration = 0.2);
	
	//Dying Manners
	
	void fall_back(float t, float beginning_time, float duration = 0.4);
	//Fonctions globales d'action 
	void attack(cgp::vec3 nearest); //Plusieurs types d'attaques
	void defend(cgp::vec3 nearest, float t, float beginning_time, float up_duration);
	void flee();
	void die(float t, float beginning_time);
	void ally();
	void kill();
	void kill_horse();
	void get_burnt();
	void run_randomly();
	//void see_neighbors(std::vector<cgp::vec3> chevaliers, std::vector<cgp::vec3> soldats);
	void fall();
	void getUp();
	void sit(); 
	void layDown();
	void throwWeapon(float t, float beginning_time, float duration);
	void surrender();
	

	//void gestionActions(std::vector<cgp::vec3> chevaliers, std::vector<cgp::vec3> soldats);
};