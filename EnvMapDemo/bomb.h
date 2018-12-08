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
            Bomb(const Resource *geometry, const Resource *material, glm::vec3 pos, std::string name, const Resource* texture);

            // Destructor
            ~Bomb();
            
            //Get Set methods
            glm::quat GetAngM(void) const;
            void SetAngM(glm::quat angm);

            glm::vec3 getPosition();
			void setPosition(glm::vec3 pos);
			
			// Update geometry configuration
            void update(float timer);

			void Draw(Camera* camera);

			bool isDead();

        private:
            // Angular momentum of asteroid
            glm::quat angm_;
			glm::vec3 position;
			float speed = 0.1;
			float damage = 100;
			float radius = 15;
			float elapsedTime = 0;
			bool dead = false;
			Resource *geometry;
			Resource *material;

    }; 

} // namespace game

#endif
