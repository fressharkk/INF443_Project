#pragma once

#include "cgp/cgp.hpp"
#include "environment_camera_head/environment_camera_head.hpp"

class Rocks
{
	cgp::mesh rock_with_texture(float radius, cgp::vec3 const& center, int Nu, int Nv);
	cgp::mesh rock_with_texture_1(float radius, cgp::vec3 const& center, int Nu, int Nv);
	cgp::mesh rock_with_texture_2(float radius, cgp::vec3 const& center, int Nu, int Nv);
	cgp::mesh_drawable rock;
public :
	float rad;
	cgp::vec3 getHitBox();
	std::vector<cgp::vec3> pos;
	std::vector<cgp::vec3> ori;
	std::vector<cgp::vec3> getPos();
	Rocks(int type, int number, float radius, cgp::vec3 center, cgp::vec4 bounds, float(*func)(float, float), cgp::vec3(*n_func)(float, float));
	void generatePositions(int n, float min_x, float max_x, float min_z, float max_z, float(*func)(float, float), cgp::vec3(*n_func)(float, float));
	void draw_rocks(scene_environment_camera_head &environment);

	
};

