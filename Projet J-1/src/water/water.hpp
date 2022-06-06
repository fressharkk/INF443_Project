#include "cgp/cgp.hpp"
#include "environment_camera_head/environment_camera_head.hpp"

class Water
{
private:
	int window_width = 1280;
	int window_height = 720;
	float time = 0.f;
	cgp::mesh_drawable quad_water;
	float quad_length;
	cgp::vec3 position;
	GLuint reflectionFBO;
	GLuint reflectionTexture;
	GLuint reflectionDepthBuffer;
	
	GLuint refractionFBO;
	GLuint refractionTexture;
	GLuint refractionDepthTexture;

	GLuint dudv_texture;
	GLuint normal_map_texture;
	const int REFRACTION_WIDTH = 1280;
	const int REFRACTION_HEIGHT = 720;

	const int REFLECTION_WIDTH = 320;
	const int REFLECTION_HEIGHT = 180;

public:
	cgp::vec3 pos = cgp::vec3(75, -0.5, 75);
	float radius = 17;
	Water(float _quad_length, cgp::vec3 _position);
	void initialize();
	void initializeFBOs();
	void initializeReflectionFBO();
	void initializeRefractionFBO();
	void bindRefractionFrameBuffer();
	void bindReflectionFrameBuffer();
	void bindFrameBuffer(GLuint framebuffer, int width, int height, GLuint texture);
	GLuint getRefractionDepthTexture();
	GLuint getReflectionTexture();
	GLuint getRefractionTexture();
	void updateWindowSize(int width, int height);
	GLuint createFrameBuffer();
	GLuint createTextureAttachment(int width, int height);
	GLuint createDepthTextureAttachment(int width, int height);
	GLuint createDepthBufferAttachment(int width, int height);
	void unbindCurrentFrameBuffer();
	void draw_Water(scene_environment_camera_head& environment, float t);
};


struct fbo_screen_effect
{
	GLuint fbo;
	GLuint output_texture_id;
	GLuint depth_buffer_id;

	cgp::mesh_drawable quad_screen;

	int window_width;
	int window_height;

	void initialize(GLuint shader_screen_effect, int width, int height);
	void update_screen_resize(int width, int height); // Function to call everytime the window is resized

	void prepare_render_pass_into_fbo(cgp::vec3 const& background_color = { 0,0,0 });
};


void draw_effect(fbo_screen_effect const& screen_effect);