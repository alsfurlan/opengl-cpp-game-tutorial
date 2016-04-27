#include "playersprite.h"

PlayerSprite::PlayerSprite(GLuint textureBufferID, Vector2 position):Sprite(textureBufferID,position)
{
	
}

void PlayerSprite::setBoundingBox(BoundingBox boundingBox)
{
	_boundingBox = boundingBox;
}

void PlayerSprite::update()
{
	if(glfwGetKey(GLFW_KEY_UP) && _position.y <= _boundingBox.top) {
		_position = addVector2(_position, makeVector2(0.0f, 1.5f));
	}
	
	if(glfwGetKey(GLFW_KEY_DOWN) && _position.y >= _boundingBox.bottom) {
		_position = addVector2(_position, makeVector2(0.0f, -1.5f));
	}
	
	if(glfwGetKey(GLFW_KEY_LEFT) && _position.x >= _boundingBox.left) {
		_position = addVector2(_position, makeVector2(-1.5f, 0.0f));
	}
	
	if(glfwGetKey(GLFW_KEY_RIGHT) && _position.x <= _boundingBox.right) {
		_position = addVector2(_position, makeVector2(1.5f, 0.0f));
	}
}
		
