#include "cgp/cgp.hpp"
#include "chevalier/chevalier.hpp"

class Soldat_Mesh
{
public:
	cgp::hierarchy_mesh_drawable soldat_to_draw;
	const cgp::vec3 trans_center = cgp::vec3(0, -0.9, 0);
	void make_soldat();
	void reset();
};

class Soldat
{
private:
	cgp::vec3 pos;

public:
	static bool is_mesh_initialized;
	static Soldat_Mesh* soldat_mesh;
	static void initialize_mesh();

	cgp::vec3 hit_box;
	Soldat(cgp::vec3 pos_);
	void draw_soldat(scene_environment_camera_head& environment);
	void update_soldat();

	//Fonctions d'animation et mouvement 
	cgp::vec3 get_center();
	cgp::vec3 get_hit_box();
	cgp::vec3 get_vision_pos();
	cgp::rotation_transform get_vision_orientation();

	void get_orientation();
	void mouvement_test();


	

};