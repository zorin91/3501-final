#ifndef EHELI_H
#define EHELI_H

#include <string>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/quaternion.hpp>
#include <vector>

#include "resource.h"
#include "scene_node.h"
#include "bullet.h"

namespace game {


	class EnemyHeli{

	public:
		// Constructor
		EnemyHeli(const Resource *geometry, const Resource *material, glm::vec3 pos, std::vector<Bullet *> bullets);

		// Destructor
		~EnemyHeli();

		//Get Set methods
		glm::quat getAngle(void) const;
		void getAngle(glm::quat angm);

		glm::vec3 getPosition();
		void setPosition(glm::vec3 pos);

		glm::vec3 getTrajectory();
		void setTrajectory(glm::vec3 traj);

		// Update geometry configuration
		void update(float timer);

	private:
		// Angular momentum of asteroid
		glm::quat angle;
		glm::vec3 position;
		glm::vec3 trajectory;
		float speed = 1.0;
		float health = 50;
		float radius = 20;
		float timer = 0;
		float rateOfFire = 0.1;
		bool dead = false;

	};

} // namespace game

#endif
