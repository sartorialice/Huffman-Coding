#include <iostream>
#include <map>
#include <fstream>
#include <math.h>
#include <vector>
#include <iomanip>

using namespace std;
//-------DATA STRUCTURES, GLOBAL VARIABLES AND FUNCTION DECLARATIONS------------------------------

map<char, vector<int>> HCoding; //Global variable with Huffman Coding for every character

struct node { //Node of the tree
  int freq;
  char ch;
  node *left;
  node *right;
};

struct HTree { //Huffman tree
  int size;
  int capacity;
  node **array;
};

//Initialize the structures
node *newNode(char ch, int freq);
HTree *createHeap(int capacity);

//Auxiliar and printing functions
void createCodingAux(int chCode[], int dim, char ch);
void swap(node **a, node **b);
void createCoding(node *father, int chCode[], int index);
int isLeaf(node *root);

//Create, building and working on the heap
HTree * buildHeap (char ch[], int freq[], int size);
void ConvertToHeap(HTree *Heap, int indx);
node *extractMin(HTree *Heap);
void insert(HTree *Heap, node *HeapNode);

//Huffman Tree functions
node *buildHfTree(char ch[], int freq[], int size);
void HuffmanCodes(char characters[], int freq[], int size, int max_dim);
