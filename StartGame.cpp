#include "GameEngine.h"
#include "HoverCraft.h"
#include "Obstacle.h"
#include "grass.h"
#include "Track.h" 
int main(int argc, char **argv) {

	//Initialise the engine.
	GameEngine::initEngine(argc, argv, "Billard game", true);
	//Adding an Obstacle.
	GameEngine::addGameObject(new Obstacle(glm::vec3(17, 150, 8.15), { 1.0f,0.5f,0.0f }));
	GameEngine::addGameObject(new Obstacle(glm::vec3(12, 120, 8.15), { 1.0f,0.5f,0.0f }));
	GameEngine::addGameObject(new Obstacle(glm::vec3(7, 140, 8.15), { 1.0f,0.5f,0.0f }));
	GameEngine::addGameObject(new Obstacle(glm::vec3(10, 110, 8.15), { 0.0f,0.0f,0.0f }));

	//Add grass
	GameEngine::addGameObject(new grass(glm::vec3(0, 0, 11), { 0.0f, 1.0f, 0.0f }));


	//Adding Obstacles with different colours.
	GameEngine::addGameObject(new Obstacle(glm::vec3(glm::vec3(2, 90, 8.15))));
	GameEngine::addGameObject(new Obstacle(glm::vec3(glm::vec3(6, 170, 8.15))));
	GameEngine::addGameObject(new Obstacle(glm::vec3(glm::vec3(6, 100, 8.15))));

	//Add a track in this case the pool table
	GameEngine::addGameObject(new Track(glm::vec3(10, 100, 40)));

	//Add a movable ball.
    GameEngine::addGameObject(new HoverCraft(glm::vec3(5, 160, 8.15), { 1, 1, 1 }), true);

	//Start the game engine.
	GameEngine::startEngine();

	return 0;
}