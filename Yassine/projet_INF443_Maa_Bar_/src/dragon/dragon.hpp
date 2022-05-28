#pragma once

#include "cgp/cgp.hpp"
#include <string>
#include <vector>
#include "environment_camera_head/environment_camera_head.hpp"

class Flamme
{
private:
	float cone_radius;
	float cone_height;
	float speed;
	float time_begin;
	cgp::mesh_drawable flamme_mesh_d;
	cgp::vec3 pos;
	cgp::vec3 dir_axis;
	static int i;

public:

	Flamme(float _cone_radius, float _cone_height, float _speed, float _time_begin);
	void set_dir_axis(cgp::vec3 _dir_axis);
	void set_pos(cgp::vec3 _pos);
	void draw_flamme(scene_environment_camera_head& environment);
};


struct Dragon
{

	cgp::hierarchy_mesh_drawable dragon_hierarchy;
	bool dragon_random_tail_not_initialized = true;
	cgp::vec3 initial_position_walking; 
	cgp::vec3 initial_position_temp;
	cgp::vec3 current_orientation_temp;
	
	//First Hit Box : x : 1 y: 6 z : 12
	//Second Hit Box x : 6; y:1, z : 2
	
	const cgp::vec3 hit_box_1 = cgp::vec3(1,6,5);
	const cgp::vec3 hit_box_2 = cgp::vec3(6,1,2);
	float time_coupure; 


	std::vector<cgp::vec3> random_tail_axis;
	//Dragon();
	void make_dragon();
	cgp::vec3 get_current_position();
	cgp::vec3 get_current_orientation();
	cgp::vec3 get_mouth_position();
	cgp::vec3 get_mouth_orientation();
	cgp::rotation_transform get_rotation();
	cgp::rotation_transform get_eyes_rotation();

	void draw_dragon(scene_environment_camera_head &environment);



	// Mouvements internes particuliers

	void reset_legs();
	void open_mouth(float t,  float beginning_time, float duration = 0.0, float speed = 0.0);
	void close_mouth(float t, float beginning_time, float duration = 0.0, float speed = 0.0);

	void stretching_back_legs(float t, float beginning_time, float duration = 0.0);
	void folding_back_legs(float t, float beginning_time, float duration = 0.0);
	void stretching_front_legs(float t, float beginning_time, float duration = 0.0, float speed = 0.0);
	void folding_front_legs(float t, float beginning_time, float duration = 0.0, float speed = 0.0);

	void random_moving_tail(float t, float beginning_time, float duration);
	void initialize_rd_tail(int n);

	void fly_left_wing(float t, float beginning_time, float wing_speed, float duration = 0.0);
	void fly_right_wing(float t, float beginning_time, float wing_speed, float duration = 0.0);

	void full_stretching_neck(float t, float beginning_time, float duration = 0.0);

	void random_moving_neck(float t, float beginning_time, float duration);

	//Mouvements internes plus complexes

	void walking_phase_1(float t, float beginning_time, float walking_speed, float duration);
	void walking_phase_2(float t, float beginning_time, float walking_speed, float duration);
	void walking_phase_3(float t, float beginning_time, float walking_speed, float duration);
	void walking_phase_4(float t, float beginning_time, float walking_speed, float duration);

	//Mouvements externes simples

	
	//Mouvements externes plus complexes

	void walking(float t, float beginning_time, cgp::vec3 where_to, float duration);
	void fly(float t, float beginning_time, cgp::vec3 where_to, float duration, std::string type = "spline_cardinale");
	void fly_(float t, float beginning_time, cgp::vec3 where_to, float duration, std::string type = "spline_cardinale");
	void throw_fire(float t, float beginning_time, float duration, Flamme* flame, scene_environment_camera_head& environment);
};	

