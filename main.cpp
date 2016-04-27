#include "prefix.h"
#include "gamewindow.h"

#define Updates_Per_Second 60

GameWindow *gameWindow;

void GLFWCALL mouseButtonPressed(int button, int action) 
{
	gameWindow->mouseButtonPressed(button, action);
}

int main(int argc, char **argv) {
	glfwInit();
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	glfwOpenWindow(600,600,8,8,8,8,0,0,GLFW_WINDOW);
	glfwSetWindowTitle("OpenGL Game");
	glfwSetMouseButtonCallback(mouseButtonPressed);
	glfwSwapInterval(0);
	glewInit();
	
	gameWindow = new GameWindow(true);
	
	double lastTime = glfwGetTime();
	double deltaTime = 0.0f;
	
	while(gameWindow->getRunning()) {
		gameWindow->render();
		
		deltaTime += (glfwGetTime() - lastTime) * Updates_Per_Second;
		lastTime = glfwGetTime();
		while(deltaTime >= 1.0f) {
			gameWindow->update();		
			-- deltaTime;	
		}	
		
		gameWindow->setRunning(glfwGetWindowParam(GLFW_OPENED));
	}
	delete gameWindow;
	
	glfwTerminate();
	return 0;
}
