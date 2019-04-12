#include "Common.h"

extern GLFWwindow*window;

extern glm::vec3 eye, right, target;

extern float speed;

extern float modelX, modelY, modelZ;
extern float rotX, rotY, rotZ;
extern float scalingX, scalingY, scalingZ;

extern bool hasloaded;
extern int dostuff;
int keyB = 0, keyN = 0, keyM = 0;

bool keydown(int key)
{
	if(glfwGetKey(window, key) == GLFW_PRESS)return 1;
}

int keylift(int key, int oldState, int function)
{
	//printf("oldState: %d\n", oldState);
	int newState = glfwGetKey(window, key);
	if(newState == GLFW_RELEASE && oldState == GLFW_PRESS)
	{
		printf("%d - %d - %d\n", oldState, newState, key);
		dostuff = function;
	}
	oldState = newState;
	return oldState;
}

void keyPress()
{
	//MOVE KEYS
	if(keydown(GLFW_KEY_UP))   eye += target * speed;//Move forward
	if(keydown(GLFW_KEY_DOWN)) eye -= target * speed;//Move backward
	if(keydown(GLFW_KEY_RIGHT))eye +=  right * speed;//Strafe right
	if(keydown(GLFW_KEY_LEFT)) eye -=  right * speed;//Strafe left
	//X AXIS TRANSLATION
	if(keydown(GLFW_KEY_I))modelX += 3;
	if(keydown(GLFW_KEY_J))modelX -= 3;
	//Y AXIS TRANSLATION
	if(keydown(GLFW_KEY_O))modelY += 3;
	if(keydown(GLFW_KEY_K))modelY -= 3;
	//Z AXIS TRANSLATION
	if(keydown(GLFW_KEY_P))modelZ += 3;
	if(keydown(GLFW_KEY_L))modelZ -= 3;
	//EULER X ROTATION
	if(keydown(GLFW_KEY_1))rotX += 10;
	if(keydown(GLFW_KEY_2))rotX -= 10;
	//EULER Y ROTATION
	if(keydown(GLFW_KEY_3))rotY += 10;
	if(keydown(GLFW_KEY_4))rotY -= 10;
	//EULER Z ROTATION
	if(keydown(GLFW_KEY_5))rotZ += 10;
	if(keydown(GLFW_KEY_6))rotZ -= 10;
	//X AXIS SCALING
	if(keydown(GLFW_KEY_F1))scalingX += 3;
	if(keydown(GLFW_KEY_F2))scalingX -= 3;
	//Y AXIS SCALING
	if(keydown(GLFW_KEY_F3))scalingY += 3;
	if(keydown(GLFW_KEY_F4))scalingY -= 3;
	//Z AXIS SCALING
	if(keydown(GLFW_KEY_F5))scalingZ += 3;
	if(keydown(GLFW_KEY_F6))scalingZ -= 3;
	
	//LOAD MODELS	
	keyB = keylift(GLFW_KEY_B, keyB, 1);
	keyN = keylift(GLFW_KEY_N, keyN, 2);
	keyM = keylift(GLFW_KEY_M, keyM, 3);
}