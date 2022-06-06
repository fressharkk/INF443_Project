#pragma once

#include "cgp/cgp.hpp"
#include <vector>
#include "decor_terrain/cart.hpp"
#include "decor_terrain/rock.hpp"
#include "decor_terrain/lake.hpp"
#include "soldat/soldat.hpp"
#include "particles/particle_Emitter.hpp"
#include "decor_terrain/myTerrain.hpp"
#include "water/water.hpp"
#include "decor_terrain/low_tree.hpp"
#include "decor_terrain/billboards.hpp"
#include <algorithm>

//Trees
	//Weeds
	//Cactus
	// 
	//Rocks
	//Carts
	//Straws
	//Lake
	//



typedef std::vector<cgp::vec3> l_pos;
typedef std::tuple<std::string, int> elt;
typedef std::vector<elt> corresp;
typedef std::tuple<elt, float> dist_idx;
typedef std::tuple<bool, float> col;

class gridCut
{
	float x_min = -100;
	float x_max = 100;
	float z_min = -100;
	float z_max = 100;
	corresp grid_correspondance[10][10];
	Rocks* r1;
	Rocks* r2;
	Rocks* r3;
	Water* w;
	Carts* c;
public: 
	float translateX(float x);
	float translateZ(float z);
	void setBounds(cgp::vec4 bounds);
	void divide_Terrain(Rocks* rocks1, Rocks* rocks2, Rocks* rocks3, Water* water, l_pos tree, Carts *carts);
	void detectCollisionFixe(cgp::vec3 pos, cgp::vec3 hitbox);
	dist_idx checkCollision(cgp::vec3, cgp::vec3 hitbox, int i, int j);
	cgp::vec3 getPositionOutOfElt(elt p);
	cgp::vec3 getHitBoxOutOfElt(elt p);
	col isCollision(cgp::vec3 p1, cgp::vec3 h1, cgp::vec3 p2, cgp::vec3 h2);
	col intersect(cgp::vec4 a, cgp::vec4 b);
};