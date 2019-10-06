#pragma once
#include "BotFeature.h"



class Movement : BotFeature{

private:
	class Point : public Layout, Point2D {
		Point(float x, float y) : Point2D(x, y) {};

		//Heuristics function
		virtual float calculateH(Layout & a) {
			Point *p = (Point*)&a;
			return distance(this);
		}

		virtual bool operator==(Layout & a) {
			Point *p = (Point*)&a;
			return Point2D::operator==(*p);
		}

		//Returns childrens of that point
		virtual void getChilds(std::list<Layout>* path);
		

		//Returns cost
		virtual float getG() {
			return gCost;
		}

	private:
		float gCost;
	};

public:
	Movement();
	~Movement();

	// Inherited via BotFeature
	virtual void Start() override;
	virtual void ThreadLoop() override;
	virtual void Stop() override;

private:


	//PathFiding Stuff
	bool use_aStar;

	static float x_DeltaPathFinding;
	static float y_DeltaPathFinding;

};

