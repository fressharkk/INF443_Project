#include "grid_cut.hpp"


using namespace cgp;

float gridCut::translateX(float x)
{
	return (x - x_min) / (x_max - x_min);
}

float gridCut::translateZ(float z)
{
	return (z - z_min) / (z_max - z_min);
}

void gridCut::setBounds(cgp::vec4 bounds)
{
	x_min = bounds.x;
	x_max = bounds.y;
	z_min = bounds.z;
	z_max = bounds.w;
}

void gridCut::divide_Terrain(Rocks* rocks1, Rocks* rocks2, Rocks* rocks3, Water* water, l_pos tree, Carts* carts)
{
	r1 = rocks1;
	r2 = rocks2;
	r3 = rocks3;
	w = water;
	c = carts;
	for (int i = 0; i< rocks1->getPos().size(); i++)
	{
		vec3 r = rocks1->getPos()[i];
		int x = (int) 10*translateX(r.x);
		int z = (int) 10*translateZ(r.z);
		grid_correspondance[x][z].push_back(elt("Rocks1", i));
	}
	for (int i = 0; i < rocks2->getPos().size(); i++)
	{
		vec3 r = rocks2->getPos()[i];
		int x = (int)10 * translateX(r.x);
		int z = (int)10 * translateZ(r.z);
		grid_correspondance[x][z].push_back(elt("Rocks2", i));
	}
	for (int i = 0; i < rocks3->getPos().size(); i++)
	{
		vec3 r = rocks3->getPos()[i];
		int x = (int)10 * translateX(r.x);
		int z = (int)10 * translateZ(r.z);
		grid_correspondance[x][z].push_back(elt("Rocks3", i));
	}
	for (int i = 0; i < carts->getPos().size(); i++)
	{
		vec3 r = carts->getPos()[i];
		int x = (int)10 * translateX(r.x);
		int z = (int)10 * translateZ(r.z);
		grid_correspondance[x][z].push_back(elt("Carts", i));
	}
	
	int x = (int)10 * translateX(water->pos.x);
	int z = (int)10 * translateZ(water->pos.y);
	grid_correspondance[x][z].push_back(elt("Water", 0));


}

void gridCut::detectCollisionFixe(cgp::vec3 pos, cgp::vec3 hitbox)
{
	int x_int = (int)10 * translateX(pos.x);
	int z_int = (int)10 * translateZ(pos.z);
	
	std::vector<dist_idx> distances;

	distances.push_back(checkCollision(pos, hitbox, x_int, z_int+1));
	distances.push_back(checkCollision(pos, hitbox, x_int, z_int));
	distances.push_back(checkCollision(pos, hitbox, x_int, z_int-1));
	distances.push_back(checkCollision(pos, hitbox, x_int+1, z_int+1));
	distances.push_back(checkCollision(pos, hitbox, x_int+1, z_int));
	distances.push_back(checkCollision(pos, hitbox, x_int+1, z_int-1));
	distances.push_back(checkCollision(pos, hitbox, x_int-1, z_int+1));
	distances.push_back(checkCollision(pos, hitbox, x_int-1, z_int));
	distances.push_back(checkCollision(pos, hitbox, x_int-1, z_int-1));

	std::sort(distances.begin(), distances.end(), [](dist_idx a, dist_idx b)
		{
			return std::get<1>(a) < std::get<1>(b);
		});

	if (std::get<1>(distances[0]) < 1000)
		std::cout << "COLLLLLISSSSIOOON        " << std::get<0>(std::get<0>(distances[0])) << std::endl;
}

dist_idx gridCut::checkCollision(cgp::vec3 position, cgp::vec3 hitbox, int i, int j)
{
	
		if (i < 0)
			return dist_idx(elt("",-1), 100000);
		if (j < 0)
			return dist_idx(elt("", -1), 100000);
		if (i > 9)
			return dist_idx(elt("", -1), 100000);
		if (j > 9)
			return dist_idx(elt("", -1), 100000);

		float min_dist = 1000000;
		dist_idx res = dist_idx(elt("", -1), min_dist);
		for (auto p : grid_correspondance[i][j])
		{
			vec3 pos_p = getPositionOutOfElt(p);
			vec3 hit_b = getHitBoxOutOfElt(p);
			col collision = isCollision(pos_p, hit_b, position, hitbox);
			if (std::get<0>(collision))
			{
				float d = std::get<1>(collision);
				if (d <= std::get<1>(res))
					res = dist_idx(p, std::get<1>(collision));
			}
		}
		
		return res;
	
}

cgp::vec3 gridCut::getPositionOutOfElt(elt p)
{
	std::string type = std::get<0>(p);
	int idx = std::get<1>(p);
	if (type == "Rocks1")
		return r1->getPos()[idx];
	else if (type == "Rocks2")
		return r2->getPos()[idx];
	else if (type == "Rocks3")
		return r3->getPos()[idx];
	else if (type == "Water")
		return vec3(75, -0.5, 75);
	else if (type == "Carts")
		return c->getPos()[idx];
	else
		return vec3(100000, 100000, 100000);
}

cgp::vec3 gridCut::getHitBoxOutOfElt(elt p)
{
	std::string type = std::get<0>(p);
	int idx = std::get<1>(p);
	if (type == "Rocks1")
		return r1->getHitBox();
	else if (type == "Rocks2")
		return r2->getHitBox();
	else if (type == "Rocks3")
		return r3->getHitBox();
	else if (type == "Water")
		return vec3(17, 1, 17);
	else if (type == "Carts")
		return c->getHitBox();
	else
		return vec3(0,0,0);
}

col gridCut::isCollision(cgp::vec3 p1, cgp::vec3 h1, cgp::vec3 p2, cgp::vec3 h2)
{
	float min_x, max_x, min_z, max_z;
	float min_x_2, max_x_2, min_z_2, max_z_2;

	min_x = p1.x - h1.x/2;
	min_z = p1.z - h1.z / 2;
	max_x = p1.x + h1.x / 2;
	max_z = p1.z + h1.z / 2;

	min_x_2 = p2.x - h2.x / 2;
	min_z_2 = p2.z - h2.z / 2;
	max_x_2 = p2.x + h2.x / 2;
	max_z_2 = p2.z + h2.z / 2;

	vec4 seg1 = vec4(min_x, max_x, min_z, max_z);
	vec4 seg2 = vec4(min_x_2, max_x_2, min_z_2, max_z_2);
	col c1 = intersect(seg1, seg2);
	col c2 = intersect(seg2, seg1);

	return col(std::get<0>(c1) || std::get<0>(c2), std::min(std::get<1>(c1), std::get<1>(c2)));

}

col gridCut::intersect(cgp::vec4 a, cgp::vec4 b)
{
	bool do_intersect_1 = false;
	bool do_intersect_2 = false;
	bool do_intersect = false;
	float min_dist = 100000;
	if (a.x <= b.y && a.y >= b.x)
	{
		do_intersect_1 = true;
		float d = a.y - b.x;
		if (d < min_dist)
			min_dist = d;
	}

	if (a.z <= b.w && a.w >= b.z)
	{
		do_intersect_2 = true;
		float d = a.w - b.z;
		if (d < min_dist)
			min_dist = d;
	}
	do_intersect = do_intersect_1 && do_intersect_2;
	return col(do_intersect, min_dist);
}


