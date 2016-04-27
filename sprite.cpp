#include "sprite.h"

Sprite::Sprite(GLuint textureBufferID, Vector2 position)
{
	_textureBufferID = textureBufferID;
	_position = position;
}

void Sprite::setRotation(GLfloat rotation)
{
	_rotation = rotation;
}

GLfloat Sprite::getRotation()
{
	return _rotation;
}

void Sprite::setPosition(Vector2 newPosition)
{
	_position = newPosition;
}
Vector2 Sprite::getPosition()
{
	return _position;
}

void Sprite::setRotationVelocity(GLfloat rotationVelocity)
{
	_rotationVelocity = rotationVelocity;
}

GLfloat Sprite::getRotationVelocity()
{
	return _rotationVelocity;
}

void Sprite::setVelocity(Vector2 newPosition)
{
	_velocity = newPosition;
}

Vector2 Sprite::getVelocity()
{
	return _velocity;
}

void Sprite::render()
{
	glBindTexture(GL_TEXTURE_2D, _textureBufferID);
	glLoadIdentity();
	
	glTranslatef(_position.x + Square_Size/2, _position.y + Square_Size/2, 0);
	glRotatef(_rotation, 0, 0, 1.0f);	
	
	glDrawArrays(GL_QUADS,0,4);
}

void Sprite::update()
{
	_position = addVector2(_position, _velocity);
	_rotation += _rotationVelocity;
}
