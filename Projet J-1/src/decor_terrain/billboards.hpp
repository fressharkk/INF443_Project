#include "cgp/cgp.hpp"
#include "environment_camera_head/environment_camera_head.hpp"
#include <vector>

class BillBoards
{
	GLuint texture; 
	static cgp::mesh_drawable quad;
	static bool is_mesh_initialized;
	std::vector<cgp::vec3> pos;
	std::vector<cgp::vec3> normales;
public:
	BillBoards(GLuint text, int n, float scale, float min_x, float max_x, float min_z, float max_z, float (*func)(float,float), cgp::vec3 (*n_func)(float, float));
	BillBoards(std::string path, int n, float scale, float min_x, float max_x, float min_z, float max_z, float (*func)(float, float), cgp::vec3(*n_func)(float, float));
	void initialize();
	cgp::rotation_transform correctOrientation(int i, scene_environment_camera_head& environment);
	void draw_billboards(scene_environment_camera_head&environment);
};