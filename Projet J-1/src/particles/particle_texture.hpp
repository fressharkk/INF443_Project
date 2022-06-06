#include "environment_camera_head/environment_camera_head.hpp"

class ParticleTexture
{
	GLuint textureID;
	int nb_rows; //Using Texture Atlas 
public:
	ParticleTexture(GLuint _textureID, int _nbRows);
	GLuint getTextureID();
	int getNbRows();
};