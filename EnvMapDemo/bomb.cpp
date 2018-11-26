#include "bomb.h"

namespace game {

Bomb::Bomb(const std::string name, const Resource *geometry, const Resource *material, glm::vec3 pos) : SceneNode(name, geometry, material) {
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


void Bomb::Update(float timer){
	position.y -= speed*timer;
	elapsedTime += timer;
	if (timer >= 10.0) {
		dead = true;
	}
}

glm::vec3 Bomb::getPosition() {
	return position;
}

void Bomb::setPosition(glm::vec3 pos) {
	position = pos;
}
            
} // namespace game
