``#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

struct Node {
   int rank;
   int parent;
};

struct Edge {
   int src;
   int dst;
   int weight;
};

// Create a single-node tree with i as the root
void MakeSet(Node *node, int i) {
    //TODO
}

// Return the index of the element corresponding to the root of the tree that contains i
int FindSet(Node *nodes, int i) {
    //TODO
}

// Link the root of the tree with smaller rank to the root of the tree with larger rank
// when uniting the trees that contain u and v
void UnionByRank(Node *nodes, int u, int v) {
    //TODO
}

void Kruskal(Node *nodes, Edge *edgeList, int vertexSize, int edgeCount) {
    //TODO: Implement Kruskal's algorithm to find the minimum spanning tree.
    Edge MST[vertexSize-1];
	
	
    //TODO: Print out the resulting minimum spanning tree.
	
}

int main(int argc, char *argv[]){
    int vertexSize, edgeCount;
	
    if(argc < 2){
		fprintf(stderr, "ERROR: Must include edge list file as command line argument\n"); 
		exit(-1);
	}
    string file = argv[1];
	
    ifstream fin;
    fin.open(file);
	
    if(!fin){
        cout << "Input file not found! Please ensure you have the required file in the correct location\n";
		exit(EXIT_FAILURE);
    }
    fin >> vertexSize >> edgeCount;
	
    Node nodes[vertexSize];
    for(int i = 0; i < vertexSize; i++){
        nodes[i].rank = 0; 
        nodes[i].parent = -1; 
    }
	
    Edge edgeList[edgeCount];
    for (int i = 0; i < edgeCount; i++) {
        fin >> edgeList[i].src >> edgeList[i].dst >> edgeList[i].weight;
    }

    Kruskal(nodes, edgeList, vertexSize, edgeCount);

	return 0;
}