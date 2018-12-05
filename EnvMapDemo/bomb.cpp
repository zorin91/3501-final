#include "bomb.h"
#include <iostream>

namespace game {

	Bomb::Bomb(const Resource *geometry, const Resource *material, glm::vec3 pos){
		position = pos;
	
	}


	Bomb::~Bomb(){
	}


	glm::quat Bomb::GetAngM(void) const {

		return angm_;
	}


	void Bomb::SetAngM(glm::quat angm){

		angm_ = angm;
	}


	void Bomb::update(float deltaTime){
		//Debug
		//std::cout << "updating" << std::endl;
		
		if (!dead) { //Dont update dead objects, TODO: should delete them
			position.y -= speed * deltaTime;
			elapsedTime += deltaTime;
			if (elapsedTime >= 10.0) {
				dead = true;
				//std::cout << "Dead" << std::endl;
			}
			//Debug: print their position
			//std::cout << "Position.y: " << position.y << std::endl;
		}
	}

	glm::vec3 Bomb::getPosition() {
		return position;
	}

	void Bomb::setPosition(glm::vec3 pos) {
		position = pos;
	}

	void draw() {

	}
            
} // namespace game
