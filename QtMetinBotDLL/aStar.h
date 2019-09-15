#pragma once
#include <stdlib.h>
#include <vector>
#include <queue>
#include <list>
#include <set>


class Point2D {
public:
	Point2D(float x = 0.f, float y = 0.f) { this->x = x; this->y = y; }

	inline float distance(Point2D* p) { return sqrt((p->x - x)*(p->x - x) + (p->y - y)*(p->y - y)); }
	float angle(Point2D *p);
	inline void absoluteY() { y = abs(y); }

	inline int getIntX() { return (int)x; }
	inline int getIntY() { return (int)y; }

	inline void setIntX(int x) { this->x = x; }
	inline void setIntY(int y) { this->y = y; }

	bool operator==(Point2D & a) { return getIntX() == a.getIntX() && getIntY() == a.getIntY(); }

	float x;
	float y;
};


class aStar
{



public:
	aStar();
	~aStar();

	bool doAStar(Point2D &source, Point2D& dest, std::list<Point2D>* path);



protected:

	struct Node {

		Node(float distStartToPoint, float distPointToFinal, Point2D pos, Point2D parentPos) : g(distStartToPoint), h(distPointToFinal), pos(pos), f(distStartToPoint+ distPointToFinal), parent(parentPos) {}

		bool operator ==(Node &a) { return a.pos == pos; }
		float g = 0;
		float h = 0;
		float f = 0;

		Point2D parent;
		Point2D pos;
	};
	bool findParentPoint(Point2D & p, Point2D *parentBuffer);
	bool tracePath(Point2D &start, Point2D& end, std::list<Point2D>* point);
	virtual void getAvailablePointsArround(std::vector<Point2D> *arroundPoints, Point2D &pos) = 0;


	std::vector<Node> closedList;
};

