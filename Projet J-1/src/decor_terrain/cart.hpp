#pragma once

#include "cgp/cgp.hpp"
#include "environment_camera_head/environment_camera_head.hpp"

class Carts
{
	cgp::mesh cylinder_with_texture(float h, float r);
	cgp::mesh disc_with_texture(float r);
	cgp::mesh create_straw_mesh();
	cgp::mesh create_cart_mesh();
	
	cgp::mesh_drawable cart;
	cgp::mesh_drawable straw;
	float length;
	float width;
	float height;
public:
	cgp::vec3 hitbox;
	std::vector<cgp::vec3> pos;
	std::vector<cgp::vec3> ori;
	
	cgp::vec3 getHitBox();
	std::vector<cgp::vec3> getPos();
	Carts(int number, float scale, cgp::vec4 bounds, float(*func)(float, float), cgp::vec3(*n_func)(float, float));
	void generatePositions(int n, float min_x, float max_x, float min_z, float max_z, float(*func)(float, float), cgp::vec3(*n_func)(float, float));
	void draw_carts(scene_environment_camera_head& environment);


};

