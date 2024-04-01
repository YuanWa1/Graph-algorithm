#include <iostream>
#include <fstream>
#include "AdjList.h"
#include "queue"
#include "iomanip"
#include "vector"
using namespace std;

struct CompareDistance {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) const {
        return a.first > b.first;
    }
};

void printSolution(int dist[], int prev[], int vertexSize, int startID) {
    // TODO: Print out the shortest distances and their corresponding paths from the source to all other nodes in the graph
    cout << "Vertex" << setw(12) << "Distance" << setw(10) << "Path" << endl;
    for(int i = 0; i < vertexSize; i++) {
        if (prev[i] != -1) {
            cout << setw(0) << startID << "->" << i << setw(10) << dist[i] << setw(10);
            int tmp = i;
            vector<int> path;
            while (tmp != startID) {
                path.push_back(tmp);
                tmp = prev[tmp];
            }
            path.push_back(startID);
            for (auto it = path.rbegin(); it != path.rend(); ++it) {
                cout << *it << setw(2);
            }
            cout << endl;
        }else if(i == startID){
            cout << setw(0) << startID << "->" << i << setw(10) << dist[i] << setw(10) << startID << endl;
        }else{
            cout << setw(0) << startID << "->" << i << setw(15) << "can't reach" << setw(10) << endl;
        }
    }
}
void Dijkstra(AdjList *list, int startID, int vertexSize) {
	int *dist = new int[vertexSize];
    int *prev = new int[vertexSize];
    bool *visited = new bool[vertexSize]();
    visited[startID] = true;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, CompareDistance> distanceQueue;
    // TODO: Implement Dijsktra's algorithm
    Node* tmp = list[startID].GetHeadNode();
    int maxint = ~(1 << (sizeof(int)*8-1));
    for(int i = 0; i < vertexSize; i++){
        //assign the max of int to each one
        dist[i] = maxint;
        //assign -1 as undefined
        prev[i] = -1;
    }
    //assign the values for adj node, and add the adj node to queue
    while(tmp!= nullptr){
        //update adj nodes
        dist[tmp->nodeID] = tmp->edgeWeight;
        prev[tmp->nodeID] = startID;
        tmp = tmp->next;
    }
    dist[startID]= 0;

//    for(int i =0; i < vertexSize; i++){
//        cout << i << " " << dist[i] << endl;
//    }

    //push the unsure node into a queue with order
    for(int i = 0; i < vertexSize; i++){
        if(i!=startID){
            distanceQueue.emplace(dist[i],i);
        }
    }

    //
    while(!distanceQueue.empty()) {
        auto p = distanceQueue.top();
        distanceQueue.pop();
        if (visited[p.second]) {
            continue;
        }
        if(p.first== maxint){
            continue;
        }
        visited[p.second] = true;
        Node *tmp = list[p.second].GetHeadNode();
        while (tmp != nullptr) {
            int alt = 0;
            alt = (p.first) + (tmp->edgeWeight);
            if (alt < dist[tmp->nodeID]) {
                dist[tmp->nodeID] = alt;
                prev[tmp->nodeID] = p.second;
                distanceQueue.emplace(dist[tmp->nodeID], tmp->nodeID);
            }
            tmp = tmp->next;
        }
    }

    printSolution(dist, prev, vertexSize, startID);

    delete[] visited;
	delete[] dist;
    delete[] prev;
}


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
        int src, dest, edgeweight;
        fin >> src >> dest >> edgeweight;
        list[src].AddNode(dest, edgeweight);
    }
	
    return list;
}

int main(int argc, char *argv[]){
	
    int vertexSize, edgeCount;
	
    if(argc < 2){
		fprintf(stderr, "ERROR: Must include edge list file as command line argument\n"); 
		exit(-1);
	}
    string file = argv[1];
	
    AdjList *adjList = createAdjList(file, vertexSize, edgeCount);
    
	int startNode = 0;
    Dijkstra(adjList, startNode, vertexSize);
    delete[] adjList;
	return 0;
}