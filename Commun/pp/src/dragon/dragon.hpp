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