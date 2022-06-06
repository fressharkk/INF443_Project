
#include "particle_texture.hpp"

#define GRAVITY -0.981*0.01

class Particle {

private:
	cgp::vec3 position;
	cgp::vec3 velocity;
	cgp::vec2 texture_Offset1;
	cgp::vec2 texture_Offset2;
	float blend;
	float gravityEffect;
	float lifeTime;
	float rotation;
	float scale;
	ParticleTexture* texture;

	float elapsedTime = 0;
public: 
	Particle(float _createTime, GLuint textureID, int nb_rows, cgp::vec3 _position, cgp::vec3 _velocity, float _gravityEffect, float _lifeTime, float _rotation, float _scale);
	
	cgp::vec3 getPosition();
	cgp::vec3 getVelocity();
	float previous_time;
	float getGravityEffect();
	float getRotation();
	float getScale();
	cgp::vec2 getTextureOffset1();
	cgp::vec2 getTextureOffset2();
	float getBlend();
	bool update_particle(float t);
	GLuint getTexture();
	int getNbRow();
	void updateTextureCoord();
	float getCreationTime();
	float getElapsedTime();
	float getLifeTime();
	void setTextureOffset(cgp::vec2& offset, int index);
};
