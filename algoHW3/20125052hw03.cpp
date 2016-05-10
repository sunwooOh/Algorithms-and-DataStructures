#include<iostream> // cout
#include<sstream> // istringstream
#include<string> //string
#include<fstream> // file operations
#include<stdio.h>
#include"Graph.h"

using namespace std;

//-----function declaration-------------------------
void buildGraph(Graph<string>* G, List<Graph<string>::Edge*>* toDest);
List<string>* aSearch(string src, string dest, Graph<string>* G, \
	List<Graph<string>::Edge*>* toDest, double* distance);
Graph<string>::Edge* findNode(List<Graph<string>::Edge*>* list, string keyword);
//--------------------------------------------------

//-----global variable declaration------------------
extern double distance;
//--------------------------------------------------

int main()
{
	//-----get input and build graph-----------------
	int n;
	cout << "How many nodes does your graph have?" << endl;
	cin >> n;
	
	Graph<string>* G = new Graph<string>(n);
	List<Graph<string>::Edge*>* toDest = new List<Graph<string>::Edge*>();
	double* distance = new double();

	buildGraph(G, toDest);
	//-----------------------------------------------
	
	//-----Apply A* algorithm below----------
	string src, dest;
	cout << "Set start point: " << endl;
	cin >> src;
	cout << "Set destination: " << endl;
	cin >> dest;

	List<string>* path = aSearch(src, dest, G, toDest, distance);
	//-----------------------------------------------

	List<string>::Node* ptr = path->getHead();
	cout << "Resulting path:" << endl;
	while (ptr)
	{
		cout << ptr->getData() << " ";
		ptr = ptr->getNext();
	}cout << endl;
	cout << "Total distance: " << *distance << endl;

	return 0;
}

void buildGraph(Graph<string>* G, List<Graph<string>::Edge*>* toDest) {
	//-----get file input---------------------------
	ifstream input;
	string line, area1, area2;
	string alphabets = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	double w;

	input.open("drivingdistances.txt");
	if (input.is_open()) {
		while (getline(input, line)) {
			// checks if input line starts with an alphabet
			if (alphabets.find(line[0]) == string::npos)
				break;

			istringstream iss(line);
			iss >> area1 >> area2 >> w;

			// build graph
			G->setEdge(area1, area2, w);
		}
		input.close();
	}
	else
		cout << "Cannot open file 'drivingdistances.txt'" << endl;

	input.open("straightlinedistances.txt");
	if (input.is_open()) {
		while (getline(input, line)) {
			if (alphabets.find(line[0]) == string::npos)
				break;

			istringstream iss(line);
			iss >> area1 >> area2 >> w;

			// make list of distances to destination
			Graph<string>::Edge* toAdd = new Graph<string>::Edge(area2, w);
			toDest->insertTail(toAdd);
		}
		input.close();
	}
	else
		cout << "Cannot open file 'straightlinedistances.txt'" << endl;
	//-----------------------------------------------
}

Graph<string>::Edge* \
findNode(List<Graph<string>::Edge*>* list, string keyword)
{
	List<Graph<string>::Edge*>::Node* ptr = list->getHead();
	
	while (ptr) {
		if (ptr->getData()->getIncV() == keyword)
			return ptr->getData();
		ptr = ptr->getNext();
	}
	
	return NULL;
}

