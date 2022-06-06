#include "low_tree.hpp"

using namespace cgp;

hierarchy_mesh_drawable build_tree()
{
	hierarchy_mesh_drawable tree;
	mesh_drawable trunk;
	mesh_drawable leaves;
	leaves.initialize(mesh_load_file_obj("assets/lowpoly_tree_leaves.obj"), "Leaves");
	trunk.initialize(mesh_load_file_obj("assets/lowpoly_tree_trunk.obj"), "Trunk");
	
	leaves.shading.color = vec3(140/255, 190/255, 90/255);
	trunk.shading.color = vec3(213 / 255, 157 / 255, 74 / 255);


	tree.add(trunk);
	tree.add(leaves, "Trunk");

	return tree;
}
