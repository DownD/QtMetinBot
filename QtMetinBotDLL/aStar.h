#pragma once
#include <stdlib.h>
#include <vector>
#include <queue>
#include <list>
#include <set>

class Layout {
public:
	//Heuristics function
	virtual float calculateH(Layout & a);

	virtual bool operator==(Layout & a);

	//Returns childrens of that point
	virtual void getChilds(std::list<Layout>* path);

	//Returns cost
	virtual float getG();
};


class aStar
{



public:
	aStar();
	~aStar();

	bool doAStar(Layout* source, Layout* dest, std::list<Layout*>* path);



protected:

	struct Node {

		Node(float distStartToPoint, float distPointToFinal, Layout* pos, Layout* parentPos) : g(distStartToPoint), h(distPointToFinal), pos(pos), f(distStartToPoint+ distPointToFinal), parent(parentPos) {}

		bool operator ==(Node &a) { return a.pos == pos; }
		float g = 0;
		float h = 0;
		float f = 0;

		Layout* parent;
		Layout* pos;
	};

	bool findParentPoint(Layout* p, Layout *parentBuffer);
	bool tracePath(Layout* start, Layout* end, std::list<Layout>* point);
	virtual void getAvailablePointsArround(std::vector<Layout> *arroundPoints, Layout &pos) = 0;


	std::vector<Node> closedList;
};

