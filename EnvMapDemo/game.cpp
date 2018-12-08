
#include <iostream>
#include <time.h>
#include <sstream>

#include "game.h"
#include "path_config.h"
#include "model.h"


namespace game {

// Some configuration constants
// They are written here as global variables, but ideally they should be loaded from a configuration file

// Main window settings
const std::string window_title_g = "Demo";
const unsigned int window_width_g = 640;
const unsigned int window_height_g = 480;
const bool window_full_screen_g = false;

// Viewport and camera settings
float camera_near_clip_distance_g = 0.01;
float camera_far_clip_distance_g = 10000.0;
float camera_fov_g = 50.0; // Field-of-view of camera
const glm::vec3 viewport_background_color_g(0.0, 0.0, 0.0);
glm::vec3 camera_position_g(0.0, 0.0, 0.0);
glm::vec3 camera_look_at_g(0.0, 0.0, -10.0);
glm::vec3 camera_up_g(0.0, 1.0, 0.0);

// Materials
const std::string material_directory_g = MATERIAL_DIRECTORY;


Game::Game(void){

    // Don't do work in the constructor, leave it for the Init() function
}


void Game::Init(void){

    // Run all initialization steps
    InitWindow();
    InitView();
    InitEventHandlers();

    // Set variables
    animating_ = true;
}


void Game::InitWindow(void){

    // Initialize the window management library (GLFW)
    if (!glfwInit()){
        throw(GameException(std::string("Could not initialize the GLFW library")));
    }

    // Create a window and its OpenGL context
    if (window_full_screen_g){
        window_ = glfwCreateWindow(window_width_g, window_height_g, window_title_g.c_str(), glfwGetPrimaryMonitor(), NULL);
    } else {
        window_ = glfwCreateWindow(window_width_g, window_height_g, window_title_g.c_str(), NULL, NULL);
    }
    if (!window_){
        glfwTerminate();
        throw(GameException(std::string("Could not create window")));
    }

    // Make the window's context the current one
    glfwMakeContextCurrent(window_);

    // Initialize the GLEW library to access OpenGL extensions
    // Need to do it after initializing an OpenGL context
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK){
        throw(GameException(std::string("Could not initialize the GLEW library: ")+std::string((const char *) glewGetErrorString(err))));
    }
}


void Game::InitView(void){

    // Set up z-buffer
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Set viewport
    int width, height;
    glfwGetFramebufferSize(window_, &width, &height);
    glViewport(0, 0, width, height);

    // Set up camera
    // Set current view
    camera_.SetView(camera_position_g, camera_look_at_g, camera_up_g);
    // Set projection
    camera_.SetProjection(camera_fov_g, camera_near_clip_distance_g, camera_far_clip_distance_g, width, height);
}


void Game::InitEventHandlers(void){

    // Set event callbacks
    glfwSetKeyCallback(window_, KeyCallback);
    glfwSetFramebufferSizeCallback(window_, ResizeCallback);

    // Set pointer to game object, so that callbacks can access it
    glfwSetWindowUserPointer(window_, (void *) this);
}


void Game::SetupResources(void){

    // Create a torus
    resman_.CreateTorus("TorusMesh");

    // Create a cube for the skybox
    resman_.CreateCube("CubeMesh2");

    // Load material to be applied to torus
    std::string filename = std::string(MATERIAL_DIRECTORY) + std::string("/envmap");
    resman_.LoadResource(Material, "EnvMapMaterial", filename.c_str());

    // Load cube map to be applied to skybox
    filename = std::string(MATERIAL_DIRECTORY) + std::string("/island/island.tga");
    resman_.LoadResource(CubeMap, "LakeCubeMap", filename.c_str());

    // Load material to be applied to skybox
    filename = std::string(MATERIAL_DIRECTORY) + std::string("/skybox");
	resman_.LoadResource(Material, "SkyboxMaterial", filename.c_str());

	// Load a cube from an obj file
	
	//The terrain
	filename = std::string(MATERIAL_DIRECTORY) + std::string("/Ter2.obj");
	resman_.LoadResource(Mesh, "Terrain", filename.c_str());

	// Load texture to be applied to the cube
	filename = std::string(MATERIAL_DIRECTORY) + std::string("/test.png");
	resman_.LoadResource(Texture, "Checker2", filename.c_str());

	// Load material to be applied to the cube
	filename = std::string(MATERIAL_DIRECTORY) + std::string("/textured_material");
	resman_.LoadResource(Material, "TexturedMaterial2", filename.c_str());
	
}



