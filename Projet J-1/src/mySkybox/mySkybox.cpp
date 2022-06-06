#include "mySkybox/mySkybox.hpp"
 
using namespace cgp;

void mySkybox::initialize(std::string object_name, float _blend)
{
	GLuint const shader = opengl_load_shader("shaders/skybox/sky_vert.glsl", "shaders/skybox/sky_frag.glsl");
	
	mesh const cube_mesh = mesh_primitive_cube({ 0,0,0 }, 10.0f);
	
	const std::string l = object_name;
	cube.initialize(cube_mesh, l);
	cube.shader = shader;
	
	cube.texture = loadSkybox_texturePNG("assets/skyboxes/skybox_day/");
	loadSkybox_texturePNG("assets/skyboxes/skybox_night/");
	blend = _blend;

}

GLuint mySkybox::loadSkybox_texturePNG(std::string path)
{

	image_raw const x_neg_day = image_load_file(path + "left.png");
	image_raw const x_pos_day = image_load_file(path + "right.png");
	image_raw const y_pos_day = image_load_file(path + "top.png");
	image_raw const y_neg_day = image_load_file(path + "bottom.png");
	image_raw const z_pos_day = image_load_file(path + "back.png");
	image_raw const z_neg_day = image_load_file(path + "front.png");


	GLuint cubemap;
	glGenTextures(1, &cubemap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);
	
	
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, x_neg_day.width, x_neg_day.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ptr(x_neg_day.data));
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, x_pos_day.width, x_pos_day.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ptr(x_pos_day.data));

	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, y_neg_day.width, y_neg_day.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ptr(y_neg_day.data));
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, y_pos_day.width, y_pos_day.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ptr(y_pos_day.data));

	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, z_neg_day.width, z_neg_day.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ptr(z_neg_day.data));
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, z_pos_day.width, z_pos_day.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ptr(z_pos_day.data));

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	textureIDs.push_back(cubemap);
	return cubemap;

}

void mySkybox::updateSkybox(float t)
{
	rotationAngle = rotationSpeed * t;
}
void mySkybox::setFogColour(vec3 c)
{
	fogColour = c;
}
void mySkybox::draw_Skybox(scene_environment_camera_head &environment)
{
	mat4 m_view;
	if (environment.is_camera_head_used)
		m_view = environment.camera.matrix_view();
	else if (environment.use_water_camera)
		m_view = environment.water_camera.matrix_view();
	else
		m_view = environment.camera_fixe.matrix_view();
	glDepthMask(GL_FALSE);


	if (cube.number_triangles == 0) return;

	// Setup shader
	assert_cgp(cube.shader != 0, "Try to draw skybox_drawable without shader [name:" + cube.name + "]");
	assert_cgp(cube.texture != 0, "Try to draw skybox_drawable without texture [name:" + cube.name + "]");
	glUseProgram(cube.shader); opengl_check; 
	mat3 rot = rotation_transform::convert_quaternion_to_matrix(rotation_transform::from_axis_angle({ 0,1,0 }, rotationAngle).data);
	skyboxMatrix = mat4(rot);
	skyboxMatrix[3][3] = 1;
	skyboxMatrix *= m_view;
	// Send uniforms for this shader
	opengl_uniform(cube.shader, "projection", environment.projection.matrix());
	opengl_uniform(cube.shader, "view", skyboxMatrix);
	opengl_uniform(cube.shader, "model", cube.model_matrix());

	// Set texture as a cubemap (different from the 2D texture using in the "standard" draw call)
	glActiveTexture(GL_TEXTURE0); opengl_check;
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureIDs[0]); opengl_check;
	cgp::opengl_uniform(cube.shader, "image_texture", 0);  opengl_check;
	glActiveTexture(GL_TEXTURE1); opengl_check;
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureIDs[1]); opengl_check;
	cgp::opengl_uniform(cube.shader, "image_texture2", 1, false); opengl_check;
	cgp::opengl_uniform(cube.shader, "blend", blend, false); opengl_check;
	cgp::opengl_uniform(cube.shader, "fogColour", fogColour, false); opengl_check;
	// Call draw function
	assert_cgp(cube.number_triangles > 0, "Try to draw mesh_drawable with 0 triangles [name:" + cube.name + "]"); opengl_check;
	glBindVertexArray(cube.vao);   opengl_check;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube.vbo.at("index")); opengl_check;
	glDrawElements(GL_TRIANGLES, GLsizei(cube.number_triangles * 3), GL_UNSIGNED_INT, nullptr); opengl_check;

	// Clean buffers
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glDepthMask(GL_TRUE);
}

float mySkybox::getBlend()
{
	return blend;
}

void mySkybox::setBlend(float blend_)
{
	blend = blend_;
}
  