/////////////////////////////////////////////////////////////////////////////////////////////        
/// GameEngine.cpp
///
/// Implementation for a simple example game engine.
///
/// @author Maurice Hendrix
///////////////////////////////////////////////////////////////////////////////////////////// 
#include "GameEngine.h"
#include "HoverCraft.h"
#include "getbmp.h"
#include <iostream>
using namespace std;
vector<GameObject*> GameEngine::objects; //The definition of static variables needs to be repeated in the cpp file.
int GameEngine::oldTimeSinceStart;
int GameEngine::newTimeSinceStart;
bool GameEngine::debugMode;
GameObject* GameEngine::cameraFollow;
unsigned int GameEngine::base; // Generate display list base. 
float X = 5;
float Y = 50;
float red, green, blue;
float rotatex, rotatey, rotatez, angle;
int oldTimeSinceStart;
int newTimeSinceStart;
int cameraMode = 1;

void GameEngine::initEngine(int argc, char **argv, const char* windowTitle, bool debug, int width, int height) {

	//Init glut.
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Billard");

	glewExperimental = GL_TRUE;
	glewInit();

	glutDisplayFunc(displayFunc);
	glutReshapeFunc(reshapeFunc);

	//Lambda functions to link our code to glut's keydown and keyup. Our function deals with both regular and special keys in one.
	glutKeyboardFunc([](unsigned char key, int x, int y) {
		GameObject::keys[key] = true;
		//if we press escape, exit the game
		if (key == '1') {
			red = red + 0.1;
			glClearColor(red, green, blue, 0.0);
		}
		if (key == '2') {
			green = green + 0.1;
			glClearColor(red, green, blue, 0.0);
		}
		if (key == '3') {
			blue = blue + 0.1;
			glClearColor(red, green, blue, 0.0);
		}
		if (key == '4') {
			blue = 0;
			red = 0;
			green = 0;
			glClearColor(red, green, blue, 0.0);
		}
		if (key == 'f') {
			cameraMode++;
			if (cameraMode == 5) {
				cameraMode = 1;
			}
		}
		if (key == 'q') {
			if (debugMode == true) {
				debugMode = false;
			}
			else
			{
				debugMode = true;
			}
		}
		if (key == 'w') {
			X--;
		}
		if (key == 's') {
			X++;
		}
		if (key == 'a') {
			Y++;
		}
		if (key == 'd') {
			Y--;
		}
		if (key == 'z') {
			angle = 0;
			rotatex = 0;
			rotatey = 0;
			rotatez++;
		}
		if (key == 'x') {
			angle = 0;
			rotatez = 0;
			rotatey = 0;
			rotatex++;
		}
		if (key == 'y') {
			angle = 0;
			rotatex = 0;
			rotatez = 0;
			rotatey++;
		}
		if (key == 'c') {
			angle = angle + 5;
		}
		if (key == 27) {
			cleanup();
			exit(0);
		}
	});

	glutKeyboardUpFunc([](unsigned char key, int x, int y) {
		GameObject::keys[key] = false;
	});

	glutSpecialFunc([](int key, int x, int y) {
		GameObject::specialKeys[key] = true;
	});

	glutSpecialUpFunc([](int key, int x, int y) {
		GameObject::specialKeys[key] = false;
	});

	glutIdleFunc(updateGame);

}

