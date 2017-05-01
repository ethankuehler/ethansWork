#pragma once

typedef unsigned short pos, dis;


struct Node
{
	//position on img
	pos PositionX;
	pos PositionY;

	//is checked
	//bool isChecked = false;

	//total distance from start
	dis Distance;
	//the name/ location of this node
	size_t Name;
	//the name/location of the previous node
	size_t FromWhere;

	Node(size_t name, dis dis, size_t from, pos x, pos y);
	Node();
	~Node();
};

bool operator==(Node left, Node right);


dis caclDistance(pos x1, pos y1, pos x2, pos y2);
dis caclDistance(const Node& node, pos x, pos y);
dis caclDistance(const Node& node1, const Node& node2);
