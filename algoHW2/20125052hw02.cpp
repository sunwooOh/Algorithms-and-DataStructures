#include<iostream>
#include<istream>
#include"Tree.h"
#include<cstring>

using namespace std;

Tree<int>* CreateHuffmanTree(char* text);
List<char>* CreateFreqList(char* text);
char* compress(Tree<int>* HuffmanTree, char* text);
char* decompress(Tree<int>* HuffmanTree, char* bitarray);

int main() {
    char *inText = new char[2000];
    char *comText;
    char *decomText;
    Tree<int>* createdTree;
    
    cout << "Please enter the text:" << endl;
    cin.getline(inText, 2000);
    
    createdTree = CreateHuffmanTree(inText);
    
    comText = compress(createdTree, inText);
    
    decomText = decompress(createdTree, comText);
    
    int i;
    cin >> i;
}

List<char>* CreateFreqList(char* text){
    char symbol;
    List<char> *charList = new List<char>();
    List<char>::Node* searchedNode = new List<char>::Node();
    
    charList->insertHead(text[0]);
    for (int i = 1; i < strlen(text); i++) {
        symbol = text[i];
        searchedNode = charList->search(symbol);
        if (searchedNode) charList->incFreq(searchedNode);
        else charList->insertTail(symbol);
    }
  
    return charList;
}

Tree<int>* CreateHuffmanTree(char* text) {
    List<char> *charList = new List<char>();
    Tree<int> *huffTree = new Tree<int>();
    List<char>::Node* curChar = new List<char>::Node();
    List<Tree<int>*> treeList;
    
    charList = CreateFreqList(text);
        
    List<Tree<int>*>::Node* curTree = new List<Tree<int>*>::Node();
    while (!(charList->isEmpty())) {
        curChar = charList->getHead();
        Tree<int>::TreeNode* tmpRoot = new Tree<int>::TreeNode(\
                                                               curChar->getFreq(), curChar->getData(), NULL, NULL, true);
        Tree<int>* tmpTree = new Tree<int>(tmpRoot);
        treeList.insertTail(tmpTree);
        curTree = treeList.getTail();
        curTree->setFreq(curChar->getFreq());
        charList->remove(curChar->getData());
    }
   
    while (treeList.size() != 1) {
        List<Tree<int>* >::Node* minFreq = new List<Tree<int>* >::Node();
        List<Tree<int>* >::Node* min2Freq = new List<Tree<int>* >::Node();
        List<Tree<int>* >::Node* cpMinFreq = new List<Tree<int>* >::Node();
        
        minFreq = treeList.searchMinFreq();
        Tree<int>* t1 = minFreq->getData();
        cpMinFreq = minFreq;
        treeList.remove(t1);
        min2Freq = treeList.searchMinFreq();
        Tree<int>* t2 = min2Freq->getData();
        
        Tree<int>::TreeNode* newRoot = new Tree<int>::TreeNode(\
			cpMinFreq->getFreq() + min2Freq->getFreq(), NULL, \
			t1->getRoot(), t2->getRoot(), false);
        
        Tree<int>* newTree = new Tree<int>(newRoot);
        treeList.insertTail(newTree);
        
        List<Tree<int>* >::Node* curList = treeList.getTail();
        
        curList->setFreq(newRoot->getData());
        
        treeList.remove(t2);
     }
    
    huffTree = treeList.getHead()->getData();
   
    return huffTree;
}

char* compress(Tree<int>* HuffmanTree, char* text) {
    int i = 0;
    char symbol;
    char* encTable;
    char* result = new char[10000];
    int pos = 0;
    
    encTable = HuffmanTree->lookUp(HuffmanTree->getRoot());
    
    while (i < strlen(text)) {
        symbol = text[i];

        int j = 1;
        
        while (encTable[symbol * 20 + j] == '0' || encTable[symbol * 20 + j] == '1') {
            result[pos] = encTable[symbol * 20 + j];
            j++; pos++;
        }
        result[pos] = ' ';
        i++; pos++;
    }
    
    cout << "Encoded result: ";
    i = 0;
    while(result[i] == '0' || result[i] == '1' || result[i]==' '){
        cout << result[i];
        i++;
    }
    cout << endl;
    
    return result;
}

char* decompress(Tree<int>* HuffmanTree, char* bitarray) {
    char* decText = new char[2000];
    char symbol;
    int pos = 0; int i = 0;
    
	cout << "Decoded result: ";
    while (i < strlen(bitarray)) {
        if (bitarray[i] == '0' || bitarray[i] == '1') {
            symbol = HuffmanTree->lookDown(bitarray, i);
            decText[pos] = symbol;
			cout << decText[pos];
            pos++; i++;
            
        }
        while (bitarray[i] == '0' || bitarray[i] == '1')
            i++;
        
        i++;
        
    }
    
    return decText;
}