List<string>* aSearch(string src, string dest, \
	Graph<string>* G, List<Graph<string>::Edge*>* toDest, double* distance)
{
	List<string>* closedSet = new List<string>();
	List<string>* openSet = new List<string>();
	openSet->insertTail(src);

	List<string>* cameFrom = new List<string>();
	string current = src;

	//-----Compute g/f-Score----------------------------------
	List<Graph<string>::Edge*>* fScore = new List<Graph<string>::Edge*>();
	List<Graph<string>::Edge*>* gScore = new List<Graph<string>::Edge*>();

	// initialize gScore
	List<Graph<string>::Edge*>::Node* p = toDest->getHead();
	while (p) {
		if (p->getData()->getIncV() == src) { // if p = src
			Graph<string>::Edge* toAdd = \
				new Graph<string>::Edge(src, 0);
			gScore->insertTail(toAdd);
		}
		else {
			Graph<string>::Edge* toAdd = \
				new Graph<string>::Edge(p->getData()->getIncV(), 10000);
			gScore->insertTail(toAdd);
		}
		p = p->getNext();
	}
	Graph<string>::Edge* min = new Graph<string>::Edge();
	// initialize fScore
	p = toDest->getHead();
	while (p) {
		if (p->getData()->getIncV() == src) { // if p = src (Gwangju)
			Graph<string>::Edge* toAdd = \
				new Graph<string>::Edge(src, p->getData()->getWeight());
			fScore->insertTail(toAdd);
			min->setIncV(src); min->setWeight(p->getData()->getWeight());
		}
		else {
			string pStr = p->getData()->getIncV();
			Graph<string>::Edge* toAdd = \
				new Graph<string>::Edge(p->getData()->getIncV(), 10000);
			fScore->insertTail(toAdd);
		}
		p = p->getNext();
	}
	//--------------------------------------------------------

	while (!openSet->isEmpty()) { // while open set not empty
		// look for minimum fScore value in openSet
		List<string>::Node* nodeOpen = openSet->getHead();
		min->setWeight(10000);
		while (nodeOpen) {
			Graph<string>::Edge* found = \
				findNode(fScore, nodeOpen->getData());
			if (found->getWeight() < min->getWeight()) {
				min->setIncV(nodeOpen->getData());
				min->setWeight(findNode(fScore, nodeOpen->getData())->getWeight());
			}
			nodeOpen = nodeOpen->getNext();
		}

		// min has minimum fScore value
		// give current minimum
		current = min->getIncV();

		if (current == dest) {
			*distance = min->getWeight();
			cameFrom->insertTail(current);
			return cameFrom;
		}

		openSet->remove(current);
		closedSet->insertTail(current);

		double tentGScore;
		//-----visit current--------------------------------------------
		// look for current in G
		List<Graph<string>::Edge*>* neighbors = \
			new List<Graph<string>::Edge*>();
		neighbors = G->search(current);

		// for each neighbors
		List<Graph<string>::Edge*>::Node* eachNei = \
			new List<Graph<string>::Edge*>::Node();

		eachNei = neighbors->getHead()->getNext();
		//	(getHead is src node, next nodes are its neighbors)

		while (eachNei) {
			if (closedSet->search(eachNei->getData()->getIncV())) {
				eachNei = eachNei->getNext();
				continue;
			}

			// look for current gScore
			tentGScore = findNode(gScore, current)->getWeight() + \
				eachNei->getData()->getWeight();
			
			// If neighbor is not in openSet, discover new node
			if (!openSet->search(eachNei->getData()->getIncV()))
				openSet->insertTail(eachNei->getData()->getIncV());

			// not the best path
			else if (tentGScore >= \
				findNode(gScore, eachNei->getData()->getIncV())->getWeight()) {
				eachNei = eachNei->getNext();
				continue;
			}

			//// is the best path
			if (!cameFrom->search(current))
				cameFrom->insertTail(current);
			// if cameFrom doesn't have current, insert

			// set gScore[neighbor] to tentGScore
			Graph<string>::Edge* toAdd1 = new Graph<string>::Edge();
			toAdd1->setWeight(tentGScore);
			toAdd1->setIncV(eachNei->getData()->getIncV());
			gScore->remove(findNode(gScore, eachNei->getData()->getIncV()));
			gScore->insertTail(toAdd1);

			// set fScore[neighbor] to gScore[neighbor] + toDest
			Graph<string>::Edge* toAdd2 = new Graph<string>::Edge();
			toAdd2->setIncV(eachNei->getData()->getIncV());
			toAdd2->setWeight(tentGScore\
				+ findNode(toDest, eachNei->getData()->getIncV())->getWeight());
			fScore->remove(findNode(fScore, eachNei->getData()->getIncV()));
			fScore->insertTail(toAdd2);
			
			eachNei = eachNei->getNext();
		}
		//--------------------------------------------------------------
	}
	return NULL;
}
