#include "Feu/Feu.hpp"
#include "cgp/cgp.hpp"

class Chevalier_Mesh {
public :
	cgp::hierarchy_mesh_drawable man_drawable;
	cgp::hierarchy_mesh_drawable saddle_drawable;
	cgp::hierarchy_mesh_drawable horse_drawable;

	const cgp::vec3 trans_center = cgp::vec3(0, -1.5, 0.6);
	void make_chevalier();
	void make_man();
	void make_man_obsolete();
	void make_saddle();
	void make_horse();
	void scale(float s = 0.3);

	void reset();
};


class Chevalier
{
private : 
	cgp::vec3 man_pos;
	cgp::vec3 saddle_pos;
	cgp::vec3 horse_pos;
	

public :
	static bool is_mesh_initialized;
	static Chevalier_Mesh* cheva_mesh;
	
	
	cgp::vec3 hit_box;
	Chevalier(cgp::vec3 horse_pos);
	Chevalier(cgp::vec3 horse_pos, cgp::vec3 saddle_pos, cgp::vec3 man_pos);
	static void initialize_mesh();
	void draw_chevalier(scene_environment_camera_head& environment);
	void update_chevalier();

	//Fonctions d'animation et mouvement 
	cgp::vec3 get_center();
	cgp::vec3 get_hit_box();
	cgp::vec3 get_vision_pos();
	cgp::rotation_transform get_vision_orientation();
	void get_orientation();
	void mouvement_test();
};

