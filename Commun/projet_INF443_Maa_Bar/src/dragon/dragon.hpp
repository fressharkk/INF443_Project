#pragma once

#include "cgp/cgp.hpp"
#include "environment_camera_head/environment_camera_head.hpp"

struct Dragon
{

	cgp::hierarchy_mesh_drawable dragon_hierarchy;
	//Dragon();
	void make_dragon();
	void draw_dragon(scene_environment_camera_head &environment);

};

class Flamme
{
private:
	float cone_radius;
	float cone_height;
	float speed;
	float time_begin;
	cgp::mesh_drawable flamme_mesh_d;
	static int i;

public:

	Flamme(float _cone_radius, float _cone_height, float _speed, float _time_begin);
	void draw_flamme(scene_environment_camera_head& environment, float x, float y, float z, cgp::vec3 dir_axis);
};
