#pragma once

#include <vector>
#include <string>
#include <memory>

#include "easyBMP/EasyBMP.h"
#include "Node.h"


const RGBApixel RED = {0x00, 0x00, 0xff, 0x00};
const RGBApixel GREEN = {0x00, 0xff, 0x00, 0x00};
const RGBApixel BLUE = {0xff, 0x00, 0x00, 0x00};
const RGBApixel BLACK = {0x00, 0x00, 0x00, 0x00};

//warring to be return from start
const int START_NOT_FOUND = 1;
const int END_NOT_FOUND = 2;

bool operator==(const RGBApixel& left, const RGBApixel& right);

class Solver
{
	//list of nodes
	std::vector<Node> nodeList;

	//the name of the inputed FileLocation
	std::string fileLocation;

	//the maze data
	BMP image;


	std::vector<std::vector<RGBApixel>> Maze;

	//if endNode found and its locaion
	//this is set by checkPlace func
	bool foundEndNode = false;
	size_t endNode = 0;

	//the current node we are checking
	//this is set by checkNode func
	size_t current_node = 0;

	//checks a node
	void checkNode(size_t name);

	//returns true if node or wall at pos x y
	bool checkPlace(pos x, pos y);

	//draws the inputed node and returns the next node
	size_t drawNodes(size_t name);

	//add a node to a given position
	void addNode(pos x, pos y);

public:
	Solver(const std::string Filelocation);
	Solver() = default;
	int start();
	~Solver() = default;
};
