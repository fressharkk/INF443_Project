#include "cgp/cgp.hpp"
#include "particles/particle_cloud.hpp"

class ParticleEmitter
{
	float pps, averageSpeed, gravityComplient, averageLifeLength, averageScale;
	float timeOfCreation;
	float prevTime;
	float speedError, lifeError, scaleError = 0;
	bool randomRotation = false;
	cgp::vec3 direction;
	float directionDeviation = 0;
public:
	Particle_Cloud* draw_c;

	ParticleEmitter(ParticleTexture text, float _pps, float _speed, float _gravityComplient, float _lifeLength, float _scale, float timeOfCreation, bool sort, bool additiveBlending,std::string type = "quad");
	void setDirection(cgp::vec3 direction, float deviation);
	void randomizeRotation();
	void setSpeed(float s);
	void setPps(float pps);
	void setLifeLength(float l);
	void setScale(float s);
	void setGravEffect(float g);
	void setSpeedError(float error);
	void setLifeError(float error);
	void setScaleError(float error);
	void generateParticles(cgp::vec3 systemCenter, float current_time);
	void emitParticle(cgp::vec3 center, float current_time);
	float generateValue(float average, float errorMargin);
	float generateRotation();
	cgp::vec3 generateRandomUnitVectorWithinCone(cgp::vec3 coneDirection, float angle);
	cgp::vec3 generateRandomUnitVector();

	void drawParticles(scene_environment_camera_head& environment);
};