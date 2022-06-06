#pragma once
#include "cgp/cgp.hpp"
#include "environment_camera_head/environment_camera_head.hpp"

using namespace cgp;

class mySkybox 
{
	mesh_drawable cube;
	std::vector<GLuint> textureIDs;
	float blend = 1;
	float rotationAngle = 0;
	float rotationSpeed = 0.01;
	mat4 skyboxMatrix;
	vec3 fogColour;
public : 
	void updateSkybox(float t);
	void setFogColour(vec3 c);
	void initialize(std::string object_name = "MySkybox", float blend = 1);
	GLuint loadSkybox_texturePNG(std::string path);
	void draw_Skybox(scene_environment_camera_head &environment);
	float getBlend();
	void setBlend(float blend_);
};

