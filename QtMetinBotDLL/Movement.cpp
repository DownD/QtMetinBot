#include "Movement.h"



Movement::Movement()
{
	x_DeltaPathFinding = 10;
	y_DeltaPathFinding = 10;

	use_aStar = true;
}


Movement::~Movement()
{
}

void Movement::Start()
{
}

void Movement::ThreadLoop()
{
}

void Movement::Stop()
{
}

void Movement::Point::getChilds(std::list<Layout>* path)
{
	CPythonBackground* background = sdk->getPythonBackground();

	if (!background->isLocationBlocked(x + x_DeltaPathFinding, y)) {
		path->insert(Point2D(x + 1, y));
	}

	if (!isLocked(x + 1, y + 1)) {
		path->push_back(Point2D(x + 1, y + 1));
	}
	if (!isLocked(x + 1, y - 1)) {
		path->push_back(Point2D(x + 1, y - 1));
	}

	if (!isLocked(x, y + 1)) {
		arroundPoints->push_back(Point2D(x, y + 1));
	}

	if (!isLocked(x, y - 1)) {
		arroundPoints->push_back(Point2D(x, y - 1));
	}

	if (!isLocked(x - 1, y)) {
		arroundPoints->push_back(Point2D(x - 1, y));
	}
	if (!isLocked(x - 1, y + 1)) {
		arroundPoints->push_back(Point2D(x - 1, y + 1));
	}

	if (!isLocked(x - 1, y - 1)) {
		arroundPoints->push_back(Point2D(x - 1, y - 1));
	}
}
