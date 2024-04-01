#include <iostream>
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

bool sortByWeight (const Edge& a, const Edge& b){
    return(a.weight<b.weight);
}

// Create a single-node tree with i as the root
void MakeSet(Node *node, int i) {
    //TODO
    node->parent = i;
}

// Return the index of the element corresponding to the root of the tree that contains i
int FindSet(Node *nodes, int i) {
    //TODO
    int parent = nodes[i].parent;
    if(parent != i){
        parent = FindSet(nodes,parent);
        return parent;
    }else{
        return i;
    }
}

// Link the root of the tree with smaller rank to the root of the tree with larger rank
// when uniting the trees that contain u and v
void UnionByRank(Node *nodes, int u, int v) {
    //TODO
    int uRank = nodes[u].rank, vRank =nodes[v].rank;
    if(uRank == vRank){
        vRank++;
        nodes[u].parent = v;
    } else if(uRank<vRank){
        nodes[u].parent = v;
    } else{
        nodes[v].parent = u;
    }
}

void Kruskal(Node *nodes, Edge *edgeList, int vertexSize, int edgeCount) {
    //TODO: Implement Kruskal's algorithm to find the minimum spanning tree.
    Edge MST[vertexSize-1];
    int numInTree = 0;
    for (int i = 0; i < vertexSize; i++) {
        MakeSet(&nodes[i],i);
    }

    sort(edgeList, edgeList+edgeCount,sortByWeight);

    for (int i = 0; i < edgeCount; ++i) {
        if(FindSet(nodes,edgeList[i].src) != FindSet(nodes,edgeList[i].dst)){
            MST[numInTree] = edgeList[i];
            numInTree++;
            UnionByRank(nodes, FindSet(nodes,edgeList[i].src),FindSet(nodes,edgeList[i].dst));
        }
    }

	
    //TODO: Print out the resulting minimum spanning tree.
    cout << "Edges in the MST:" << endl;
    for(int i = 0; i < numInTree; ++i) {
        cout << MST[i].src << " -> " << MST[i].dst << " : " << MST[i].weight << endl;
    }
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