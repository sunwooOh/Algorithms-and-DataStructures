#include<assert.h>
#include"List.h"

using namespace std;

template <class T>
class Graph {
public:
    Graph(int n = 0) {
        assert(n >= 0);
        numNodes = n;
        if (n == 0)
            p = NULL;
        else {
            p = new T*[n];
            for (int i = 0; i < n; i++) {
                p[i] = new T[n];
                for (int j = 0; j < n; j++)
                    p[i][j] = 0;
            }
        }
    }
    bool isEdge(int i, int j) {
        assert(i >= 0 && j >= 0);
        return p[i][j] != 0;
    }
    T getEdge(int i, int j) {
        assert(i >= 0 && j >= 0);
        return p[i][j];
    }
    void setEdge(int i, int j, T x) {
        assert(i >= 0 && j >= 0);
        p[i][j] = x;
    }
    int getSize() { return numNodes; }
    void printG() {
        for (int i = 0; i < numNodes; i++) {
            for (int j = 0; j < numNodes; j++)
                cout << p[i][j] << " ";
            
            cout << endl;
        }
    }
    
private:
    T** p;
    int numNodes;
};