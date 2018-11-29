#include "bullet.h"

namespace game {

	Bullet::Bullet(const std::string name, const Resource *geometry, const Resource *material, glm::vec3 pos, glm::vec3 traj) : SceneNode(name, geometry, material) {
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


	void Bullet::Update(float timer) {

		//Update position
		position += trajectory * timer * speed;
		position.y -= timer;

		//Check timer
		elapsedTime += timer;
		if (timer >= 10.0) {
			dead = true;
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
