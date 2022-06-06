#include "water/water.hpp"

using namespace cgp;
Water::Water(float _quad_length, cgp::vec3 _position)
{
	quad_length = _quad_length;
	position = _position;
	initialize();
}

void Water::initialize()
{
	GLuint shad = opengl_load_shader("shaders/water/water_vert.glsl", "shaders/water/wat.glsl");
	dudv_texture = opengl_load_texture_image("assets/Terrain_Texture/waterDUDV.png", GL_REPEAT, GL_REPEAT);
	normal_map_texture = opengl_load_texture_image("assets/Terrain_Texture/normal.png");

	quad_water.initialize(mesh_primitive_quadrangle({-1,0,-1},{1,0,-1}, {1,0,1}, {-1,0,1}), "Water",shad);
	quad_water.transform.scaling = quad_length;
	quad_water.transform.translation = position;
	quad_water.shading.color = vec3(0, 0, 1);
	initializeFBOs();
}

void Water::initializeFBOs()
{
	initializeReflectionFBO();
	initializeRefractionFBO();
}

void Water::initializeReflectionFBO()
{
	reflectionFBO = createFrameBuffer();
	reflectionTexture = createTextureAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
	reflectionDepthBuffer = createDepthBufferAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
	unbindCurrentFrameBuffer();

}

void Water::initializeRefractionFBO()
{
	refractionFBO = createFrameBuffer();
	refractionTexture = createTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
	refractionDepthTexture = createDepthTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
	unbindCurrentFrameBuffer();
}

void Water::bindRefractionFrameBuffer()
{
	bindFrameBuffer(refractionFBO, REFRACTION_WIDTH, REFRACTION_HEIGHT, refractionTexture);
}

void Water::bindReflectionFrameBuffer()
{ 
	bindFrameBuffer(reflectionFBO, REFLECTION_WIDTH, REFLECTION_HEIGHT, reflectionTexture);
}

void Water::bindFrameBuffer(GLuint framebuffer, int width, int height, GLuint texture)
{
	glBindTexture(GL_TEXTURE_2D, 0);//To make sure the texture isn't bound
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glViewport(0, 0, width, height);
	glBindTexture(GL_TEXTURE_2D, refractionDepthTexture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glClearColor(0,0,0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
}

GLuint Water::getRefractionDepthTexture()
{
	return refractionDepthTexture;
}

GLuint Water::getReflectionTexture()
{
	return reflectionTexture;
}

GLuint Water::getRefractionTexture()
{
	return refractionTexture;
}

void Water::updateWindowSize(int width, int height)
{
	window_width = width;
	window_height = height;

	glBindTexture(GL_TEXTURE_2D, reflectionTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_2D, refractionDepthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_2D, refractionTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);

}

GLuint Water::createFrameBuffer()
{
	GLuint frameBuffer;
	glGenFramebuffers(1, &frameBuffer);
	//generate name for frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	//create the framebuffer
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	//indicate that we will always render to color attachment 0
	return frameBuffer;
}

GLuint Water::createTextureAttachment(int width, int height)
{
	
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
		0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,
		texture, 0);

	return texture;
}

GLuint Water::createDepthTextureAttachment(int width, int height)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height,
		0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,
		texture, 0);
	return texture;
}

GLuint Water::createDepthBufferAttachment(int width, int height)
{
	GLuint depthBuffer;
	glGenRenderbuffers(1, &depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width,
		height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
		GL_RENDERBUFFER, depthBuffer);
	return depthBuffer;
}

void Water::unbindCurrentFrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, window_width, window_height);
}

