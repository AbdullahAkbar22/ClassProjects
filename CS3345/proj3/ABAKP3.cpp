/*
           ____   _____  _____ ____  _____  ______ 
     /\   |  _ \ / ____|/ ____/ __ \|  __ \|  ____|
    /  \  | |_) | (___ | |   | |  | | |  | | |__   
   / /\ \ |  _ < \___ \| |   | |  | | |  | |  __|  
  / ____ \| |_) |____) | |___| |__| | |__| | |____ 
 /_/    \_\____/|_____/ \_____\____/|_____/|______|
 
 
 The following code was written by Abdullah Akbar for his CS3345 (Data Structures) class at the University of Texas at Dallas
 
*/

#include <bits/stdc++.h>

using namespace std;

struct Edge;

//Node and Edge structs

struct Node{
	int val;
	vector<Edge *> connections; //Adjacency list to other nodes
	Node * from;
	int shortestD; //Shortest distance from the source node (determined by Dijkstra's
	
};

struct Edge{
	Node * from;
	Node * to;
	bool visited = false;
	int weight;
	
};

//MSTEdge will be used to list out edges generated by Kruskall's at the end of the program
struct MSTEdge{
	int vOne;
	int vTwo;
};

struct edgeCmp{ //Comparator to order edges by weight
    bool operator()(Edge* a, Edge* b){
        return a->weight > b->weight;
    }
};


struct mstCMP{//Comparator to handle the order with which we list out MSTs (smaller first vertex, then smaller second vertex)
	bool operator()(MSTEdge a, MSTEdge b){
		if(a.vOne == b.vOne)
			return a.vTwo > b.vTwo;
        return a.vOne > b.vOne;
    }
};

struct dijksCMP{ //Comparator to order Nodes in Dijkstra's algo
	bool operator()(Node* a, Node* b){
		
        return a->shortestD > b->shortestD;
    }
	
};


//PQue for all the edges in the graph (for Kruskalls)
priority_queue<Edge*, vector<Edge*>, edgeCmp> edgeList;
priority_queue<MSTEdge, vector<MSTEdge>, mstCMP> mstEdges; //PQue for edges in the MST we will list at the end

vector<Node *> nodeList; //A list of pointers to all the graph's nodes
priority_queue<Node *, vector<Node *>, dijksCMP> nodeQ; //PQue for Dijkstras


int* parents; //Parent array for union find (used in Kruskall's)




//Union find methods
int find(int passed){
	if(parents[passed] == -1){
		return passed;
	}
	
	return find(parents[passed]);
}

int unionElements(int one, int two){ //Returns -1 if the union would create a cycle, unions the nodes otherwise
	int parentTwo = find(two);
	
	int parentOne = find(one);
	
	if(parentOne == parentTwo)
		return -1;
	
	parents[parentTwo] = one;
	return 1;
}

int main(){
	ifstream infile("Graphs.txt");
	
	int numberNodes, source;
	infile >> numberNodes >> source;
	parents = new int[numberNodes + 1];
	fill(parents, parents + numberNodes + 1, -1);
	Node * src;
	
	for(int i = 1; i <= numberNodes; i++){ //Create all the  graph's nodes and set source node
		Node * newN = new Node();
		newN->val = i;
		if(i == source){
			newN->shortestD = 0;
			src = newN;
		}
		else{
			newN->shortestD = INT_MAX;
		}
		
		nodeList.push_back(newN);
	}
	
	int vFrom, vTo, edgeWeight;
	infile >> vFrom >> vTo >> edgeWeight;
	
	//We will treat each undirected edge as two directed edges going in opposite directions for Dijkstra's
	while(vFrom != 0 && vTo != 0 && edgeWeight != 0){
		Edge * newE = new Edge();
		newE->from = nodeList[vFrom - 1];
		newE->to = nodeList[vTo - 1];
		newE->weight = edgeWeight;
		
		Edge * secondE = new Edge();
		secondE->from = nodeList[vTo - 1];
		secondE->to = nodeList[vFrom - 1];
		secondE->weight = edgeWeight;
		
		nodeList[vFrom - 1]->connections.push_back(newE);
		nodeList[vTo - 1]->connections.push_back(secondE);
		edgeList.push(newE);
		infile >> vFrom >> vTo >> edgeWeight;
	}
	
	nodeQ.push(src); //Start out with source node in PQue
	
	
	//Dijkstra's algo
	while(!nodeQ.empty()){
		Node * currentNode = nodeQ.top();
		nodeQ.pop();
		
		
		for(Edge * edgeOn : currentNode->connections){
			
			
			if(!edgeOn->visited){
				//Update the Node's distance from the source if we have found a shorter one
				if((currentNode->shortestD + edgeOn->weight) < edgeOn->to->shortestD && (currentNode->shortestD + edgeOn->weight) > 0){
					edgeOn->to->from = currentNode;
					edgeOn->to->shortestD = (currentNode->shortestD + edgeOn->weight);
					nodeQ.push(edgeOn->to);
				}
				
				edgeOn->visited = true;
			}
		}
	}
	
	
	//Print out all the shortest paths from the source node we found for every node
	for(Node * nodeOn : nodeList){
		
		if(nodeOn == src){
			cout << nodeOn->val << " " << nodeOn->val << " " << 0 << endl;
		}
		else{
			vector<int> path;
			Node * traverse = nodeOn;
			while(traverse != src && traverse != nullptr){
				path.push_back(traverse->val);
				traverse = traverse->from;
			}
			path.push_back(src->val);
			
			for(int x = path.size() - 1; x > -1; x--){
				cout << path[x] << " ";
			}
			cout << nodeOn->shortestD << endl;
		}
	}
	
	cout << endl;
	
	
	//Kruskall's algo
	int edgesAdded = 0;
	long long int mstSum = 0;
	
	while(edgesAdded < (numberNodes - 1) && !edgeList.empty()){
		Edge * KEOn = edgeList.top();
		edgeList.pop();
		if(!(unionElements(KEOn->from->val, KEOn->to->val) == -1)){ //Add the edge to the tree if it will not cause a cycle
			edgesAdded++;
			mstSum += KEOn->weight;
			MSTEdge M = MSTEdge(); //Create MSTedge for display later
			M.vOne = min(KEOn->from->val, KEOn->to->val);
			M.vTwo = max(KEOn->from->val, KEOn->to->val);
			mstEdges.push(M);
		}
		
	}
	
	//Display all of the edges in the MST in the format requested
	while(!mstEdges.empty()){
		MSTEdge M = mstEdges.top();
		mstEdges.pop();
		cout << M.vOne << " " << M.vTwo << endl;
	}
	cout << "Minimal spanning tree length = " << mstSum << endl;
}