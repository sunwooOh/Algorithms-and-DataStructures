#include<iostream> // cout
#include<sstream> // istringstream
#include<string> //string
#include<fstream> // file operations
#include<stdio.h>
#include<bitset> // tbd
#include"Graph.h"

using namespace std;

//-----function declaration-------------------------
List<string>* buildGraph(Graph<double>* G);
double TSP(int srcNode, Graph<double>* G, int numNodes, List<string>* index, string origSrc);
double** recC(Graph<double>* D, int numNodes, List<int>* travel, int src);
void recC(double** C, int S, int j, Graph<double>* D, List<int>* travel, bool flag);
void getAns(double** C, int src, int numNodes, Graph<double>* G, List<string>* index, string origSrc);
//--------------------------------------------------

//-----global variable declaration------------------
//--------------------------------------------------

int main()
{
    //-----get input and build graph-----------------
    int n;
    string src;
    List<string>* areaIndex = new List<string>();
    
    cout << "How many nodes does your graph have?" << endl;
    cin >> n;
//    n = 10;
//    n = 5;
    
    cout << "Where is the start point?" << endl;
    cin >> src;
//    src = "Gwangju";
//    src = "B";
    
    Graph<double>* G = new Graph<double>(n);
    //double* distance = new double();
    
    areaIndex = buildGraph(G);
    //-----------------------------------------------
    
    string origSrc;
    
    //-----preprocess--------------------------------
    int i = 0;
    List<string>::Node* srcNode = areaIndex->getHead();
    while (srcNode) {
        if (srcNode->getData() == src) break;
        srcNode = srcNode->getNext();
        i++;
    }
    if (i != 0) {
//        G->printG(); // tbd
//        cout << endl << endl;
//        
//        // swap src & head in areaIndex
//        areaIndex->remove(src);
//        areaIndex->insertHead(src);
//        
//        // swap src & head in Graph
//        for(int j = 1; j < n; j++){
//            if(j != i){
//                double tmp;
//                tmp = G->getEdge(0, j);
//                G->setEdge(0, j, G->getEdge(i, j)); // set src to head
//                G->setEdge(j, 0, G->getEdge(i, j));
//                G->setEdge(i, j, tmp); // set head to src
//                G->setEdge(j, i, tmp);
//            }
//        }
//        G->printG(); // tbd
        
        origSrc = src;
        
        i = 0;
    }
//    cout << areaIndex->getHead()->getData();
    
    //-----------------------------------------------
    
    //-----TSP---------------------------------------
    double path;
    
    path = TSP(i, G, n, areaIndex, origSrc);
//    cout << path;
    //-----------------------------------------------
    
    
    return 0;
}

List<string>* buildGraph(Graph<double>* G) {
    //-----get file input---------------------------
    ifstream input;
    string line, area1, area2;
    // string prev = src;
    string alphabets = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    double w;
    List<string>* areaIndex = new List<string>();
    int i = 0, j = 0;
    
    
    input.open("alldistances.txt");
    if (input.is_open()) {
        while (getline(input, line)) {
            // checks if input line starts with an alphabet
            if (line[0] == '#')
                break;
            if (alphabets.find(line[0]) == string::npos)
                continue;
            
            istringstream iss(line);
            iss >> area1 >> area2 >> w;
            
            // create dictionary using list
            if (!(areaIndex->search(area1)))
                areaIndex->insertTail(area1);
            if (!(areaIndex->search(area2)))
                areaIndex->insertTail(area2);
            
            // convert area -> int using index
            List<string>::Node* found = areaIndex->getHead();
            i = 0;
            while (found) {
                if (found->getData() == area1)
                    break;
                found = found->getNext();
                i++;
            }
            j = 0;
            found = areaIndex->getHead();
            while (found) {
                if (found->getData() == area2)
                    break;
                found = found->getNext();
                j++;
            }
            
            // build graph
            G->setEdge(i, j, w);
            G->setEdge(j, i, w);
        }
        input.close();
        
        return areaIndex;
    }
    else
        cout << "Cannot open file 'drivingdistances.txt'" << endl;
    return NULL;
}

