#ifndef SPRITE_H
#define SPRITE_H

#include "prefix.h"

#define Square_Size 100

class Sprite
{
	private:
		GLuint _textureBufferID;
		Vector2 _velocity;
		GLfloat _rotation;
		GLfloat _rotationVelocity;
		
	protected:
		Vector2 _position;
		
	public:
		Sprite(GLuint textureBufferID, Vector2 position);
		void setVelocity(Vector2 newVelocity);
		Vector2 getVelocity();
		void setPosition(Vector2 newPosition);
		Vector2 getPosition();
		void setRotation(GLfloat rotation);
		GLfloat getRotation();
		void setRotationVelocity(GLfloat rotationVelocity);
		GLfloat getRotationVelocity();
		void render();
		virtual void update();
};

#endif
