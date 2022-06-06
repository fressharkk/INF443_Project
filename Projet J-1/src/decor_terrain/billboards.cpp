#include "billboards.hpp"

using namespace cgp;

mesh_drawable BillBoards::quad;
bool BillBoards::is_mesh_initialized = false;

BillBoards::BillBoards(GLuint text, int n, float scale, float min_x, float max_x, float min_z, float max_z, float(*func)(float, float), cgp::vec3(*n_func)(float, float))
{
	if (!BillBoards::is_mesh_initialized)
		initialize();

	quad.texture = text;
	quad.transform.scaling = scale;
	for (int i = 0; i < n; i++)
	{
		float x = rand_interval(min_x, max_x);
		float z = rand_interval(min_z, max_z);
		float y = func(x, z);
		pos.push_back(vec3(x,y,z));
		normales.push_back(n_func(x, z));
	}
}

BillBoards::BillBoards(std::string path, int n, float scale,  float min_x, float max_x, float min_z, float max_z, float(*func)(float, float), cgp::vec3(*n_func)(float, float))
{
	if (!BillBoards::is_mesh_initialized)
		initialize();

	quad.texture = opengl_load_texture_image(path,GL_REPEAT, GL_REPEAT);
	quad.transform.scaling = scale;
	for (int i = 0; i < n; i++)
	{
		float x = rand_interval(min_x, max_x);
		float z = rand_interval(min_z, max_z);
		float y = func(x, z);
		pos.push_back(vec3(x, y, z));
		normales.push_back(n_func(x, z));
	}
}

void BillBoards::initialize()
{
	quad.initialize(mesh_primitive_quadrangle());
	is_mesh_initialized = true;
}

rotation_transform BillBoards::correctOrientation(int i, scene_environment_camera_head &environment)
{
	
	auto r = rotation_transform::from_axis_angle({ 1,0,0 }, 0); //DEFAULT RETURN
	
	vec3 front_cam;
	vec3 right_cam;
	
	if (environment.is_camera_head_used)
	{
		front_cam = environment.camera.front();
		right_cam = environment.camera.right();
	}
	else if (environment.use_water_camera)
	{
		front_cam = environment.water_camera.front() * vec3(1, 0, 1);
		right_cam = environment.water_camera.right();
	}
	else
	{
		front_cam = environment.camera_fixe.front() * vec3(1, 0, 1);
		right_cam = environment.camera_fixe.right();
	}
	

	if (norm(front_cam) < 0.0001)
		return r;
	else front_cam = normalize(front_cam);

	
	if (std::abs(dot(right_cam, front_cam)) > 0.000001)
		return r;

	rotation_transform R = rotation_transform::between_vector({ 1,0,0 }, { 0,0,-1 }, right_cam, front_cam);
	return R*rotation_transform::between_vector({ 0,-1,0 }, normales[i]);
}

void BillBoards::draw_billboards(scene_environment_camera_head& environment)
{
	for (int i = 0; i < pos.size(); i++)
	{
		auto r = correctOrientation(i, environment);
		quad.transform.rotation = r;
		quad.transform.translation = pos[i];
		draw(quad, environment);
	}

}
