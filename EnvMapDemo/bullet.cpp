#include "bullet.h"
#include <iostream>

namespace game {

	Bullet::Bullet(const Resource *geometry, const Resource *material, glm::vec3 pos, glm::vec3 traj){
		position = pos;
		trajectory = traj;
	}


	Bullet::~Bullet() {
	}


	glm::quat Bullet::GetAngM(void) const {

		return angm_;
	}


	void Bullet::SetAngM(glm::quat angm) {

		angm_ = angm;
	}


	void Bullet::update(float timer) {

		if (!dead) {
			//Update position
			position += trajectory * timer * speed;
			//position.y -= timer;

			//Check timer
			elapsedTime += timer;
			if (timer >= 10.0) {
				dead = true;
			}
			//std::cout << "Bullet position: " << position.x << " " << position.y << " " << position.z << std::endl;
		}
	}

	glm::vec3 Bullet::getPosition() {
		return position;
	}

	void Bullet::setPosition(glm::vec3 pos) {
		position = pos;
	}

	glm::vec3 Bullet::getTrajectory() {
		return trajectory;
	}

	void Bullet::setTrajectory(glm::vec3 traj) {
		trajectory = traj;
	}

} // namespace game
