#include "bomb.h"
#include <iostream>

namespace game {
	Bomb::Bomb(const Resource *geometry, const Resource *material, glm::vec3 pos, std::string name, const Resource* texture) : SceneNode(name, geometry, material, texture, NULL, true) {
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

	bool Bomb::isDead()
	{
		return dead;
	}

	void Bomb::update(float deltaTime){
		//Debug
		//std::cout << "updating" << std::endl;
		
		if (!dead) { //Dont update dead objects, TODO: should delete them
			position.y -= speed * deltaTime;
			elapsedTime += deltaTime;
			SceneNode::SetPosition(Bomb::getPosition());
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

	void Bomb::Draw(Camera* camera)
	{
		SceneNode::Draw(camera);
		if (!dead)
		{
			
		}
	}
            
} // namespace game
