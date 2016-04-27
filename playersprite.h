#ifndef PLAYERSPRITE_H
#define PLAYERSPRITE_H

#include "prefix.h"
#include "sprite.h"

class PlayerSprite: public Sprite
{
	private:
		BoundingBox _boundingBox;
		
	public:
		PlayerSprite(GLuint textureBufferID, Vector2 position);
		void update();
		void setBoundingBox(BoundingBox boundingBox);
		
};

#endif
