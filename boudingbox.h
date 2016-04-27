#ifndef BOUDINGBOX_H
#define BOUDINGBOX_H

typedef struct {
	int top;
	int bottom;
	int left;
	int right;
} BoundingBox;

BoundingBox	makeBoundingBox(int top, int bottom, int left, int right); 

#endif