void GameEngine::displayFunc() {
	//Prepare for drawing all objects.
	glClearColor(red, green, blue, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (cameraFollow != NULL) {
		if (cameraMode == 1) {
			gluLookAt((cameraFollow->position.x - (cameraFollow->heading.x * 25)), (cameraFollow->position.y - (cameraFollow->heading.y * 25)), (cameraFollow->position.z * (cameraFollow->heading.z)), cameraFollow->position.x, cameraFollow->position.y, cameraFollow->position.z, 0.0, 0.0, -1.0);
		}
		else if (cameraMode == 2) {
			gluLookAt(X + 30, Y, -0.0f, X, Y - 5, 7.0, 0.0, 0.0, -1.0);
		}
		else if (cameraMode == 3) {
			gluLookAt((cameraFollow->position.x - (cameraFollow->heading.x)), (cameraFollow->position.y - (cameraFollow->heading.y)), (cameraFollow->position.z + (cameraFollow->heading.z ))- 50, cameraFollow->position.x, cameraFollow->position.y, cameraFollow->position.z, 0.0, 0.0, -1.0);
		}
		else if (cameraMode == 4) {
			gluLookAt((cameraFollow->position.x - (cameraFollow->heading.x)), (cameraFollow->position.y - (cameraFollow->heading.y)), (cameraFollow->position.z * (cameraFollow->heading.z)), cameraFollow->position.x, cameraFollow->position.y, cameraFollow->position.z, 0.0, 0.0, -1.0);
		}
	}
	
	if (GameEngine::debugMode == false) {
		glPushMatrix();
		glTranslatef(cameraFollow->position.x, cameraFollow->position.y, cameraFollow->position.z - 1000);
		glutWireSphere(2.0, 10, 10);
		glPopMatrix();
	}
	
	//Call drawscene for all gameobjects.
	for (vector<GameObject*>::size_type i = 0; i != objects.size(); i++) {
		objects[i]->drawScene();
	}
	glutSwapBuffers(); //Finish Draw Scene.
}

void GameEngine::reshapeFunc(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(60.0, (float)w / (float)h, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
};

//Add a new gameobject to the scene.
void GameEngine::addGameObject(GameObject* object, bool camFollow) {
	objects.push_back(object);
	if (camFollow) {
		cameraFollow = object;
	}
	base = glGenLists(1);
	base = object->setupDrawing(base);
	object->start();
}

//Update the game state.
void GameEngine::updateGame() {
	//Calculate delta time (in mili seconds).
	oldTimeSinceStart = newTimeSinceStart;
	newTimeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	int deltaTime = newTimeSinceStart - oldTimeSinceStart;

	//If the last frame was rendered less than 1 ms ago, the detalaTime will be 0 ms. This causes problems in calculations, so sleep for 1ms to adjust.
	if (deltaTime == 0) {
		//Sleep(1);
		Sleep(5);
		newTimeSinceStart = glutGet(GLUT_ELAPSED_TIME);
		deltaTime = newTimeSinceStart - oldTimeSinceStart;
	}

	//Remove any inactive objects first.
	for (vector<GameObject*>::size_type i = 0; i != objects.size(); i++) {
		if (!objects[i]->active) {
			delete objects[i];
			objects.erase(objects.begin() + i);
		}
	}

	//Run update for all game objects.
	for (vector<GameObject*>::size_type i = 0; i != objects.size(); i++) {
		objects[i]->update(deltaTime);
	}
	
	//Test collisions in a naive way for every pair of gameobjects (note calculations will explode when you increase the amount of gameobjects. Can you think of a better way?
	for (vector<GameObject*>::size_type i = 0; i != objects.size(); i++) {
		for (vector<GameObject*>::size_type j = i + 1; j != objects.size(); j++) {
			if (objects[i]->collider != NULL) {
				if (objects[i]->collider->collidesWith(objects[j]->collider)) {
					objects[i]->collides(objects[j]->collider);
					objects[j]->collides(objects[i]->collider);
				}
			}
		}
	}

	//Done so indicate that it's time to redraw.
	glutPostRedisplay();
}

void GameEngine::startEngine() {
	//Explain main interaction with scene.
	GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat light_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat light_specular[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_position[] = { 100.0, 100.0, 100.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	cout << "Press escape to exit." << endl;
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//Start game loop.
	glutMainLoop();
}

//Here we delete pointer objects for when we exit, to prevent memory leaks.
void GameEngine::cleanup() {
	for (auto it = objects.begin(); it != objects.end(); ++it) {
		delete *it;
	}
	objects.clear();
}