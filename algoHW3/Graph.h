#include<assert.h>
#include"List.h"

using namespace std;

template<class T>
class Graph {
public:
	//-----Edge class--------------------------------
	class Edge {
	public:
		Edge(T v = "", double w = -1) {
			incV = v;
			weight = w;
		}
		void setIncV(T ver) { incV = ver; }
		void setWeight(double w) { weight = w; }
		T getIncV() { return incV; }
		double getWeight() { return weight; }

	private:
		T incV;
		double weight;

	};
	//-----------------------------------------------

	Graph(int n = 0) {
		assert(n >= 0);
		numNodes = n;
		if (n == 0)
			G = NULL;
		else {
			G = new List<List<Edge*>*>();
		}
	}

	void setVertex(T i) {
		Edge* toAdd = new Edge(i);
		List<Edge*>* listAdd = new List<Edge*>();
		listAdd->insertTail(toAdd); // <=> listAdd->insertHead(toAdd)
		G->insertTail(listAdd);
	}

	void setEdge(T i, T j, double weight) {
		List<List<Graph<string>::Edge*>*>::Node* ptr = G->getHead();
		Edge* addI = new Edge();
		Edge* addJ = new Edge();

		while (ptr) {
			// i is found in the list
 			if (ptr->getData()->getHead()->getData()->getIncV() == i) {
				addI->setIncV(j);
				addI->setWeight(weight);
				ptr->getData()->insertTail(addI);
			}
			// j is found in the list
			else if (ptr->getData()->getHead()->getData()->getIncV() == j) {
				addJ->setIncV(i);
				addJ->setWeight(weight);
				ptr->getData()->insertTail(addJ);
			}
			ptr = ptr->getNext();
		}

		// if i or j not found in list add them
		if (addI->getWeight() == -1) {
			setVertex(i);
			ptr = G->getTail();
			addI->setIncV(j); addI->setWeight(weight);
			ptr->getData()->insertTail(addI);
		}
		if (addJ->getWeight() == -1) {
			setVertex(j);
			ptr = G->getTail();
			addJ->setIncV(i); addJ->setWeight(weight);
			ptr->getData()->insertTail(addJ);
		}
	}

	int getNumberOfNodes() { return numNodes; }

	List<Edge*>* search(string keyword) {
		List<List<Graph<string>::Edge*>*>::Node* ptr = G->getHead();

		while (ptr) {
			// keyword is found in the list
			if (ptr->getData()->getHead()->getData()->getIncV() == keyword)
				break;
			ptr = ptr->getNext();
		}

		if (ptr)
			return ptr->getData();
		else
			return NULL;
	}

private:
	List<List<Edge*>*>* G;
	int numNodes;
};