double TSP(int srcNode, Graph<double>* G, int numNodes, List<string>* index, string origSrc)
{
    //-----TSP---double* recC------------------------------
    // find shortest dist(SD) and shortest path(SP)
    int numSubsets = (1 << (numNodes + 1)) - 1;
    
    double** C;
    C = new double*[numSubsets+1];
    for (int i = 0; i < numSubsets+1; i++)
        C[i] = new double[numNodes + 2];
    
    //double* C = new double[numSubsets * (numNodes + 1)];
    
    // start TSP (iteration & recursion)
    
    // post process G : put int on i == j and else
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            if (i == j)
                G->setEdge(i, j, 10000); //numeric_limits<double>::infinity());
            else if (G->getEdge(i, j) == 0)
                G->setEdge(i, j, 10000); //numeric_limits<double>::infinity());
        }
    }
    
    List<int>* travel = new List<int>();
    
    C = recC(G, numNodes, travel, srcNode);
    
    getAns(C, srcNode, numNodes, G, index, origSrc);
    //-----------------------------------------------------
    
    
    //-----look for minimum--------------------------------
    double min = 10000; //numeric_limits<double>::infinity();
    for (int j = 1; j <= numNodes; j++) {
        if ((C[((1<<numNodes)-1)][j] + G->getEdge(j - 1, srcNode)) < min)
            min = C[((1<<numNodes)-1)][j] + G->getEdge(j - 1, srcNode);
    }	// might be deleted
    //-----------------------------------------------------
    
    /*cout << "Final:" << min << endl;
     List<int>::Node* ptr = travel->getHead();
     while (ptr) {
     cout << ptr->getData() << " ";
     ptr = ptr->getNext();
     } cout << endl << "end" << endl;*/
    
    
    // return
    return min;
}

double** recC(Graph<double>* D, int numNodes, List<int>* travel, int src)
{
    //-----TSP---------------------------------------------
    // find shortest dist(SD) and shortest path(SP)
    int j_set, j_counter = 0;
    int numSubsets = (1 << (numNodes + 1)) - 1;
    //double min;
    
    
    //double* C = new double[numSubsets * (numNodes + 5)];
    
    double** C;
    C = new double*[numSubsets+1];
    for (int i = 0; i < numSubsets+1; i++)
        C[i] = new double[numNodes + 2];
    
    for (int i = 1; i <= numSubsets; i++)
        for (int j = 1; j <= numNodes + 1; j++)
            C[i][j] = 10000; //numeric_limits<double>::infinity();
    
    
    C[src+1][1] = 0;
    
    bool flag = false;
    
    // start iteration
    for (int s = 1; s < (1 << (numNodes - 1)); s++) // 512 iterations
    {
        
        int left = s >> src;
        int right = s - (left << src);
        int s_withOne = (left << (src + 1)) + right + (1 << src);
        //int s_withOne = s << 1 + 1;
        C[s_withOne][src] = 10000; //numeric_limits<double>::infinity();
        //j_set = s_withOne - 1;
        j_set = s_withOne - (1 << src);
        
        /*bitset<8> a(s);
         bitset<8> b(left);
         bitset<8> c(right);
         bitset<8> d(s_withOne);
         
         cout << a << " " << b << " " << c << " " << d << endl;
         */
        j_counter = 1;
        
        while (j_set > 0)
        {
            if (j_counter == src + 1) {
                j_counter++;
                j_set >>= 1;
                continue;
            }
            //if (j_counter > numNodes) break;
            /*if (s == (1 << (numNodes - 1)) - 1 && j_counter == numNodes)
             flag = true;*/
            
            /*cout << "j_c  " << j_counter;
             bitset<8> sw(s_withOne);
             cout << ", sw  " << sw << endl;*/
            
            if (j_set & 1)
                recC(C, s_withOne, j_counter, D, travel, flag);
            
            j_counter++;
            j_set = j_set >> 1;
        }
    }
    
    
    /*for (int j = 1; j <= (1 << numNodes); j++) {
     for (int i = 1; i <= numNodes; i++) {
     cout << C[j][i] << " ";
     }
     cout << endl;
     }*/
    
    return C;
}

