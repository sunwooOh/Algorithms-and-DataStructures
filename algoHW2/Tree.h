#include"List.h"
#include<iostream>

using namespace std;

template <class T>
class Tree {
public:
    class TreeNode {
    public:
        TreeNode(T x = 0, char y = NULL, TreeNode *left = NULL, TreeNode *right = NULL, bool z = NULL) {
            data = x; symbol = y; this->left = left; this->right = right;
            leaf = z;
        }
        T getData() { return data; }
        char getChar() { return symbol; }
        bool isLeaf() { return leaf; }
        TreeNode* getLeft() { return left; }
        TreeNode* getRight() { return right; }
        void setData(T x) { data = x; }
        void setChar(char sym) { symbol = sym; }
        void setLeft(TreeNode *ptr) { left = ptr; }
        void setRight(TreeNode *ptr) { right = ptr; }
        
    private:
        T data;
        char symbol;
        bool leaf;
        TreeNode *left, *right;
    };
    
    Tree(TreeNode* rootPtr = NULL) { this->rootPtr = rootPtr; }
    
    TreeNode* Search(T x) {
        if (isEmpty()) return NULL;
        TreeNode *p = rootPtr;
        while (p) {
            T a = p->getData();
            if (a == x) return p;
            else if (x < a) p = p->getLeft();
            else p = p->getRight();
        }
        return NULL;
    }

    TreeNode* remove(T x) {
        if (isEmpty()) return NULL;
        TreeNode *p = rootPtr;
        TreeNode *parent = NULL;
        char whatChild;
        while (p) {
            T a = p->getData();
            if (a == x) break;
            else if (x < a) { parent = p; whatChild = 'L'; p = p->getLeft(); }
            else { parent = p; whatChild = 'R'; p = p->getRight(); }
        }
        if (p == NULL) return NULL;
        if (p->getLeft() == NULL && p->getRight() == NULL) {
            if (parent)
                if (whatChild == 'L')
                    parent->setLeft(NULL);
                else
                    parent->setRight(NULL);
                else
                    rootPtr = NULL;
            return p;
        }
        else if (!(p->getLeft())) {
            if (parent)
                if (whatChild == 'L') parent->setLeft(p->getRight());
                else parent->setRight(p->getRight());
                else rootPtr = p->getRight();
            return p;
        }
        else if (!(p->getRight())) {
            if (parent)
                if (whatChild == 'L') parent->setLeft(p->getLeft());
                else parent->setRight(p->getLeft());
                else rootPtr = p->getLeft();
            return p;
        }
        else {
            TreeNode *returnNode = new TreeNode(p->getData());
            TreeNode *leftChild = p->getLeft();
            if (!(leftChild->getRight())) {
                p->setData(leftChild->getData()); p->setLeft(leftChild->getLeft());
                delete leftChild;
                return returnNode;
            }
            TreeNode *leftMost = leftChild->getRight();
            TreeNode *parent2 = leftChild;
            while (leftMost) {
                parent2 = leftMost;
                leftMost = leftMost->getRight();
            }
            p->setData(leftMost->getData());
            if (!(leftMost->getLeft()))
                parent2->setRight(NULL);
            else
                parent2->setRight(leftMost->getLeft());
            delete leftMost;
            return returnNode;
        }
    }
    TreeNode* getRoot() { return rootPtr; }
    bool isEmpty() { return rootPtr == NULL; }
    
    void visit(TreeNode *p) { cout << "("<< p->getData() << " " << p->getChar() << ")" << " "; }
    void preOrder(TreeNode *p) {
        if (!p) return;
        visit(p);
        preOrder(p->getLeft());
        preOrder(p->getRight());
    }
    void inOrder(TreeNode *p) {
        if (!p) return;
        inOrder(p->getLeft());
        if (p->isLeaf()) cout << p->getChar() << ":" << p->getData() << " ";
        inOrder(p->getRight());
    }
    void postOrder(TreeNode *p) {
        if (!p) return;
        postOrder(p->getLeft());
        postOrder(p->getRight());
        visit(p);
    }

    char* lookUp(TreeNode* p) {
        TreeNode* current = rootPtr;
        char* table = new char[256 * 20];
        string bitArray = "";
        
        lookUp(p, bitArray, table, current);
        return table;
    }
    void lookUp(TreeNode* p, string bitArray, char* table, TreeNode* current){
        
        if (current->isLeaf()) {
            int i = 0;
            while (bitArray[i] != '\0') {
            	table[current->getChar() * 20 + i + 1] = bitArray[i];
            	i++;
            }

            return;
        }
        else{
            if (p->getLeft()) {
                current = p->getLeft();
                lookUp(p->getLeft(), bitArray+'0', table, current);
            }
            if (p->getRight()) {
                current = p->getRight();
                lookUp(p->getRight(), bitArray+'1', table, current);
            }
        }
    }
    
    char lookDown(char* bitArray, int pos) {
        TreeNode* p = rootPtr;
        while (!(p->isLeaf())) {
            if (bitArray[pos] == '0') {
                p = p->getLeft();
                pos++;
            }
            else if (bitArray[pos] == '1') {
                p = p->getRight();
                pos++;
            }
        }
        return p->getChar();
    }
    
    
private:
    TreeNode* rootPtr;
};