void Game::SetupScene(void){
    // Set background color for the scene
    scene_.SetBackgroundColor(viewport_background_color_g);

    // Create an instance of the torus mesh
    game::SceneNode *torus = CreateInstance("TorusInstance1", "TorusMesh", "EnvMapMaterial", "", "LakeCubeMap");
    // Scale the instance
    torus->Scale(glm::vec3(1.5, 1.5, 1.5));
    torus->Translate(glm::vec3(0.5, 0.5, -10.0));

    // Create skybox
    skybox_ = CreateInstance("CubeInstance1", "CubeMesh2", "SkyboxMaterial");
    skybox_->Scale(glm::vec3(50.0, 20.0, 50.0));

	//Terrain
	game::SceneNode *cube = CreateInstance("CubeInstance2", "Terrain", "TexturedMaterial2", "Checker2");
	// Adjust the instance
	cube->Scale(glm::vec3(3.0, 2.0, 3.0));
}

//When testing stuff on your computer just add the path here
#define PATHTOSHADER "C:/Users/Jacob DiDiodato/Documents/3501 Final/3501-final/EnvMapDemo"
#define PATHTOMODELS "C:/Users/Jacob DiDiodato/Documents/3501 Final/3501-final"
//#define PATHTOSHADER "C:/Users/Alex/Documents/GitHub/3501-final/EnvMapDemo"
//#define PATHTOMODELS "C:/Users/Alex/Documents/GitHub/3501-final"

