#include "particle_Emitter.hpp"

using namespace cgp;

ParticleEmitter::ParticleEmitter(ParticleTexture tex, float _pps, float _speed, float _gravityComplient, float _lifeLength, float _scale, float beginningTime,  bool sort, bool additiveBlending,std::string type)
{
		
		pps = _pps;
		averageSpeed = _speed;
		gravityComplient = _gravityComplient;
		averageLifeLength = _lifeLength;
		averageScale = _scale;
		timeOfCreation = beginningTime;
		prevTime = beginningTime;
		draw_c = new Particle_Cloud(tex, sort, additiveBlending, type);
}

void ParticleEmitter::setDirection(vec3 direction, float deviation)
{
	direction = direction;
	directionDeviation = (float)deviation * Pi;
}

void ParticleEmitter::randomizeRotation()
{
	randomRotation = true;
}

void ParticleEmitter::setSpeed(float s)
{
	averageSpeed = s;
}

void ParticleEmitter::setPps(float _pps)
{
	pps = _pps;
}

void ParticleEmitter::setLifeLength(float l)
{
	averageLifeLength = l;
}

void ParticleEmitter::setScale(float s)
{
	averageScale = s;
}

void ParticleEmitter::setGravEffect(float g)
{
	gravityComplient = g;
}

void ParticleEmitter::setSpeedError(float error)
{
	speedError = error * averageSpeed;
}

void ParticleEmitter::setLifeError(float error)
{
	lifeError = error * averageLifeLength;
}

void ParticleEmitter::setScaleError(float error)
{
	scaleError = error * averageScale;
}

void ParticleEmitter::generateParticles(cgp::vec3 systemCenter, float current_time)
{
	float delta = current_time - prevTime;
	float particlesToCreate = pps * delta;
	int count = (int) particlesToCreate;
	float partialParticle = std::fmod(particlesToCreate,1);
	for (int i = 0; i < count; i++) {
		emitParticle(systemCenter, current_time);
	}
	if (rand_interval() < partialParticle) {
		emitParticle(systemCenter, current_time);
	}
	draw_c->update_all_particles(current_time);
	prevTime = current_time;
}

void ParticleEmitter::emitParticle(cgp::vec3 center, float current_time)
{
	cgp::vec3 velocity = vec3(0, 0, 0);
	if (norm(direction) > 0.0000001) {
		velocity = generateRandomUnitVectorWithinCone(direction, directionDeviation);
	}
	else {
		velocity = generateRandomUnitVector();
	}

	velocity = generateValue(averageSpeed, speedError) * normalize(velocity);
	

	float scale = generateValue(averageScale, scaleError);
	float lifeLength = generateValue(averageLifeLength, lifeError);
	draw_c->addParticle(current_time, center, velocity, gravityComplient, lifeLength, generateRotation(), scale);
}

float ParticleEmitter::generateValue(float average, float errorMargin)
{
	float offset = (rand_interval() - 0.5) * 2.f * errorMargin;
	return average + offset;
}

float ParticleEmitter::generateRotation()
{
	if (randomRotation)
		return rand_interval() * 360;
	else
		return 0;
}

cgp::vec3 ParticleEmitter::generateRandomUnitVectorWithinCone(cgp::vec3 coneDirection, float angle)
{
	float cosAngle = (float) cos(angle);
	float theta = (float)(rand_interval() * 2.f * Pi);
	float z = cosAngle + (rand_interval() * (1 - cosAngle));
	float rootOneMinusZSquared = (float) sqrt(1 - z * z);
	float x = (float)(rootOneMinusZSquared *  cos(theta));
	float y = (float)(rootOneMinusZSquared *  sin(theta));

	vec4 direction = vec4(x, y, z, 1);
	if (coneDirection.x != 0 || coneDirection.y != 0 || (coneDirection.z != 1 && coneDirection.z != -1)) {
		vec3 rotateAxis = normalize(cross(coneDirection, vec3(0, 0, 1)));
		float rotateAngle = (float) acos(dot(coneDirection, vec3(0, 0, 1)));
		rotation_transform rotationMatrix = rotation_transform::from_axis_angle(rotateAxis, -rotateAngle);
		direction = rotationMatrix * direction ;
	}
	else if (coneDirection.z == -1) {
		direction.z *= -1;
	}
	return direction;
}

cgp::vec3 ParticleEmitter::generateRandomUnitVector()
{
		float theta = (float)(rand_interval() * 2.f * Pi);
		float z = (rand_interval() * 2) - 1;
		float rootOneMinusZSquared = (float) sqrt(1 - z * z);
		float x = (float)(rootOneMinusZSquared * cos(theta));
		float y = (float)(rootOneMinusZSquared * sin(theta));
		return vec3(x,y,z);
	
}

void ParticleEmitter::drawParticles(scene_environment_camera_head& environment)
{
	draw_c->drawParticles(environment);
}