void recC(double** C, int S, int j, Graph<double>* D, List<int>* travel, bool flag)
{
    // return condition
    if (S - (1 << (j-1)) < 0)
        return;
    
    //initialization
    int i_set = S - (1 << (j - 1));
    if (i_set < 1)
        return;
    
    //if (flag && j != 1) {
    //	bitset<16> I(i_set);
    //	cout << "before_j: " << j << endl;
    //	//cout << "i_set: " << I << endl;
    //}
    
    int i = 1;
    
    List<double>* minList = new List<double>();
    //minList->setDefault();
    while (i_set > 0)
    {
        if (i > 10) break;
        if ((i_set & 1) && (i != j))
        {
            recC(C, S - (1 << (j-1)), i, D, travel, flag);
            
            minList->insertTail \
            (C[(S - (1 << (j-1)))][i] \
             + D->getEdge(i - 1, j - 1));
        }
        i++;
        i_set = i_set >> 1;
    }
    List<double>::Node* found = minList->getHead();
    double min = 10000; //numeric_limits<double>::infinity();
    while (found)
    {
        if (found->getData() < min)
            min = found->getData();
        found = found->getNext();
    }
    
    C[S][j] = min;
    //if (flag && j != 1) {
    //	if (!(travel->search(j)))
    //		//travel->remove(j);
    //		travel->insertTail(j);
    //}
    
    /*bitset<16> I(i_set);
     cout << "i set: " << I << endl;*/
    
    /*if(flag)
     cout << min << endl;*/
    
    minList->~List();
    
    return;
}

void getAns(double** C, int src, int numNodes, Graph<double>* G, List<string>* index, string origSrc) {
    double offset = 0.58;
    double min = 10000; //numeric_limits<double>::infinity();
    int tot = 1 << numNodes;
    List<int>* path = new List<int>();
    
//    cout << "src: " << src << endl;
    
    int min_pos = -1;
    for (int j = 1; j <= numNodes; j++) {
        if ((C[tot - 1][j] + G->getEdge(j - 1, src)) < min) {
            min = C[tot - 1][j] + G->getEdge(j - 1, src);
            min_pos = j - 1;
        }
    }
    min += offset;
    cout << "Total distance: " << min << endl;
    
    int i = 1;
//    cout << "minpos " << min_pos + 1 << endl;
    int nxt = tot - 1 - (1 << min_pos);
    
    path->insertTail(min_pos + 1);
    
//    bitset<16> set(nxt);
//    cout << nxt << " = " << set << endl << endl;
    
    while (i < numNodes) {
        min = 10000;
        int prev = min_pos;
        for (int j = 1; j <= numNodes; j++) {
            if ((C[nxt][j] + G->getEdge(j - 1, prev)) < min) {
                min = C[nxt][j] + G->getEdge(j - 1, prev);
                min_pos = j-1;
            }
//            cout << "C[" << nxt << "][" << j << "] " << C[nxt][j] << "  ";
//            cout << "G[" << j-1 << "][" << prev << "] " << G->getEdge(j - 1, prev) << endl;
        } //cout << endl;
        
        
        path->insertTail(min_pos+1);
        nxt = nxt - (1 << (min_pos));
//        cout << "minpos " << min_pos+1 << endl;
//        bitset<16> test(nxt);
//        
//        cout <<nxt<<" = "<<test << endl << endl;
        i++;
    }
    
    // print the path
    cout << "Path:" << endl;
    List<int>::Node* ptr = path->getHead();
   
    while(ptr){
        if(index->itemAt(ptr->getData() - 1)->getData() == origSrc)
            break;
        ptr = ptr->getNext();
    }
    if(!ptr)
        cout << index->itemAt(0)->getData() << " ";
    
    while (ptr) {
        cout << index->itemAt(ptr->getData() - 1)->getData() << " ";
        ptr = ptr->getNext();
    }
    
    ptr = path->getHead();
    while (ptr) {
        if(index->itemAt(ptr->getData() - 1)->getData() == origSrc)
            break;
        cout << index->itemAt(ptr->getData() - 1)->getData() << " ";
        ptr = ptr->getNext();
    }
    
    cout << origSrc << " ";


}
