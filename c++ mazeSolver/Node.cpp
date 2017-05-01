#include "Node.h"
#include <cmath>


Node::Node(size_t name, dis dis, size_t from, pos x, pos y)
{
	Name = name;
	Distance = dis;
	FromWhere = from;
	PositionX = x;
	PositionY = y;
}

Node::Node()
{
	Name = 0;
	Distance = 0;
	FromWhere = 0;
	PositionX = 0;
	PositionY = 0;
}


Node::~Node()
{
}

bool operator==(Node left, Node right)
{
	return left.PositionX == right.PositionX && left.PositionY == right.PositionY &&
		left.Distance == right.Distance && left.FromWhere == right.FromWhere &&
		left.Name == right.Name;//&& left.isChecked == right.isChecked;
}

dis caclDistance(pos x1, pos y1, pos x2, pos y2)
{
	dis distance = abs((x1 - x2) + (y1 - y2));
	return distance;
}

dis caclDistance(const Node& node, pos x, pos y)
{
	dis distance = abs((node.PositionX - x) + (node.PositionY - y));
	return distance;
}

dis caclDistance(const Node& node1, const Node& node2)
{
	dis distance = abs((node1.PositionX - node2.PositionX) + (node1.PositionY - node2.PositionY));
	return distance;
}