void Game::MainLoop(void){
	//Model helicopterTest = Model("C:\\Users\\nicho\\Documents\\University Docs\\3rd Year\\[F] Comp 3501 Game Dev III\\3501-final\\gameAssets\\helicopter\\uh60.obj");
	//Shader helicopterShader = Shader("C:\\Users\\nicho\\Documents\\University Docs\\3rd Year\\[F] Comp 3501 Game Dev III\\3501-final\\EnvMapDemo\\helicopterfrag.fs", "C:\\Users\\nicho\\Documents\\University Docs\\3rd Year\\[F] Comp 3501 Game Dev III\\3501-final\\EnvMapDemo\\helicopterfrag.vs");
	//Model enemyhelicopter = Model("C:/Users/nicho/Documents/3501 Final/3501-final/gameAssets/testheli/Mi-28N_Havoc_BF3/havoc.obj");
	//Model tank = Model("C:\\Users\\nicho\\Documents\\University Docs\\3rd Year\\[F] Comp 3501 Game Dev III\\3501-final\\gameAssets\\tank\\test.obj");
	//Model deathstar = Model("C:\\Users\\nicho\\Documents\\University Docs\\3rd Year\\[F] Comp 3501 Game Dev III\\3501-final\\gameAssets\\deathstar\\test.obj");

	//Work the macro magic
	
    Model helicopterTest = Model(PATHTOMODELS "/gameAssets/helicopter/uh60.obj");
    Shader ourShader = Shader(PATHTOSHADER "/helicopterfrag.vs", PATHTOSHADER "/helicopterfrag.fs");
    Model tankModel(PATHTOMODELS "/gameAssets/tank/test.obj");
    Model enemyHeliModel(PATHTOMODELS "/gameAssets/testheli/Mi-28N_Havoc_BF3/body.obj");
	Model enemyHeliRotorModel(PATHTOMODELS "/gameAssets/testheli/Mi-28N_Havoc_BF3/rotor2.obj");
    Model towerModel(PATHTOMODELS "/gameAssets/watchtower/obj/wooden watch tower2.obj");
    Model complexModel(PATHTOMODELS "/gameAssets/Nubian Complex/nubian complex.obj");
    Model deathstarModel(PATHTOMODELS "/gameAssets/deathstar/test.obj");
	

	float rot_factor(glm::pi<float>() / 180);
	float rotation = 0.0f;
	float trans_factor = 0.05;

	float forwardLean = 0.0f;
	float leftLean = 0.0f;
	float rightLean = 0.0f;

	float acceleration = 0.0f;

	glm::vec3 currentFwd = camera_.GetForward();
	glm::vec3 currentSide = camera_.GetSide();


	//Test for weapon systems

	cout << "Before making the bomb!" << endl;

	//Bomb *bomb = new Bomb(resman_.GetResource("CubeMesh2"), resman_.GetResource("TexturedMaterial2"), glm::vec3(0, 1, -1), "bomba", resman_.GetResource("Checker2"));

	cout << "After making the bomb!" << endl;

	//scene_.AddNode(bomb);

	float rotorAngle = 180;
	float rotateBy = 0.1;

	//Bullet * bullet = new Bullet(resman_.GetResource("CubeMesh2"), resman_.GetResource("TexturedMaterial2"), glm::vec3(0, 0, 0), camera_.GetForward());

    // Loop while the user did not close the window
	while (!glfwWindowShouldClose(window_)) {
		cout << "In the loop!" << endl;
		// Animate the scene
		if (animating_) {
			static double last_time = 0;
			double current_time = glfwGetTime();
			if ((current_time - last_time) > 0.01) {
				deltaTime = current_time - last_time;
				//std::cout << deltaTime << std::endl;
				scene_.Update();

				// Animate the sphere
				SceneNode *node = scene_.GetNode("TorusInstance1");
				glm::quat rotation = glm::angleAxis(glm::pi<float>() / 180.0f, glm::vec3(0.0, 1.0, 0.0));
				node->Rotate(rotation);

				for (int i = 0; i < bombs.size(); i++)
				{
					bombs[i]->update(deltaTime);
				}

				last_time = current_time;
			}
		}

		if (glfwGetKey(window_, GLFW_KEY_W))
		{
			acceleration += 0.001;
			forwardLean += 0.005;
			if (forwardLean > 0.2)
			{
				forwardLean = 0.2;
			}
			else
			{
				this->camera_.Pitch(-0.005);
			}
		}
		else if (glfwGetKey(window_, GLFW_KEY_S))
		{
			acceleration -= 0.002;
			forwardLean -= 0.01;
			if (forwardLean < 0)
			{
				forwardLean = 0;
			}
			else
			{
				this->camera_.Pitch(0.01);
			}
		}
		else
		{
			acceleration -= 0.0005;
			forwardLean -= 0.005;
			if (forwardLean < 0)
			{
				forwardLean = 0;
			}
			else
			{
				this->camera_.Pitch(0.005);
			}
		}
		if (glfwGetKey(window_, GLFW_KEY_LEFT))
		{
			this->camera_.Yaw(rot_factor);
			currentFwd = camera_.GetForward();
			currentSide = camera_.GetSide();
		}
		if (glfwGetKey(window_, GLFW_KEY_RIGHT))
		{
			this->camera_.Yaw(-rot_factor);
			currentFwd = camera_.GetForward();
			currentSide = camera_.GetSide();
		}
		if (glfwGetKey(window_, GLFW_KEY_Q))
		{
			this->camera_.Roll(rot_factor);
			rotation += rot_factor;
			if (rotation > 0.2)
			{
				rotation = 0.2;
				this->camera_.Roll(-rot_factor);
			}
			currentSide = camera_.GetSide();
		}
		if (glfwGetKey(window_, GLFW_KEY_E))
		{
			this->camera_.Roll(-rot_factor);
			rotation -= rot_factor;
			if (rotation < -0.2)
			{
				rotation = -0.2;
				this->camera_.Roll(rot_factor);
			}
			currentSide = camera_.GetSide();
		}

		//cout << forwardLean << endl;

		if (glfwGetKey(window_, GLFW_KEY_R))
		{
			this->camera_.Translate(this->camera_.GetUp() * trans_factor);
			this->skybox_->Translate(this->camera_.GetUp() * trans_factor);
		}
		if (glfwGetKey(window_, GLFW_KEY_F))
		{
			this->camera_.Translate(-this->camera_.GetUp() * trans_factor);
			this->skybox_->Translate(-this->camera_.GetUp() * trans_factor);
		}

		if (glfwGetKey(window_, GLFW_KEY_A) == GLFW_PRESS)
		{
			leftLean += 0.005;
			if (leftLean > 0.2)
			{
				leftLean = 0.2;
			}
			else
			{
				this->camera_.Roll(-0.005);
			}

			this->camera_.Translate(-this->camera_.GetSide() * trans_factor);
			this->skybox_->Translate(-this->camera_.GetSide() * trans_factor);
		}
		else if (glfwGetKey(window_, GLFW_KEY_A) == GLFW_RELEASE)
		{
			leftLean -= 0.005;
			if (leftLean < 0)
			{
				leftLean = 0;
			}
			else
			{
				this->camera_.Roll(0.005);
			}
		}

		if (glfwGetKey(window_, GLFW_KEY_D) == GLFW_PRESS)
		{
			rightLean += 0.005;
			if (rightLean > 0.2)
			{
				rightLean = 0.2;
			}
			else
			{
				this->camera_.Roll(0.005);
			}

			this->camera_.Translate(this->camera_.GetSide() * trans_factor);
			this->skybox_->Translate(this->camera_.GetSide() * trans_factor);
		}
		else if (glfwGetKey(window_, GLFW_KEY_D) == GLFW_RELEASE)
		{
			rightLean -= 0.005;
			if (rightLean < 0)
			{
				rightLean = 0;
			}
			else
			{
				this->camera_.Roll(-0.005);
			}
		}

		if (acceleration < 0)
		{
			acceleration = 0;
		}

		if (acceleration > 0.1)
		{
			acceleration = 0.1;
		}

		this->camera_.Translate(currentFwd * acceleration);
		this->skybox_->Translate(currentFwd * acceleration);

        // Draw the scene
		//bomb->Bomb::Draw(&camera_);
        scene_.Draw(&camera_);

		ourShader.use();

		// view/projection transformations
		ourShader.setMat4("projection", camera_.getProjection());
		ourShader.setMat4("view", camera_.getView());

		// render the loaded model
		glm::mat4 model;
		//ISROT

		glm::vec3 yaw   /*X*/ = camera_.getRoll();
		glm::vec3 roll  /*Y*/ = camera_.getPitch();
		glm::vec3 pitch /*Z*/ = camera_.getYaw();

		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));	// it's a bit too big for our scene, so scale it down
		ourShader.setMat4("model", model);
		//ourModel.Draw(ourShader);


		//tank1
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(-50.0, -42., 0.0)); // translate it down so it's at the center of the scene
		model = glm::rotate(model, 180.0f*(180.0f / 3.14159f), glm::vec3(0.0, 1.0, 0.0));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));	// it's a bit too big for our scene, so scale it down
		ourShader.setMat4("model", model);
		tankModel.Draw(ourShader);

		//tank2
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(-70.0, -48, 0.0)); // translate it down so it's at the center of the scene
		model = glm::rotate(model, 180.0f*(180.0f / 3.14159f), glm::vec3(0.0, 1.0, 0.0));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));	// it's a bit too big for our scene, so scale it down
		ourShader.setMat4("model", model);

		tankModel.Draw(ourShader);

		//enemyheli1 (far)
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(-200.0, 0.0, -800.0)); // translate it down so it's at the center of the scene
		model = glm::rotate(model, 90.0f*(180.0f / 3.14159f), glm::vec3(0.0, 1.0, 0.0));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));	// it's a bit too big for our scene, so scale it down
		ourShader.setMat4("model", model);
		enemyHeliModel.Draw(ourShader);
		rotorAngle += rotateBy;
		model = glm::rotate(model, rotorAngle, glm::vec3(0, 1, 0));
		ourShader.setMat4("model", model);
		enemyHeliRotorModel.Draw(ourShader);


		//enemyheli2 (close)
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(0.0, 0.0, -20.0)); // translate it down so it's at the center of the scene
		model = glm::rotate(model, 180.0f*(180.0f / 3.14159f), glm::vec3(0.0, 1.0, 0.0));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));	// it's a bit too big for our scene, so scale it down
		ourShader.setMat4("model", model);
		enemyHeliModel.Draw(ourShader);
		rotorAngle += rotateBy;
		model = glm::rotate(model, rotorAngle, glm::vec3(0, 1, 0));
		ourShader.setMat4("model", model);
		enemyHeliRotorModel.Draw(ourShader);

		//complex
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(-100.0, -100.0, -800.0));
		//model = glm::rotate(model, 180.0f * 180 / 3.14159f, glm::vec3(0.0, 0.0, 1.0));
		model = glm::scale(model, glm::vec3(50.0f, 50.0f, 50.0f));	// it's a bit too big for our scene, so scale it down
		ourShader.setMat4("model", model);
		complexModel.Draw(ourShader);

		//deathstar
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(-700.0, -50.0, -750.0));
		model = glm::rotate(model, 180.0f * 180 / 3.14159f, glm::vec3(0.0, 0.0, 1.0));
		model = glm::scale(model, glm::vec3(120.0f, 120.0f, 120.0f));	// it's a bit too big for our scene, so scale it down
		ourShader.setMat4("model", model);
		deathstarModel.Draw(ourShader);





		/*
		model = glm::translate(model, glm::vec3(0.5, 0.5, -5.0)); // translate it down so it's at the center of the scene
		model = glm::rotate(model, (float)glm::radians(90.0f), glm::vec3(-1, 0, 0));
		//This is to rotate the helicopter but it doesn't work currently
		//model = glm::rotate(model, 1.0f, yaw);
		//model = glm::rotate(model, 1.0f, roll);
		//model = glm::rotate(model, 1.0f, pitch);
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
		helicopterShader.setMat4("model", model);
		//enemyhelicopter.Draw(helicopterShader);

		model = glm::translate(model, glm::vec3(-2.5, 0.5, -5.0)); // translate it down so it's at the center of the scene
		helicopterShader.setMat4("model", model);
		//tank.Draw(helicopterShader);


		//model = glm::mat4();
		helicopterShader.setMat4("model", model);
		helicopterTest.Draw(helicopterShader);
		//enemyhelicopter.Draw(helicopterShader);

		model = glm::mat4();
		model = glm::scale(model, glm::vec3(2.2f, 2.2f, 2.2f));	// it's a bit too big for our scene, so scale it down

		//treeModel.Draw(helicopterShader);
		tankModel.Draw(helicopterShader);
		enemyHeliModel.Draw(helicopterShader);
		towerModel.Draw(helicopterShader);

		model = glm::mat4();
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));	// it's a bit too big for our scene, so scale it down
		helicopterShader.setMat4("model", model);
		complexModel.Draw(helicopterShader);

		model = glm::mat4();
		model = glm::translate(model, glm::vec3(-400.0, 0.0, -250.0));
		model = glm::rotate(model, 180.0f * 180 / 3.14159f, glm::vec3(0.0, 0.0, 1.0));
		model = glm::scale(model, glm::vec3(80.0f, 80.0f, 80.0f));	// it's a bit too big for our scene, so scale it down
		helicopterShader.setMat4("model", model);
		deathstarModel.Draw(helicopterShader);

		*/


        // Push buffer drawn in the background onto the display
        glfwSwapBuffers(window_);

        // Update other events like input handling
        glfwPollEvents();
    }
}


