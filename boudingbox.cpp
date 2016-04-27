#include "boudingbox.h"

BoundingBox	makeBoundingBox(int top, int bottom, int left, int right)
{
	BoundingBox boundingBox;
	boundingBox.top = top;
	boundingBox.bottom = bottom;
	boundingBox.left = left;
	boundingBox.right = right;
	return boundingBox;
}
