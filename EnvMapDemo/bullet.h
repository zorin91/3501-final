#ifndef BULLET_H
#define BULLET_H

#include <string>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/quaternion.hpp>

#include "resource.h"
#include "scene_node.h"

namespace game {


	class Bullet{

	public:
		// Constructor
		Bullet(const Resource *geometry, const Resource *material, glm::vec3 pos, glm::vec3 traj);

		// Destructor
		~Bullet();

		//Get Set methods
		glm::quat GetAngM(void) const;
		void SetAngM(glm::quat angm);

		glm::vec3 getPosition();
		void setPosition(glm::vec3 pos);

		glm::vec3 getTrajectory();
		void setTrajectory(glm::vec3 traj);

		// Update geometry configuration
		void update(float timer);

	private:
		// Angular momentum of asteroid
		glm::quat angm_;
		glm::vec3 position;
		glm::vec3 trajectory;
		float speed = 1.0;
		float damage = 2;
		float radius = 5;
		float elapsedTime = 0;
		bool dead = false;

	};

} // namespace game

#endif
