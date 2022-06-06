#include "flame_collisions.hpp"

using namespace cgp;

void checkFlameCollisionGround(Flamme* f, myTerrain& terrain, float current_time)
{
	vec3 pos = f->getPos();
	vec3 dir_axis = normalize(f->getDirAxis());
	float cone_radius = f->getConeRadius();
	float cone_height = f->getConeHeight();
	float speed = f->getSpeed();
	float t = f->getTimeOfCreation();
	std::cout << t << std::endl;
	std::cout << t * speed << std::endl;
	//VERSION PLUS SIMPLE (PLUS RAPIDE)
	vec3 coords = pos + dir_axis * cone_height;//std::min(cone_height, (current_time ) * speed);
	if (coords.y - myTerrain::getHeight(coords.x, coords.z) < 0.5)
		burn(coords.x, coords.z, terrain);

	std::cout << coords << std::endl;
	//VERSION PLUS SOFISTIQUEE
	/*for (int i = 0; i < 10; i++)
	{
		float angle = (float) 2 * Pi * i / 10;
		vec3 orth = vec3(-dir_axis.y, dir_axis.x, dir_axis.z);
		vec3 coords = pos + dir_axis * std::min(cone_height, (current_time-t) * speed) + cos(angle) * orth + sin(angle)
			*cross(dir_axis,orth);
		vec3 coords_ = pos + dir_axis;
		if ((coords.y - myTerrain::getHeight(coords.x, coords.z) < 0.5) || (coords_.y - myTerrain::getHeight(coords_.x, coords_.z)) < 0.5 )
			burn(coords.x, coords.z, terrain);
	}*/


}

void burn(float x, float z, myTerrain &terrain)
{
	std::cout << x + 100 << std::endl;
	std::cout << z + 100 << std::endl;
	terrain.updateIsBurnt((int)(x + 100) / 2, (int)(z + 100) / 2);
}