void Game::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){

    // Get user data with a pointer to the game class
    void* ptr = glfwGetWindowUserPointer(window);
    Game *game = (Game *) ptr;

    // Quit game if 'q' is pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }

    // Stop animation if space bar is pressed
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		Bomb *bomb = new Bomb(game->resman_.GetResource("CubeMesh2"), game->resman_.GetResource("TexturedMaterial2"), game->camera_.GetPosition(), "bomba", game->resman_.GetResource("Checker2"));
		bomb->SetScale(glm::vec3(0.3, 0.3, 0.3));
		game->bombs.push_back(bomb);
		game->scene_.AddNode(bomb);
	}
}


void Game::ResizeCallback(GLFWwindow* window, int width, int height){

    // Set up viewport and camera projection based on new window size
    glViewport(0, 0, width, height);
    void* ptr = glfwGetWindowUserPointer(window);
    Game *game = (Game *) ptr;
    game->camera_.SetProjection(camera_fov_g, camera_near_clip_distance_g, camera_far_clip_distance_g, width, height);
}


Game::~Game(){

    glfwTerminate();
}


Asteroid *Game::CreateAsteroidInstance(std::string entity_name, std::string object_name, std::string material_name){

    // Get resources
    Resource *geom = resman_.GetResource(object_name);
    if (!geom){
        throw(GameException(std::string("Could not find resource \"")+object_name+std::string("\"")));
    }

    Resource *mat = resman_.GetResource(material_name);
    if (!mat){
        throw(GameException(std::string("Could not find resource \"")+material_name+std::string("\"")));
    }

    // Create asteroid instance
    Asteroid *ast = new Asteroid(entity_name, geom, mat);
    scene_.AddNode(ast);
    return ast;
}


