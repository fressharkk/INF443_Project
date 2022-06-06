#pragma once

#include "grid_cut.hpp"

void checkFlameCollisionGround(Flamme* f, myTerrain& terrain, float current_time);
void burn(float x, float y,myTerrain& terrain);