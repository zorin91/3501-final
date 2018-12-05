#include "rocket.h"

namespace game {

	Rocket::Rocket(const Resource *geometry, const Resource *material, glm::vec3 pos, glm::vec3 traj){
		position = pos;
		trajectory = traj;
	}


	Rocket::~Rocket() {
	}


	glm::quat Rocket::GetAngM(void) const {

		return angm_;
	}


	void Rocket::SetAngM(glm::quat angm) {

		angm_ = angm;
	}


	void Rocket::update(float timer) {
		
		//Update position
		position += trajectory * timer * speed;
		position.y -= timer * speed / 2;

		//Check timer
		elapsedTime += timer;
		if (timer >= 10.0) {
			dead = true;
		}
	}

	glm::vec3 Rocket::getPosition() {
		return position;
	}

	void Rocket::setPosition(glm::vec3 pos) {
		position = pos;
	}
	
	glm::vec3 Rocket::getTrajectory() {
		return trajectory;
	}

	void Rocket::setTrajectory(glm::vec3 traj) {
		trajectory = traj;
	}

} // namespace game