void Game::CreateAsteroidField(int num_asteroids){

    // Create a number of asteroid instances
    for (int i = 0; i < num_asteroids; i++){
        // Create instance name
        std::stringstream ss;
        ss << i;
        std::string index = ss.str();
        std::string name = "AsteroidInstance" + index;

        // Create asteroid instance
        Asteroid *ast = CreateAsteroidInstance(name, "SimpleSphereMesh", "ObjectMaterial");

        // Set attributes of asteroid: random position, orientation, and
        // angular momentum
        ast->SetPosition(glm::vec3(-300.0 + 600.0*((float) rand() / RAND_MAX), -300.0 + 600.0*((float) rand() / RAND_MAX), 600.0*((float) rand() / RAND_MAX)));
        ast->SetOrientation(glm::normalize(glm::angleAxis(glm::pi<float>()*((float) rand() / RAND_MAX), glm::vec3(((float) rand() / RAND_MAX), ((float) rand() / RAND_MAX), ((float) rand() / RAND_MAX)))));
        ast->SetAngM(glm::normalize(glm::angleAxis(0.05f*glm::pi<float>()*((float) rand() / RAND_MAX), glm::vec3(((float) rand() / RAND_MAX), ((float) rand() / RAND_MAX), ((float) rand() / RAND_MAX)))));
    }
}


SceneNode *Game::CreateInstance(std::string entity_name, std::string object_name, std::string material_name, std::string texture_name, std::string envmap_name){

    Resource *geom = resman_.GetResource(object_name);
    if (!geom){
        throw(GameException(std::string("Could not find resource \"")+object_name+std::string("\"")));
    }

    Resource *mat = resman_.GetResource(material_name);
    if (!mat){
        throw(GameException(std::string("Could not find resource \"")+material_name+std::string("\"")));
    }

    Resource *tex = NULL;
    if (texture_name != ""){
        tex = resman_.GetResource(texture_name);
        if (!tex){
            throw(GameException(std::string("Could not find resource \"")+material_name+std::string("\"")));
        }
    }

    Resource *envmap = NULL;
    if (envmap_name != ""){
        envmap = resman_.GetResource(envmap_name);
        if (!envmap){
            throw(GameException(std::string("Could not find resource \"")+envmap_name+std::string("\"")));
        }
    }

    SceneNode *scn = scene_.CreateNode(entity_name, geom, mat, tex, envmap);
    return scn;
}

} // namespace game