void Water::draw_Water(scene_environment_camera_head& environment, float t)
{
	time = t;
	vec3 camera_pos = vec3(0, 0, 0);
	if (environment.is_camera_head_used)
		camera_pos = environment.camera.position();
	else
		camera_pos = environment.camera_fixe.position();

	glUseProgram(quad_water.shader); opengl_check;
	glActiveTexture(GL_TEXTURE2); opengl_check;
	glBindTexture(GL_TEXTURE_2D, reflectionTexture); opengl_check;
	opengl_uniform(quad_water.shader, "reflectionTexture", 2);  opengl_check;
	glActiveTexture(GL_TEXTURE1); opengl_check;
	glBindTexture(GL_TEXTURE_2D, refractionTexture); opengl_check;
	opengl_uniform(quad_water.shader, "refractionTexture", 1);  opengl_check;
	glActiveTexture(GL_TEXTURE3); opengl_check;
	glBindTexture(GL_TEXTURE_2D, dudv_texture); opengl_check;
	opengl_uniform(quad_water.shader, "dudv_texture", 3);
	glActiveTexture(GL_TEXTURE4); opengl_check;
	glBindTexture(GL_TEXTURE_2D, normal_map_texture); opengl_check;
	opengl_uniform(quad_water.shader, "normal_map_texture", 4); opengl_check;
	glActiveTexture(GL_TEXTURE5); opengl_check;
	glBindTexture(GL_TEXTURE_2D, refractionDepthTexture); opengl_check;
	opengl_uniform(quad_water.shader, "normal_map_texture", 5); opengl_check;
	opengl_uniform(quad_water.shader, "light_position", vec3(0, 100, 0), false);
	opengl_uniform(quad_water.shader, "wave_speed", std::fmod(time/80,1.f), false);
	opengl_uniform(quad_water.shader, "camera_position", camera_pos, false);
	draw(quad_water, environment);
}














































void fbo_screen_effect::initialize(GLuint shader_screen_effect, int width, int height)
{
	window_width = width;
	window_height = height;

	// Allocate texture to store a rendered image
	glGenTextures(1, &output_texture_id);
	glBindTexture(GL_TEXTURE_2D, output_texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Allocate a depth buffer - need to do it when using the frame buffer
	int const max_window_width = 2000;
	int const max_window_height = 2000;
	glGenRenderbuffers(1, &depth_buffer_id);
	glBindRenderbuffer(GL_RENDERBUFFER, depth_buffer_id);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, max_window_width, max_window_height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	// Create frame buffer
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	// associate the texture to the frame buffer
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, output_texture_id, 0);
	// associate the depth-buffer
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_buffer_id);

	// Reset the standard framebuffer to output on the screen
	glBindFramebuffer(GL_FRAMEBUFFER, 0);



	// The result of the second pass is displayed on a quad
	quad_screen.initialize(mesh_primitive_quadrangle({ -1,-1,0 }, { 1,-1,0 }, { 1,1,0 }, { -1,1,0 }));
	quad_screen.texture = output_texture_id;
	quad_screen.shader = shader_screen_effect;

}

void fbo_screen_effect::update_screen_resize(int width, int height)
{
	window_width = width;
	window_height = height;

	glBindTexture(GL_TEXTURE_2D, output_texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void fbo_screen_effect::prepare_render_pass_into_fbo(vec3 const& background_color)
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glViewport(0, 0, window_width, window_height);
	glBindTexture(GL_TEXTURE_2D, output_texture_id);

	glClearColor(background_color.x, background_color.y, background_color.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
}


void draw_effect(fbo_screen_effect const& screen_effect)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, screen_effect.window_width, screen_effect.window_height);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	mesh_drawable const& drawable = screen_effect.quad_screen;
	if (drawable.number_triangles == 0) return;

	// Setup shader
	assert_cgp(drawable.shader != 0, "Try to draw mesh_drawable without shader [name:" + drawable.name + "]");
	assert_cgp(drawable.texture != 0, "Try to draw mesh_drawable without texture [name:" + drawable.name + "]");
	glUseProgram(drawable.shader); opengl_check;

	// Set texture
	glActiveTexture(GL_TEXTURE0); opengl_check;
	glBindTexture(GL_TEXTURE_2D, drawable.texture); opengl_check;
	opengl_uniform(drawable.shader, "image_texture", 0);  opengl_check;

	// Call draw function
	assert_cgp(drawable.number_triangles > 0, "Try to draw mesh_drawable with 0 triangles [name:" + drawable.name + "]"); opengl_check;
	glBindVertexArray(drawable.vao);   opengl_check;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, drawable.vbo.at("index")); opengl_check;
	glDrawElements(GL_TRIANGLES, GLsizei(drawable.number_triangles * 3), GL_UNSIGNED_INT, nullptr); opengl_check;

	// Clean buffers
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}