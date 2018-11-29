#ifndef BOMB_H
#define BOMB_H

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

    
    class Bomb : public SceneNode {

        public:
            // Constructor
            Bomb(const std::string name, const Resource *geometry, const Resource *material, glm::vec3 pos);

            // Destructor
            ~Bomb();
            
            //Get Set methods
            glm::quat GetAngM(void) const;
            void SetAngM(glm::quat angm);

            glm::vec3 getPosition();
			void setPosition(glm::vec3 pos);
			
			// Update geometry configuration
            void Update(float timer);

        private:
            // Angular momentum of asteroid
            glm::quat angm_;
			glm::vec3 position;
			float speed = 1.0;
			float damage = 100;
			float radius = 15;
			float elapsedTime = 0;
			bool dead = false;

    }; 

} // namespace game

#endif
