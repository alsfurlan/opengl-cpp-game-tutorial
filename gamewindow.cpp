#include "prefix.h"
#include "gamewindow.h"
#include "sprite.h"

using namespace std;

typedef struct {
	GLfloat positionCoordinates[3];
	GLfloat textureCoordinates[2];
} VertexData;

VertexData vertices[] = {
	{{-Square_Size/2, -Square_Size/2, 0.0f},{0.0f, 0.0f}},
	{{Square_Size/2, -Square_Size/2, 0.0f},	{1.0f, 0.0f}},
	{{Square_Size/2, Square_Size/2, 0.0f},	{1.0f,1.0f}},
	{{-Square_Size/2, Square_Size/2, 0.0f}, {0.0f, 1.0f}}
};

GameWindow::GameWindow(bool running):_running(running), _height(600), _width(600), _vertexBufferID(0)
{
	setupGL();
	_textureBufferID = loadAndBufferImage("images/rocket.tga");
	_ballTextureBufferID = loadAndBufferImage("images/ball.tga");
	_rockTextureBufferID = loadAndBufferImage("images/rock.tga");
	
	ballsArray = new std::vector<Sprite *>();
	ballsArray->reserve(20);
	
	rockArray = new std::vector<Sprite *>();
	rockArray->reserve(20);
	
	_playerRocket = new PlayerSprite(_textureBufferID, makeVector2(100,300));
	_playerRocket->setBoundingBox(makeBoundingBox(_height,0,0,_width));
}

GameWindow::~GameWindow()
{
	for(std::vector<Sprite *>::iterator spriteIterator = ballsArray->begin(); spriteIterator != ballsArray->end(); spriteIterator++) {
		delete (*spriteIterator);
	}
	delete ballsArray;
	delete _playerRocket;
	glDeleteBuffers(1, &_vertexBufferID);
	glDeleteTextures(1, &_textureBufferID);
	glDeleteTextures(1, &_ballTextureBufferID);
	glDeleteTextures(1, &_rockTextureBufferID);
}

void GameWindow::addRock() 
{
	int locationY = rand() % (int)_height;
	Sprite *newRock = new Sprite(_rockTextureBufferID, makeVector2(_width + Square_Size/2, locationY));
	newRock->setVelocity(makeVector2(-5,0));
	newRock->setRotationVelocity(1);
	rockArray->push_back(newRock);
}

void GameWindow::mouseButtonPressed(int button, int action) {

	if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		Sprite *ball = new Sprite(_ballTextureBufferID, makeVector2(_playerRocket->getPosition().x + Square_Size/2, _playerRocket->getPosition().y));
		ball->setVelocity(makeVector2(8,0));
		ball->setRotationVelocity(-1);
		ballsArray->push_back(ball);
	}
}

void GameWindow::setupGL()
{
	glClearColor(1.0f,1.0f,1.0f,1.0f);
	glViewport(0,0,_width,_height);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,_width, 0, _height);
	glMatrixMode(GL_MODELVIEW);	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	
	glGenBuffers(1, &_vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(VertexData), (GLvoid *) offsetof(VertexData, positionCoordinates));
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, sizeof(VertexData), (GLvoid *) offsetof(VertexData, textureCoordinates));
}

GLuint GameWindow::loadAndBufferImage(const char* filename)
{
	GLFWimage imageData;	
	glfwReadImage(filename, &imageData, NULL);
	GLuint textureBufferID;
	glGenTextures(1, &textureBufferID);
	glBindTexture(GL_TEXTURE_2D, textureBufferID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageData.Width, imageData.Height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData.Data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);	
	glfwFreeImage(&imageData);
	return textureBufferID;
}

void GameWindow::setRunning(bool newRunning)
{
	_running = newRunning;	
}

bool GameWindow::getRunning()
{
	return _running;
}

void GameWindow::render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	_playerRocket->render();
	
	for(std::vector<Sprite *>::iterator spriteIterator = ballsArray->begin(); spriteIterator != ballsArray->end(); spriteIterator++) {
		(*spriteIterator)->render();
	}
	
	for(std::vector<Sprite *>::iterator spriteIterator = rockArray->begin(); spriteIterator != rockArray->end(); spriteIterator++) {
		(*spriteIterator)->render();
	}
	
	glfwSwapBuffers();
}

bool GameWindow::checkForCollision(Sprite *a, Sprite *b)
{
	return !(
		a->getPosition().x + Square_Size/2 <= b->getPosition().x - Square_Size/2 || 
		a->getPosition().x - Square_Size/2 >= b->getPosition().x + Square_Size/2 ||
		a->getPosition().y + Square_Size/2 <= b->getPosition().y - Square_Size/2 ||
		a->getPosition().y - Square_Size/2 >= b->getPosition().y + Square_Size/2
	);
}

void GameWindow::update()
{
	std::vector<std::vector<Sprite *>::iterator> deleteArray; 
	
	for(std::vector<Sprite *>::iterator spriteIteratorRock = rockArray->begin(); spriteIteratorRock != rockArray->end(); spriteIteratorRock++)
	{
		if(checkForCollision(*spriteIteratorRock, _playerRocket)) {
			deleteArray.push_back(spriteIteratorRock);
		}
		
		for(std::vector<Sprite *>::iterator spriteIteratorBall = ballsArray->begin();
			spriteIteratorBall != ballsArray->end(); spriteIteratorBall++) {
			
			if(checkForCollision(*spriteIteratorRock, *spriteIteratorBall)) {
				deleteArray.push_back(spriteIteratorRock);
				deleteArray.push_back(spriteIteratorBall);
			}					
		}
	}
	
	for(std::vector<Sprite *>::iterator spriteIterator = ballsArray->begin(); spriteIterator != ballsArray->end(); spriteIterator++) {
		if(((*spriteIterator)->getPosition()).x > _width + Square_Size) {
			deleteArray.push_back(spriteIterator);
		}
	}
	
	for(std::vector<std::vector<Sprite *>::iterator>::iterator deleteIterator = deleteArray.begin(); deleteIterator != deleteArray.end(); deleteIterator++) {
		if((**deleteIterator)->getVelocity().x > 0) {
			ballsArray->erase(*deleteIterator);	
		} else {
			rockArray->erase(*deleteIterator);	
		}
	}
	
	_playerRocket->update();
	
	static int updates;
	if(updates >= 60) {
		addRock();
		updates = 0;
	}
	++updates;
	
	
	
	for(std::vector<Sprite *>::iterator spriteIterator = ballsArray->begin(); spriteIterator != ballsArray->end(); spriteIterator++) {
		(*spriteIterator)->update();
	}
	
	for(std::vector<Sprite *>::iterator spriteIterator = rockArray->begin(); spriteIterator != rockArray->end(); spriteIterator++) {
		(*spriteIterator)->update();
	}
	
}
