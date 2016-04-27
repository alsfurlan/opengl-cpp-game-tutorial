#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "prefix.h"
#include "playersprite.h"

using namespace std;

class GameWindow
{
	private:
		bool _running;
		GLfloat _height;
		GLfloat _width;
		GLuint _vertexBufferID;
		GLuint _textureBufferID;
		GLuint _ballTextureBufferID;
		GLuint _rockTextureBufferID;
		PlayerSprite *_playerRocket;		
		std::vector<Sprite *> *ballsArray;
		std::vector<Sprite *> *rockArray;
		
		void addRock();
		void setupGL();
		GLuint loadAndBufferImage(const char* filename);		
		
		
	public:
		GameWindow(bool running);
		~GameWindow();
		void setRunning(bool newRunning);
		bool getRunning();
		void render();
		void update();
		void mouseButtonPressed(int button, int key);
		bool checkForCollision(Sprite *a, Sprite *b);
};

#endif
