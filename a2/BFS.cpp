#include <iostream>
#include <fstream>
#include <queue>
#include "AdjList.h"

using namespace std;

AdjList *createAdjList(string file, int &V, int &E){
    ifstream fin;
    fin.open(file);
    if(!fin){
        cout << "Input file not found! Please ensure you have the required file in the correct location\n";
        exit(EXIT_FAILURE);
    }
    fin >> V >> E;

    AdjList *list = new AdjList[V];
    for(int i = 0; i < E; i++){
        int src, dest;
        fin >> src >> dest;
        list[src].AddNode(dest);
    }

    return list;
}

void BFS(AdjList *list, int startID, bool *isVisited){
    // TODO
    queue<int> queue1;
    Node* current_node = new Node;
    int id = startID;
    isVisited[id] = true;
    queue1.push(id);
    while(!queue1.empty()){
        id = queue1.front();
        queue1.pop();
        current_node = list[id].GetHeadNode();
        //cout << "now at node id: " << current_node->nodeID << endl;
        while(current_node!= nullptr){
            if (!isVisited[current_node->nodeID]){
                isVisited[current_node->nodeID] = true;
                cout << "now at node id: " << current_node->nodeID << endl;
                queue1.push(current_node->nodeID);
            }
            current_node = current_node->next;
        }
    }
}

int main(int argc, char *argv[]){

    int vertexSize, edgeCount;

    if(argc < 2){
		fprintf(stderr, "ERROR: Must include edge list file as command line argument\n"); 
		exit(-1);
	}
    string file = argv[1];
	
    AdjList *adjList = createAdjList(file, vertexSize, edgeCount);

    bool *isVisited = new bool[vertexSize];
    for(int i = 0; i < vertexSize; i++){
        isVisited[i] = false;
    }

    BFS(adjList, 0, isVisited);

    return 0;
}