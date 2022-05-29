#include "particle_texture.hpp"


ParticleTexture::ParticleTexture(GLuint _textureID, int _nbRows)
{
	textureID = _textureID;
	nb_rows = _nbRows;
}
GLuint ParticleTexture::getTextureID()
{
	return textureID;
}

int ParticleTexture::getNbRows()
{
	return nb_rows;
}
