#pragma once

#include "cgp/cgp.hpp"

cgp::mesh create_road_mesh(float terrain_length);

std::vector<cgp::vec3> generate_positions_on_road(int N, float terrain_length);
