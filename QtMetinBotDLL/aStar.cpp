#include "aStar.h"



aStar::aStar()
{
}


aStar::~aStar()
{
}

bool aStar::doAStar(Point2D& source, Point2D& dest, std::list<Point2D> *path)
{
	auto cmp = [](const Node &left,const Node &right) { return ((left.f) < (right.f)); };
	std::set<Node, decltype(cmp)> openList(cmp);

	openList.insert(Node(0, source.distance(&dest), source,source));

	while (!openList.empty()) {

		/*for (auto node : openList) {
			//printf("X:%d  Y: %d  F: %f  G: %f  H:%f\n", node.pos.getIntX(),node.pos.getIntY(), node.f, node.g, node.h);
		}
		//printf("\n\n");
		//system("pause");*/

		Node curr = *openList.begin();
		openList.erase(openList.begin());
		closedList.push_back(curr);

		if (curr.pos == dest) {
			return tracePath(source, dest, path);
		}


		std::vector<Point2D> arroundPoints;
		getAvailablePointsArround(&arroundPoints,curr.pos);

		for (Point2D & arroundPoint : arroundPoints) {
			Node arroundNode = Node(curr.g + 1, arroundPoint.distance(&dest), arroundPoint, curr.pos);

			bool skip = false;
			for (Node node : closedList) {
				if (node == arroundNode) {
					skip = true;
					continue;
				}
			}
			if (skip)
				continue;

			for (const Node & node : openList) {

				if ((Node)node == arroundNode && node.f < arroundNode.f) {
					skip = true;
					(Node)node = arroundNode;
					continue;
				}
			}

			if (skip)
				continue;
			openList.insert(arroundNode);
		}

	}
	return false;
}

bool aStar::findParentPoint(Point2D & p, Point2D *parentBuffer)
{
	for (Node & node : closedList) {
		if (node.pos == p) {//!(node.pos == node.parent)
			*parentBuffer = node.parent;
			return true;
		}
	}
	return false;
}

bool aStar::tracePath(Point2D & start, Point2D& end, std::list<Point2D>* point)
{
	Point2D buffer = end;
	while (!(buffer == start)) {
		point->insert(point->begin(), buffer);
		if (!findParentPoint(buffer, &buffer)) {
			printf("Fail to Tracing X: %d , Y: %d\n",buffer.getIntX(),buffer.getIntY());
			return false;
		}
		printf("Success Tracing To X: %d , Y: %d\n", buffer.getIntX(), buffer.getIntY());
	}

	return true;
}
