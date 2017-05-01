#include "Solver.h"
#include "FileName.h"


void Solver::checkNode(size_t name)
{
	//first we set the current_node to the current node;
	current_node = name;
	//first we get the positon of the node;
	pos x = nodeList.at(name).PositionX;
	pos y = nodeList.at(name).PositionY;

	//we look left untill checkplace returns true
	int step = 1;
	bool quit = false;
	while (!quit)
	{
		quit = checkPlace(x + step, y);
		step++;
	}

	//now we look right
	step = 1;
	quit = false;
	while (!quit)
	{
		quit = checkPlace(x - step, y);
		step++;
	}

	//now we look down
	step = 1;
	quit = false;
	while (!quit)
	{
		quit = checkPlace(x, y + step);
		step++;
	}

	//lastly we look up
	step = 1;
	quit = false;
	while (!quit)
	{
		quit = checkPlace(x, y - step);
		step++;
	}

	//the node has been check
	//nodeList[name].isChecked = true;

	Maze[x][y] = BLACK;
}

bool Solver::checkPlace(pos x, pos y)
{
	//so first we need to look at the current color and check if its an end node;
	RGBApixel color = Maze[x][y];
	if (color == BLACK)
	{
		return true;
	}
	if (color == BLUE)
	{
		dis dis = caclDistance(nodeList[current_node], x, y) + nodeList[current_node].Distance;
		if (foundEndNode != true)
		{
			//makes a temp node to be place in the list
			//sets the foundEndNode and endNode location

			Node temp = Node(nodeList.size(), dis, current_node, x, y);
			foundEndNode = true;
			endNode = nodeList.size();
			nodeList.push_back(temp);
			return true;
		}
		if (nodeList[endNode].Distance > dis)
		{
			nodeList.at(endNode).Distance = dis;
			nodeList.at(endNode).FromWhere = current_node;
		}
		return true;
	}

	//ok now we need see if this pos is a node or not

	bool canMove[4] = {false, false, false ,false};
	int numberOfMoves = 0;

	//look left
	color = Maze[x + 1][y];
	if (!(color == BLACK))
	{
		canMove[0] = true;
		numberOfMoves++;
	}

	//right
	color = Maze[x - 1][y];
	if (!(color == BLACK))
	{
		canMove[1] = true;
		numberOfMoves++;
	}

	//down
	color = Maze[x][y + 1];
	if (!(color == BLACK))
	{
		canMove[2] = true;
		numberOfMoves++;
	}

	//up
	color = Maze[x][y - 1];
	if (!(color == BLACK))
	{
		canMove[3] = true;
		numberOfMoves++;
	}

	if (numberOfMoves < 3)
	{
		if (canMove[0] == true && canMove[1] == true)
		{
			return false;
		}
		if (canMove[2] == true && canMove[3] == true)
		{
			return false;
		}
		if (numberOfMoves < 2)
		{
			return true;
		}

		addNode(x, y);
	}
	else
	{
		addNode(x, y);
	}
	return true;
}

size_t Solver::drawNodes(size_t name)
{
	const Node& node = nodeList.at(name);
	const Node& otherNode = nodeList.at(node.FromWhere);

	dis start;
	dis distance = caclDistance(node, otherNode);
	//draw on x line
	if (node.PositionX == otherNode.PositionX)
	{
		if (node.PositionY > otherNode.PositionY)
		{
			start = otherNode.PositionY;
		}
		else
		{
			start = node.PositionY;
		}

		for (size_t i = 0; i < distance; i++)
		{
			image.SetPixel(node.PositionX, start + i, GREEN);
		}
	}
	else
	{
		if (node.PositionX > otherNode.PositionX)
		{
			start = otherNode.PositionX;
		}
		else
		{
			start = node.PositionX;
		}

		for (size_t i = 0; i <= distance; i++)
		{
			image.SetPixel(start + i, node.PositionY, GREEN);
		}
	}

	return node.FromWhere;
}

void Solver::addNode(pos x, pos y)
{
	//we need the totalDistane for both branches
	dis totalDistance = caclDistance(nodeList[current_node], x, y) + nodeList[current_node].Distance;
	//first we look at the list to see if there is a node at this location
	for (auto node = nodeList.begin() + current_node; node != nodeList.end(); ++node)
	{
		if (node->PositionX == x && node->PositionY == y)
		{
			if (node->Distance > totalDistance)
			{
				node->Distance = totalDistance;
				node->FromWhere = current_node;
				return;
			}
			return;
		}
	}

	//if its not in the list, we make a new node at the end
	nodeList.push_back(Node(nodeList.size(), totalDistance, current_node, x, y));
}

Solver::Solver(const std::string fileName)
{
	image.ReadFromFile(fileName.c_str());
	fileLocation = fileName;
	Maze.reserve(image.TellWidth());
	for (auto x : Maze)
	{
		x.reserve(image.TellHeight());
	}

	nodeList.reserve(image.TellWidth() * image.TellHeight());
}

int Solver::start()
{
	//std::ios::sync_with_stdio(false);
	//writes the image data into a 2d vector
	for (size_t x = 0; x < image.TellWidth(); ++x)
	{
		Maze.push_back(std::vector<RGBApixel>());
		for (size_t y = 0; y < image.TellHeight(); ++y)
		{
			Maze[x].push_back(image.GetPixel(x, y));
		}
	}


	//first, we find the start node and add it to the nodelist in place 0

	Node startNode = Node();

	for (size_t x = 0; x < Maze.size(); x++)
	{
		for (size_t y = 0; y < Maze[x].size(); y++)
		{
			RGBApixel color = Maze[x][y];
			if (color == RED)
			{
				startNode = Node(0, 0, 0, x, y);
				goto breakOutOfLoop;//breaks out of the nested for loop
			}
		}
	}
breakOutOfLoop: //oooo... i am such a badboy.


	//check if the start node was found, if not it will return early wiht a start not found
	if (startNode == Node())
	{
		std::cout << "could not finde maze start in maze " << fileLocation << '\n';
		return START_NOT_FOUND;
	}

	nodeList.push_back(startNode);


	std::cout << "start found\n";

	//now we check each node in the nodeList
	for (size_t i = 0; i < nodeList.size(); i++)
	{
		checkNode(i);
	}


	//check for end Node, if not then return END_NOT_FOUND
	if (foundEndNode == false)
	{
		std::cout << "could not finde end in maze " << fileLocation << '\n';
		return END_NOT_FOUND;
	}


	//now its time to draw the line from the end to the fount
	size_t temp = endNode;
	while (true)
	{
		temp = drawNodes(temp);
		//mazeData.WriteToFile("output1.bmp"); // testing only
		if (temp == 0)
		{
			break;
		}
	}

	//redrawing the start and end nodes
	image.SetPixel(nodeList[0].PositionX, nodeList[0].PositionY, RED);
	image.SetPixel(nodeList[endNode].PositionX, nodeList[endNode].PositionY, BLUE);

	//we are done, all is left to do is save to disk
	image.WriteToFile(mygetFileName().c_str());

	return 0;
}

bool operator==(const RGBApixel& left, const RGBApixel& right)
{
	return left.Alpha == right.Alpha && left.Blue == right.Blue &&
		left.Green == right.Green && left.Red == right.Red;
}
