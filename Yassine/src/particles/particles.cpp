#include "particles.hpp"

Particle::Particle(float _createTime, GLuint textureID, int nb_rows, cgp::vec3 _position, cgp::vec3 _velocity, float _gravityEffect, float _lifeTime, float _rotation, float _scale)
{
	position = _position;
	velocity = _velocity;
	gravityEffect = _gravityEffect;
	lifeTime = _lifeTime;
	rotation = _rotation;
	scale = _scale;
	previous_time = _createTime;
	texture = new ParticleTexture(textureID, nb_rows);
}

cgp::vec2 Particle::getTextureOffset1()
{
	return texture_Offset1;
};
cgp::vec2 Particle::getTextureOffset2()
{
	return texture_Offset2;
};

float Particle::getBlend()
{
	return blend;
};

cgp::vec3 Particle::getPosition()
{
	return position;
}

cgp::vec3 Particle::getVelocity()
{
	return velocity;
}

float Particle::getGravityEffect()
{
	return gravityEffect;
}

float Particle::getRotation()
{
	return rotation;
}

float Particle::getScale()
{
	return 0.0f;
}

bool Particle::update_particle(float t)
{
	float dt = t - previous_time;
	velocity.z += GRAVITY * gravityEffect * dt;
	position += dt * velocity;
	elapsedTime += dt;
	previous_time = t;
	updateTextureCoord();
	return elapsedTime < lifeTime;
 }

GLuint Particle::getTexture()
{
	return texture->getTextureID();
}

int Particle::getNbRow()
{
	return texture->getNbRows();
}

void Particle::updateTextureCoord()
{
	float lifeFactor = elapsedTime / lifeTime;
	int stageCount = texture->getNbRows() * texture->getNbRows();
	float atlasProgression = lifeFactor * stageCount;
	int index1 = (int)atlasProgression;
	int index2 = index1 < stageCount - 1 ? index1+ 1 : index1;
	blend = std::fmod(atlasProgression,1.f);
	setTextureOffset(texture_Offset1, index1);
	setTextureOffset(texture_Offset2, index2);

}

void Particle::setTextureOffset(cgp::vec2 offset, int index)
{
	int column = index % texture->getNbRows();
	int row = (int) index / texture-> getNbRows();
	offset.x = (float)column / texture->getNbRows();
	offset.y = (float)row / texture->getNbRows();

}
