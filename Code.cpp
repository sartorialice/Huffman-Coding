#include "Huffman.h"

//------------FUNCTIONS---------------------------------------------------------
// Creating Huffman tree node
node *newNode(char ch, int freq) {
  node *aux = new node;

  aux->left = NULL;
  aux->right = NULL;
  aux->ch = ch;
  aux->freq = freq;

  return aux;
}

// Create Huffman using capacity
HTree *createHeap(int capacity) {
  HTree *Hufftree = new HTree;
  Hufftree->size = 0;
  Hufftree->capacity = capacity;
  Hufftree->array = (struct node **)malloc(Hufftree->capacity * sizeof(struct node *));

  return Hufftree;
}



// Swap function
void swap(node **a, node **b) {
  node *tmp = *a;
  *a = *b;
  *b = tmp;
}

// This function convert the array in a heap (Min)
void ConvertToHeap(HTree *Heap, int indx) {
  int smallest = indx; //Indicates the node with smallest frequence
//In a binary heap, the children of the node in pos indx are in pos:
  int right = 2 *indx + 2; //Right child is index * 2 plus 2
  int left = 2 * indx + 1; //Left child is index * 2 plus 1

//If frequence of right child is less than frequence of the current node
  if (right < Heap->size && Heap->array[right]->freq < Heap->array[smallest]->freq)
  	smallest = right; //The rightchild is the one with smaller frequence

//Frequence of left child is less than frequence of the current node
  if (left < Heap->size && Heap->array[left]->freq < Heap->array[smallest]->freq)
    smallest = left; //The left child is the one with smaller frequence

//Sorting nodes in the heap
  if (smallest != indx) {
    swap (&Heap->array[smallest], &Heap->array[indx]);
    ConvertToHeap(Heap, smallest);
  }

}

// Extract the minimum value from the heap
node *extractMin(HTree *Heap) {
  // Store the minimum value in aux and remove it from heap
  node *aux = Heap->array[0];
  Heap->array[0] = Heap->array[Heap->size - 1];

  Heap->size--;
  ConvertToHeap(Heap, 0); //Adjust the heap based on the changes

  return aux;
}

// Insertion in the Heap
void insert(HTree *Heap, node *HeapNode) {
  if (Heap->size == Heap->capacity){ //Overflow
    cout << "\nError: Could not insert\n";
    return;
 }
  ++Heap->size;
  int i = Heap->size - 1; //"i" is the last index

//While the frequence of the node to insert is less than his father node
  while (i && HeapNode->freq < Heap->array[(i - 1) / 2]->freq) {
    swap (Heap->array[i], Heap->array[(i - 1) / 2]); //Swap the current node with his father

    i = (i - 1) / 2; //Index of the father

  }
  Heap->array[i] = HeapNode; //Assign the new node

}



// Build the heap
HTree * buildHeap (char ch[], int freq[], int size) {
  HTree *Heap = createHeap(size);

//For every different character in the sequence create a new node in the heap
  for (int i = 0; i < size; ++i)
    Heap->array[i] = newNode(ch[i], freq[i]);

  Heap->size = size;

//In order to build the Heap, I start sorting the nodes from the last index,
//last cycle is for the first node
  for (int i =Heap->size; i >= 1; i--){
    ConvertToHeap(Heap, i-1); //Last index is size-1
	}
  return Heap;
}

//Function that controls if the node is a leaf
int isLeaf(node *root) {
  return !(root->left) && !(root->right);
}


node *buildHfTree(char ch[], int freq[], int size) {
  node *left;
  node *right;
  node *top;

  HTree *Heap = buildHeap(ch, freq, size); //Creates the Heap
//While the heap has still a value stored extract the leaves for huffman tree

  while (Heap->size > 1) {
    left = extractMin(Heap);
    right = extractMin(Heap);

//Using # as father id, giving as frequence the sum of the frequencies of the children
    top = newNode('#', left->freq + right->freq);
    top->left = left;
    top->right = right;

    insert(Heap, top); //Insert the nodes in Huffman Tree

  }

  return extractMin(Heap); //Return the root of the tree

}



