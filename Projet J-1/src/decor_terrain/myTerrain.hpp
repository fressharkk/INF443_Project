#include "cgp/cgp.hpp"
#include "environment_camera_head/environment_camera_head.hpp"
#include <vector>
#include <random>

class myTerrain
{
	static float height_array[100][100];
	static float sec_height_array[100][100];
	cgp::mesh_drawable main_terrain;
	cgp::mesh_drawable secondary_terrain;
	static float terrain_length;
	GLuint background_texture;
	GLuint road_texture;
	GLuint mud_texture;
	GLuint dirt_texture;
	GLuint burnt_texture;
	GLuint is_burnt_texture;
	GLuint empty_grid_texture;
	std::vector<GLuint> blend_maps_textures;
	cgp::grid_2D<cgp::vec3> is_burnt = cgp::grid_2D<cgp::vec3>(100, 100);
	cgp::grid_2D<cgp::vec3> empty_grid = cgp::grid_2D<cgp::vec3>(100, 100);
	int octaves = 3;
	float amplitude = 20;
	float roughness = 0.4;
public:
	float getTerrainLength();
	float noise(float x, float z);
	float main_terrain_shape(float x, float z);
	float evaluate_terrain_height(float x, float z);
	void build_terrain(int N, float terrain_length);
	void build_terrain_secondary(int N, float terrain_length);
	float secondaryNoise(int x, int z);
	void initialize();
	void createTexture();
	void updateIsBurnt(int x, int z);
	static float getHeight(float x, float z);
	static cgp::vec3 get_normal(float x, float z);
	void draw_main_Terrain(scene_environment_camera_head &environment);
	void draw_sec_Terrain_gl(scene_environment_camera_head& environment);
	void draw_sec_Terrain(cgp::vec2 grid_position, scene_environment_camera_head& environment);
	void draw_all_Terrains(scene_environment_camera_head& environment);

};