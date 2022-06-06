#pragma once

#include "cgp/cgp.hpp"
#include "dragon/dragon.hpp"
#include "third_party/src/simplexnoise/simplexnoise1234.hpp"

class Feu
{
	cgp::mesh_drawable mesh_to_draw;
	cgp::mesh primitive_mesh;
	cgp::vec3 center;
	float length;
	float height;
public :
	Feu(cgp::vec3 _center, float _length, float _height, cgp::vec3& feu_attributes);
	void apply_noise(std::string type = "Simplex");
	void draw_feu(scene_environment_camera_head &environment) ;
};