// Creates the Coding
void createCodingAux(int chCode[], int dim, char ch) {
  vector<int> aux; //Auxiliar vector

  for (int i = 0; i < dim; ++i){
    aux.push_back(chCode[i]); //Assign the coding to a vector
 }
  HCoding[ch]= aux; //Assign the vector to global variable HCoding

}



//Huffman Coding funcion
void createCoding(node *Hnode, int chCode[], int index) {
//Recursion on the left side of the tree
  if (Hnode->left) {
    chCode[index] = 1; //Left edge codes 1
    createCoding(Hnode->left, chCode, index + 1);
  }
//Recursion on the right side of the tree
  if (Hnode->right) {
    chCode[index] = 0; //Right edge codes 0
    createCoding(Hnode->right, chCode, index + 1);
	}
//End of the tree, print the coding
	if (isLeaf(Hnode) ) {
    createCodingAux(chCode, index, Hnode->ch);

  }

}

// Creates the tree and pints the coding for each character in the text
void HuffmanCodes(char characters[], int freq[], int size, int max_dim) {
  node *root = buildHfTree(characters, freq, size); //Creates the Huffman Tree
	//Declaring useful variables to print the coding
  int chCode[max_dim];
  int index= 0;

  createCoding(root, chCode, index);

}

//Opens input file and inserts chars into map
void openinput (map<char, double>& hmap){
  fstream my_file;
  my_file.open("sample.txt", ios::in);
  char ch;
  while (my_file >> noskipws >> ch) {
        ++hmap[ch] ;
  }
  my_file.close();

}

//Opens and writes on output file
void openoutput (map<char, vector<int>> HCoding){
   ofstream outfile;

   	outfile.open("output.txt", ios::ate);
   	ifstream my_file2;
 	my_file2.open("sample.txt", ios::in);
  char ch2;

  	while (my_file2 >> noskipws >> ch2) {
  		for(auto mapIt = begin(HCoding); mapIt != end(HCoding); ++mapIt){
  			for(auto c : mapIt->second){
  		       if (ch2==mapIt->first)
  		       	outfile << c;
  		    }
       	}
   	}
   my_file2.close();
   outfile.close();
 }

//------------MAIN--------------------------------------------------------------

int main (){

  //Creating the map and opening the file
  map<char, double> hmap;

  openinput (hmap);

  //Printing the hash map with the occurence of every character
  for(auto elem : hmap){
     std::cout << elem.first << " " << elem.second<< " " << "\n";
  }
   //Calculating the total of the characters
   long int numlen = 0;
   long int seqlen = 0;
   for(auto elem : hmap){
      numlen+= elem.second;
      seqlen++;
   }

   //Calculating the entropy
   double prob[seqlen];
   double entropy=0;
   int counter=0;
   for(auto elem : hmap){
     prob[counter]= elem.second/numlen;
     counter++;
   }
   for(int i=0;i<seqlen;i++)
    entropy+= prob[i] * log2(1/prob[i]);

   cout << "The entropy of the file is " << entropy <<endl ;

   char arr[seqlen];

   int freq[seqlen];
   int i=0;
   for(auto elem : hmap){
     arr [i]= elem.first;
     freq[i]= elem.second;
     i++;
   }

	 long int max_dim_array = 50;
   cout << "Char | Huffman coding ";
   cout << "\n______________________\n";

   HuffmanCodes(arr, freq, seqlen, max_dim_array);

   double codeLenght[50];
   int counter1=0;

   //Print the huffman Coding
   for(auto mapIt = begin(HCoding); mapIt != end(HCoding); ++mapIt){
     codeLenght[counter1]=0;
     cout << mapIt->first << " : ";
     for(auto c : mapIt->second){
        codeLenght[counter1]++;
        cout << c << " ";
     }
     counter1++;
     cout << endl;
   }

   double expLenght=0;
   int counter2=0;

   for(auto elem: HCoding){
     expLenght += (prob[counter2] * codeLenght[counter2]);
     counter2++;
   }
   cout<<"Expected Lenght: "<<expLenght<<endl;
   cout<<"Is the expected lenght more than the entropy? "<< boolalpha <<(expLenght>entropy)<<endl;

   openoutput(HCoding);

   return 0 ;
}
