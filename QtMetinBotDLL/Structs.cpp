#include "Structs.h"

float Point2D::angle(Point2D * p)
{
	float angle = ((atan2(-(p->y - y), p->x - x)) * 180.0f / PI);
	if (angle < 0) 
		angle =- abs(angle);
	angle += 90;
	if(angle>360)
		return angle-360;
	return angle;

}
